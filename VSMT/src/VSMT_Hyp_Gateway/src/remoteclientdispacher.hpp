#ifndef REMOTECLIENTDISPACHER_H
#define REMOTECLIENTDISPACHER_H

#include "clientdispatcher.hpp"
#include <QTimer>

namespace comm
{

/* Communicates with a remote client in VM */
class RemoteClientDispatcher : public ClientDispatcher
{
    Q_OBJECT
public:
    explicit RemoteClientDispatcher(const ClientConfiguration &conf, seconds timeout = seconds(5), QObject *parent = nullptr);
    ~RemoteClientDispatcher() override = default;
private slots:
    void onMetricReceived(metrics::Metric metric);
protected:
    VSockClient client;
    QTimer timeoutTmr;
};

}
#endif // REMOTECLIENTDISPACHER_H
