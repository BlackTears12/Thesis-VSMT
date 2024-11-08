#ifndef CLIENTDISPATCHER_HPP
#define CLIENTDISPATCHER_HPP

#include <QObject>
#include "metrics.hpp"
#include "clientconfiguration.hpp"
#include "vsockclient.hpp"

namespace comm
{

using namespace metrics;
using common::ClientConfiguration;
using common::client_id;
using std::shared_ptr;
using vsock::VSockClient;
using std::chrono::milliseconds;
using std::chrono::seconds;

/*
 * Communicates with a client either on a guest machine or host
 * Its a virtual class use RemoteClientDispatcher or LocalClientDispatcher
*/
class ClientDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit ClientDispatcher(const ClientConfiguration &conf, QObject *parent = nullptr):
        QObject{parent},config(conf) {}
    virtual ~ClientDispatcher() = 0;

    client_id getId() const { return config.id; }
    QString getName() const { return config.name; }
signals:
    void runtimeMetricReceived(shared_ptr<RuntimeMetric> metrics);
    void clientConnected(shared_ptr<SystemInfo> sysInfo);
    void clientTimedOut();
protected:
    const ClientConfiguration config;
};

inline ClientDispatcher::~ClientDispatcher() {}

}

#endif // CLIENTDISPATCHER_HPP
