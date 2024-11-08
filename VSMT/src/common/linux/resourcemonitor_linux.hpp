#ifndef RESOURCEMONITOR_LINUX_HPP
#define RESOURCEMONITOR_LINUX_HPP

#include "resourcemonitor.hpp"

namespace metrics::monitor
{

template<>
class ResourceMonitor<Platform::Linux>
{
    class CpuMonitor
    {
    public:
        CpuMonitor();

        const CpuInfo& getInfo() const { return info; }
        vector<double> gatherCoreLoads();
    private:
        CpuInfo gatherProcessorInfo();
        double calculateLoadForCore(const vector<unsigned int> &data,unsigned int coreIdx);

        CpuInfo info;
        QVector<unsigned int> previousIdleTimes;
        QVector<unsigned int> previousTotalTimes;
    };
    class NetworkMonitor
    {
    public:
        NetworkMonitor() {}
        vector<NetworkInterfaceInfo> gatherInfo();
    private:
        NetworkInterfaceInfo gatherNetworkInterfaceLoad(const QNetworkInterface &interface);
        void updateCurrentLoads();

        struct LoadSnapShot
        {
            qint64 rx;
            qint64 tx;
        };

        QMap<QString,LoadSnapShot> currentLoads;
        QMap<QString,LoadSnapShot> previousLoads;
    };
public:
    explicit ResourceMonitor() { };

    unique_ptr<SystemInfo> gatherSysInfo();
    unique_ptr<RuntimeMetric> gatherRuntimeMetric();
private:
    MemoryInfo gatherMemoryInfo() const;
    vector<ProcessInfo> gatherProcessInfo() const;
    ProcessInfo parsePSCommandRow(const QString &line) const;
    vector<StorageInfo> gatherStorageInfo() const;
    vector<CanBusDeviceInfo> gatherCanDevInfo() const;

    unique_ptr<SystemInfo> sysInfoCache;
    CpuMonitor cpuMonitor;
    NetworkMonitor networkMonitor;
};

}

#endif // RESOURCEMONITOR_LINUX_HPP
