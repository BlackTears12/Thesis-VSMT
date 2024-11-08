#include "metrics.hpp"

namespace metrics
{

Metric::Metric(shared_ptr<metrics::RuntimeMetric> metric,metricid_t id_) : type(metric.get() ? RuntimeMetricRequest : Corrupt),data(metric),id(id_)
{}

Metric::Metric(shared_ptr<metrics::SystemInfo> info,metricid_t id_) : type(info.get() ? SystemInfoRequest : Corrupt),data(info),id(id_)
{}

Metric::Metric(const Metric &metric)
{
    id = metric.id;
    data = metric.data;
    type = metric.type;
}

ProcessInfo::Status ProcessInfo::StrToStatus(QString str)
{
    if(str.isEmpty())
        return Status::Unknown;

    switch (str[0].unicode()) {
    case 'R':
        return Status::Running;
    case 'S':
        return Status::Sleeping;
    case 'D':
        return Status::Waiting;
    case 'Z':
        return Status::Zombie;
    case 'T':
        return Status::Stopped;
    case 'X':
        return Status::Dead;
    case 'I':
        return Status::Idle;
    default:
        return Status::Unknown;
    }
}

QString NetworkInterfaceInfo::typeAsStr() const
{
    switch(type){
    case Type::Loopback:
        return "Loopback";
    case Type::Virtual:
        return "Virtual";
    case Type::Ethernet:
        return "Ethernet";
    case Type::Wifi:
        return "Wifi";
    case Type::CanBus:
        return "CanBus";
    case Type::Fddi:
        return "Fiber Distributed Data Interface";
    case Type::Ppp:
        return "Point-to-Point Protocol";
    case Type::Slip:
        return "Serial Line Internet Protocol";
    case Type::Phonet:
        return "Linux Phone socket family";
    case Type::Ieee802154:
        return "Personal Area Network interface";
    case Type::Ieee80216:
        return "WiWire";
    case Type::Ieee1394:
        return "FireWire";
    case Type::SixLoWPAN:
    default:
        return "Unknown";
    }
}

}
