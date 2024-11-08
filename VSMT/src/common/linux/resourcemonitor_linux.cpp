#include "linux/commandutil.hpp"
#include "resourcemonitor_linux.hpp"
#include <linux/sysfileparser.hpp>
#include <QStorageInfo>

namespace metrics::monitor
{

ResourceMonitor<Platform::Linux>::CpuMonitor::CpuMonitor()
{
    info = gatherProcessorInfo();
    previousIdleTimes.resize(info.cores);
    previousTotalTimes.resize(info.cores);
}

CpuInfo ResourceMonitor<Platform::Linux>::CpuMonitor::gatherProcessorInfo()
{
    CpuInfo info;
    try {
        util::SysFileParser fileParser("/proc/cpuinfo");
        QString modelFullStr = fileParser.valueAt("model name").value_or(QStringList{"Not Available@Not Available"}).join(" ");
        auto modelIndx = modelFullStr.lastIndexOf('@');
        info.model = modelFullStr.left(modelIndx-1);
        info.speed = modelFullStr.right(modelFullStr.size()-modelIndx-2);
        // the last entry of a processor core is at the "processor" key
        info.cores = fileParser.valueAt("processor").value_or(QStringList{"0"})[0].toInt()+1;
    }
    catch(util::FileNotFoundException &e) {
        qDebug() << "File not found: " << e.fileName();
    }
    return info;
}

vector<double> ResourceMonitor<Platform::Linux>::CpuMonitor::gatherCoreLoads()
{
    vector<double> loads;
    QFile file("/proc/stat");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file";
        return loads;
    }
    ///discard the first line containing the summed values
    (void)file.readLine();

    loads.resize(info.cores);
    vector<unsigned int> data (9);
    ///read core_n lines and calculate the load
    for(int coreIdx = 0; coreIdx < info.cores; coreIdx++) {
        /* CPU nice systen idle iowait irq softirq steal guest guest_nice */
        auto parts = file.readLine().split(' ');
        parts.removeFirst();
        std::transform(parts.begin(),parts.end(),data.begin(),
                       [](const QByteArray& data){ return data.toUInt(); });
        loads[coreIdx] = calculateLoadForCore(data,coreIdx);
    }
    return loads;
}

double ResourceMonitor<Platform::Linux>::CpuMonitor::calculateLoadForCore(const vector<unsigned int> &data, unsigned int coreIdx)
{
    // idle = idle + iowait
    unsigned int idleTime = data.at(3) + data.at(4);
    unsigned int totalTime = std::reduce(data.begin(),data.end());

    unsigned int idleDelta = idleTime - previousIdleTimes[coreIdx];
    unsigned int totalDelta = totalTime - previousTotalTimes[coreIdx];

    previousTotalTimes[coreIdx] = totalTime;
    previousIdleTimes[coreIdx] = idleTime;

    // if for some reason the core wasnt used since the prev measurement
    if(totalDelta <= 0)
        return 0;

    return util::percentof(totalDelta-idleDelta,totalDelta);
}


vector<NetworkInterfaceInfo> ResourceMonitor<Platform::Linux>::NetworkMonitor::gatherInfo()
{
    updateCurrentLoads();
    vector<NetworkInterfaceInfo> infos;
    const auto &interfaces = QNetworkInterface::allInterfaces();
    infos.reserve(interfaces.size());
    for(auto &interface : interfaces) {
        infos.push_back(gatherNetworkInterfaceLoad(interface));
    }
    return infos;
}

NetworkInterfaceInfo ResourceMonitor<Platform::Linux>::
    NetworkMonitor::gatherNetworkInterfaceLoad(const QNetworkInterface &interface)
{
    auto prev = previousLoads.value(interface.name(),{0,0});
    auto current = currentLoads.value(interface.name(),prev);

    return {
        interface.humanReadableName(),
        interface.type(),
        current.rx - prev.rx,
        current.tx - prev.tx
    };
}

void ResourceMonitor<Platform::Linux>::NetworkMonitor::updateCurrentLoads()
{
    previousLoads = currentLoads;
    currentLoads.clear();
    QFile file("/proc/net/dev");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "cannot open /proc/net/dev";
        return;
    }
    file.readLine();
    file.readLine();
    QByteArray line = file.readLine();
    while(!line.isEmpty()) {
        auto ln = QString{line}.trimmed();
        line = file.readLine();
        auto parts = ln.split(':');
        if(parts.size() < 2) {
            continue;
        }
        auto values = parts[1].trimmed().split(' ');
        values.removeAll(QString{""});
        if(values.size() < 16) {
            continue;
        }

        currentLoads.insert(parts[0].trimmed(),{
            .rx = values[0].trimmed().toInt(),
            .tx = values[8].trimmed().toInt(),
        });
    }
}

unique_ptr<SystemInfo> ResourceMonitor<Platform::Linux>::gatherSysInfo()
{
    if(!sysInfoCache) {
        sysInfoCache = std::make_unique<SystemInfo>();
        sysInfoCache->platform = QString("%1 %2").arg(QSysInfo::kernelType(),QSysInfo::currentCpuArchitecture());
        sysInfoCache->distribution = QSysInfo::prettyProductName();
        sysInfoCache->cpuInfo = cpuMonitor.getInfo();
    }
    return std::unique_ptr<SystemInfo>(new SystemInfo(*sysInfoCache));
}


MemoryInfo ResourceMonitor<Platform::Linux>::gatherMemoryInfo() const
{
    MemoryInfo info;
    try {
        util::SysFileParser fileParser("/proc/meminfo");
        info.total = fileParser.valueAt("MemTotal").value_or(QStringList{"100"})[0].toInt();
        auto available = fileParser.valueAt("MemAvailable").value_or(QStringList{"0"})[0].toInt();
        info.used = info.total - available;
    } catch(util::FileNotFoundException &e) {
        qDebug() << "File not found: " << e.fileName();
    }
    return info;
}

ProcessInfo ResourceMonitor<Platform::Linux>::parsePSCommandRow(const QString &line) const
{
    auto parts = line.split(' ');
    parts.removeAll("");

    return ProcessInfo {
        (pid_t)parts[0].toUInt(),
        ProcessInfo::StrToStatus(parts[1]),
        parts[2].toDouble(),
        parts[3].toDouble(),
        parts[4],
        parts[5]
    };
}

vector<ProcessInfo> ResourceMonitor<Platform::Linux>::gatherProcessInfo() const
{
    vector<ProcessInfo> infos;
    try {
        QString output = util::cmd::exec("ps",{"--no-headings","-w","-a","-e","-o",
                                              "pid,state,pcpu,pmem,comm,args"});
        QTextStream stream(&output);
        while(!stream.atEnd()) {
            infos.push_back(parsePSCommandRow(stream.readLine()));
        }
    } catch(util::cmd::ExecutionError &e) {
        qDebug() << "Cannot exec ps";
    }
    return infos;
}

unique_ptr<RuntimeMetric> ResourceMonitor<Platform::Linux>::gatherRuntimeMetric()
{
    return std::make_unique<RuntimeMetric>(
        cpuMonitor.gatherCoreLoads(),
        gatherMemoryInfo(),
        gatherProcessInfo(),
        gatherStorageInfo(),
        gatherCanDevInfo(),
        networkMonitor.gatherInfo()
    );
}

vector<StorageInfo> ResourceMonitor<Platform::Linux>::gatherStorageInfo() const
{
    vector<StorageInfo> infos;
    auto mountedVolumes = QStorageInfo::mountedVolumes();
    for(const auto &storage : mountedVolumes) {
        if(!storage.isRoot() || !storage.isReady() || storage.isReadOnly())
            continue;
        infos.push_back(StorageInfo {
            storage.displayName(),
            storage.fileSystemType(),
            storage.device(),
            util::byteToKb(storage.bytesTotal()),
            util::byteToKb(storage.bytesAvailable())
        });
    }
    return infos;
}

vector<CanBusDeviceInfo> ResourceMonitor<Platform::Linux>::gatherCanDevInfo() const
{
    return {};
}

}
