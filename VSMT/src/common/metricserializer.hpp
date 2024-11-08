#ifndef METRICSERIALIZER_HPP
#define METRICSERIALIZER_HPP

#include <QDataStream>
#include "metrics.hpp"

namespace metrics::serialization
{

Metric deserialize(QDataStream &stream);
QDataStream& serialize(QDataStream &stream,const Metric &metric);

QDataStream &operator>>(QDataStream &stream,CpuInfo &metric);
QDataStream &operator>>(QDataStream &stream,SystemInfo &metric);
QDataStream &operator>>(QDataStream &stream,MemoryInfo &metric);
QDataStream &operator>>(QDataStream &stream,StorageInfo &metric);
QDataStream &operator>>(QDataStream &stream,ProcessInfo &metric);
QDataStream &operator>>(QDataStream &stream,CanBusDeviceInfo &metric);
QDataStream &operator>>(QDataStream &stream,NetworkInterfaceInfo &metric);
QDataStream &operator>>(QDataStream &stream,RuntimeMetric &metric);

QDataStream &operator<<(QDataStream &stream,const CpuInfo &metric);
QDataStream &operator<<(QDataStream &stream,const SystemInfo &metric);
QDataStream &operator<<(QDataStream &stream,const MemoryInfo &metric);
QDataStream &operator<<(QDataStream &stream,const StorageInfo &metric);
QDataStream &operator<<(QDataStream &stream,const ProcessInfo &metric);
QDataStream &operator<<(QDataStream &stream,const CanBusDeviceInfo &metric);
QDataStream &operator<<(QDataStream &stream,const NetworkInterfaceInfo &metric);
QDataStream &operator<<(QDataStream &stream,const RuntimeMetric &metric);

template <typename T>
QDataStream &operator<<(QDataStream &stream,const vector<T> &metrics)
{
    stream << (uint16_t)metrics.size();
    for(size_t i = 0;i < metrics.size(); i++) {
        stream << metrics[i];
    }
    return stream;
}

template <typename T>
QDataStream &operator>>(QDataStream &stream,vector<T> &metrics)
{
    uint16_t size;
    stream >> size;
    metrics.resize(size);
    for(size_t i = 0;i < metrics.size(); i++) {
        stream >> metrics[i];
    }
    return stream;
}

}

#endif // METRICSERIALIZER_HPP
