#ifndef LOCALCLIENTDISPATCHER_HPP
#define LOCALCLIENTDISPATCHER_HPP

#include <QObject>
#include <QTimer>
#include "clientdispatcher.hpp"
#include "resourcemonitor.hpp"

namespace comm
{

using ResourceMonitor = monitor::ResourceMonitor<platform::current>;

/*
 * Communicates with a client on the host machine
 * In practice it emulates a ClientDispatcher with a ResourceMonitor and scheduled metric sending
*/
class LocalClientDispatcher : public ClientDispatcher
{
    Q_OBJECT
public:
    explicit LocalClientDispatcher(const ClientConfiguration &conf, milliseconds metricInterval = milliseconds(1000), QObject *parent = nullptr);
    ~LocalClientDispatcher() override = default;
private slots:
    /* emit the clientConnected signal and set up intervalTimer */
    void finalizeDispatcher();
    void onMetricDue();
protected:
    QTimer intervalTimer;
    ResourceMonitor resourceMonitor;
    milliseconds metricInterval;
};

}

#endif // LOCALCLIENTDISPATCHER_HPP
