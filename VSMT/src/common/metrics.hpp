#ifndef METRICS_H
#define METRICS_H

#include "util.hpp"
#include <qdebug.h>
#include <variant>
#include <memory>
#include <cstdint>
#include <QString>
#include <vector>
#include <QObject>
#include <QNetworkInterface>

namespace metrics
{
using std::unique_ptr;
using std::shared_ptr;

using metricid_t = uint8_t;
using memoryunit_t = uint32_t;
using pid_t = uint16_t;
using std::vector;

/* Info on the processor */
struct CpuInfo
{
    CpuInfo(QString m,uint8_t core_n,QString sp):
        model(m),cores(core_n),speed(sp) {}

    CpuInfo(const CpuInfo&) = default;
    CpuInfo() = default;

    QString model;
    QString speed;
    uint8_t cores;
};

/* Static info on the os cannot change in runtime */
struct SystemInfo
{
    SystemInfo(CpuInfo info,QString platf,QString distr):
        cpuInfo(info),platform(platf),distribution(distr) {}

    SystemInfo(const SystemInfo&) = default;
    SystemInfo() = default;

    QString distribution;
    QString platform;
    CpuInfo cpuInfo;
};

/* Info on memory in kb-s */
struct MemoryInfo
{
    MemoryInfo(uint64_t total_,uint64_t used_):
        total(total_),used(used_){}

    MemoryInfo(const MemoryInfo&) = default;
    MemoryInfo() = default;

    constexpr double usedPercent() const { return util::percentof(used,total); }

    uint32_t total;
    uint32_t used;
};

/* Info on a disk device */
struct StorageInfo
{
    StorageInfo(QString nm,QString fileFs,QString dev,qint64 mbtotal,qint64 mbfree):
        name(nm),fileSystemType(fileFs),device(dev),mbytesTotal(mbtotal),mbytesFree(mbfree){}

    StorageInfo(const StorageInfo&) = default;
    StorageInfo() = default;

    constexpr double usedPerced() const { return util::percentof(mbytesUsed(),mbytesTotal); }
    constexpr qint64 mbytesUsed() const { return mbytesTotal - mbytesFree; }

    QString name;
    QString fileSystemType;
    QString device;
    qint64 mbytesTotal;
    qint64 mbytesFree;
};

/* Info on a single process */
struct ProcessInfo
{
    enum Status
    {
        Running,Sleeping,Waiting,Zombie,Stopped,Dead,Idle,
        Unknown
    };

    QString StatusToStr() const
    {
        QString arr[] = {
            "Running","Sleeping","Waiting","Zombie","Stopped","Dead","Idle",
            "Unknown"
        };
        return arr[(int)status];
    }

    ProcessInfo(pid_t p,Status stat,double proc,double mem,QString exec,QString arg):
        pid(p),status(stat),processorUsage(proc),memoryPercent(mem),executable(exec),args(arg) {}

    ProcessInfo(const ProcessInfo&) = default;
    ProcessInfo() = default;

    pid_t pid;
    Status status;
    double processorUsage;
    double memoryPercent;
    QString executable;
    QString args;
public:
    static Status StrToStatus(QString str);
};

/* Info on a single can bus interface plugin */
struct CanBusDeviceInfo
{
    CanBusDeviceInfo(QString n,QString plug,QString serial,int ch,bool virt):
        name(n),plugin(plug),serialNumber(serial),channel(ch),isVirtual(virt) {}

    CanBusDeviceInfo(const CanBusDeviceInfo&) = default;
    CanBusDeviceInfo() = default;

    QString name;
    QString plugin;
    QString serialNumber;
    int channel;
    bool isVirtual;
};

/* Info on a network interface */
struct NetworkInterfaceInfo
{
    using Type = QNetworkInterface::InterfaceType;
    NetworkInterfaceInfo(QString nm,Type t,qint64 rxb,qint64 txb):
        name(nm),type(t),rxBytes(rxb),txBytes(txb) {}

    NetworkInterfaceInfo(const NetworkInterfaceInfo&) = default;
    NetworkInterfaceInfo() = default;

    QString typeAsStr() const;

    QString name;
    Type type;
    qint64 rxBytes;
    qint64 txBytes;
};

/* Info on the os runtime at a given moment */
struct RuntimeMetric : public QObject
{
    Q_OBJECT
public:
    RuntimeMetric(vector<double> coreL,MemoryInfo mem,vector<ProcessInfo> proc,
        vector<StorageInfo> storage,vector<CanBusDeviceInfo> caninfo,vector<NetworkInterfaceInfo> netinfo):
        coreLoads(coreL),memory(mem),processes(proc),storageInfo(storage),
        canBusDevInfo(caninfo),networkInfo(netinfo) {}

    RuntimeMetric() = default;

    double overallCpuLoad() const { return util::average(coreLoads); }
    double overallStorageLoad() const
    {
        qint64 allMBytes = 0;
        qint64 usedMBytes = 0;
        for(const auto &e : storageInfo) {
            allMBytes += e.mbytesTotal;
            usedMBytes += e.mbytesUsed();
        }
        return util::percentof(usedMBytes,allMBytes);
    }

    MemoryInfo memory;
    vector<double> coreLoads;
    vector<ProcessInfo> processes;
    vector<StorageInfo> storageInfo;
    vector<CanBusDeviceInfo> canBusDevInfo;
    vector<NetworkInterfaceInfo> networkInfo;
};

/* Wrapper around the variant type of RuntimeMetric and SystemInfo */
struct Metric : public QObject
{
    Q_OBJECT
public:
    typedef std::variant<shared_ptr<RuntimeMetric>,shared_ptr<SystemInfo>> ResponseData;
    enum Type
    {
        SystemInfoRequest = 0,
        RuntimeMetricRequest = 1,
        Corrupt
    };
public:
    explicit Metric(shared_ptr<metrics::RuntimeMetric> metric,metricid_t id);
    explicit Metric(shared_ptr<metrics::SystemInfo> sysinfo,metricid_t id);
    explicit Metric(void* nullp,metricid_t id_): type(Corrupt),id(id_) {}
    Metric(const Metric &metric);

    bool valid() const { return type != Type::Corrupt; }

    /* Moves the contained data casted to RuntimeMetric ptr*/
    shared_ptr<metrics::RuntimeMetric> asRuntimeMetric() { return std::get<shared_ptr<metrics::RuntimeMetric>>(data); }

    /* Moves the contained data casted to SystemInfo ptr*/
    shared_ptr<metrics::SystemInfo> asSysInfo() { return std::get<shared_ptr<metrics::SystemInfo>>(data); }

    const ResponseData& viewData() const { return data; }

    Type getType() const { return type; }
    metricid_t getId() const { return id; }
private:
    /*
     * type has to be initialized before data
    */    
    Type type;
    ResponseData data;
    metricid_t id;
};

}

#endif // METRICS_H
