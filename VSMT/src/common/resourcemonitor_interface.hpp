#ifndef RESOURCEMONITOR_INTERFACE_H
#define RESOURCEMONITOR_INTERFACE_H

#include "metrics.hpp"
#include <QException>
#include "platform.hpp"

namespace metrics::monitor
{

class InvalidPlatformException : public QException {};

template <Platform>
class ResourceMonitor
{
public:
    explicit ResourceMonitor() {};

    unique_ptr<SystemInfo> gatherSysInfo() { throw InvalidPlatformException(); }
    unique_ptr<RuntimeMetric> gatherRuntimeMetric() { throw InvalidPlatformException(); }
};


}

#endif // RESOURCEMONITOR_INTERFACE_H
