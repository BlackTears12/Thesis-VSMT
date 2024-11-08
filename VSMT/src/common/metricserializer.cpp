#include "metricserializer.hpp"

namespace metrics::serialization
{

QDataStream &operator>>(QDataStream &stream,CpuInfo &metric)
{
    stream >> metric.model;
    stream >> metric.cores;
    stream >> metric.speed;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,SystemInfo &metric)
{
    stream >> metric.cpuInfo;
    stream >> metric.platform;
    stream >> metric.distribution;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,MemoryInfo &metric)
{
    stream >> metric.total;
    stream >> metric.used;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,StorageInfo &metric)
{
    stream >> metric.name;
    stream >> metric.fileSystemType;
    stream >> metric.device;
    stream >> metric.bytesTotal;
    stream >> metric.bytesFree;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,ProcessInfo &metric)
{
    stream >> metric.pid;
    stream >> metric.status;
    stream >> metric.processorUsage;
    stream >> metric.memoryPercent;
    stream >> metric.executable;
    stream >> metric.args;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,CanBusDeviceInfo &metric)
{
    stream >> metric.name;
    stream >> metric.plugin;
    stream >> metric.serialNumber;
    stream >> metric.channel;
    stream >> metric.isVirtual;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,NetworkInterfaceInfo &metric)
{
    stream >> metric.name;
    stream >> metric.type;
    stream >> metric.rxBytes;
    stream >> metric.txBytes;
    return stream;
}

QDataStream &operator>>(QDataStream &stream,RuntimeMetric &metric)
{
    stream >> metric.coreLoads;
    stream >> metric.memory;
    stream >> metric.processes;
    stream >> metric.storageInfo;
    stream >> metric.canBusDevInfo;
    stream >> metric.networkInfo;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const CpuInfo &metric)
{
    stream << metric.model;
    stream << metric.cores;
    stream << metric.speed;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const SystemInfo &metric)
{
    stream << metric.cpuInfo;
    stream << metric.platform;
    stream << metric.distribution;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const MemoryInfo &metric)
{
    stream << metric.total;
    stream << metric.used;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const StorageInfo &metric)
{
    stream << metric.name;
    stream << metric.fileSystemType;
    stream << metric.device;
    stream << metric.bytesTotal;
    stream << metric.bytesFree;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const ProcessInfo &metric)
{    
    stream << metric.pid;
    stream << metric.status;
    stream << metric.processorUsage;
    stream << metric.memoryPercent;
    stream << metric.executable;
    stream << metric.args;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const CanBusDeviceInfo &metric)
{
    stream << metric.name;
    stream << metric.plugin;
    stream << metric.serialNumber;
    stream << metric.channel;
    stream << metric.isVirtual;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const NetworkInterfaceInfo &metric)
{
    stream << metric.name;
    stream << metric.type;
    stream << metric.rxBytes;
    stream << metric.txBytes;
    return stream;
}

QDataStream &operator<<(QDataStream &stream,const RuntimeMetric &metric)
{
    stream << metric.coreLoads;
    stream << metric.memory;
    stream << metric.processes;
    stream << metric.storageInfo;
    stream << metric.canBusDevInfo;
    stream << metric.networkInfo;
    return stream;
}

Metric deserialize(QDataStream &stream)
{
    metricid_t id;
    Metric::Type type;
    stream >> id;
    stream >> type;
    switch (type) {
    case Metric::RuntimeMetricRequest: {
        auto rtMetric = std::make_shared<RuntimeMetric>();
        stream >> *rtMetric;
        return Metric(std::move(rtMetric),id);
    }
    case Metric::SystemInfoRequest: {
        auto sysInfo = std::make_shared<SystemInfo>();
        stream >> *sysInfo;
        return Metric(std::move(sysInfo),id);
    }
    case Metric::Corrupt:
    default:
        return Metric(nullptr,id);
    }
}

QDataStream& serialize(QDataStream &stream, const Metric &metric)
{
    stream << metric.getId();
    stream << metric.getType();
    switch (metric.getType()) {
    case Metric::RuntimeMetricRequest:
        stream << *std::get<shared_ptr<RuntimeMetric>>(metric.viewData());
        break;
    case Metric::SystemInfoRequest:
        stream << *std::get<shared_ptr<SystemInfo>>(metric.viewData());
        break;
    case Metric::Corrupt:
        break;
    }
    return stream;
}

}

