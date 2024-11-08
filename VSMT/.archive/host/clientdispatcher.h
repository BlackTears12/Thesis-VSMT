#ifndef CLIENTDISPATCHER_H
#define CLIENTDISPATCHER_H

#include <QObject>
#include "clientstreamhandler.h"
#include "responseparser.h"
#include "../common/metrics.h"

#define INVALID_CLIENT_ID 0;

namespace comm
{

using namespace metrics;
using std::shared_ptr;

typedef uint16_t client_id_t;

struct ClientConfiguration
{
    client_id_t id;
    unsigned int cid;
    unsigned int port;
};

struct Connection
{
    enum State {Active,Timeout,Error};
    comm::client_id_t id = INVALID_CLIENT_ID;
    State state = Error;
    shared_ptr<SystemInfo> system = nullptr;
};

/*
 * Communicates with a client either on a guest machine or host
*/
class ClientDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit ClientDispatcher(const ClientConfiguration &conf,unsigned int responseTimeoutS=5,
                              unsigned int maxReqResend=3,QObject *parent = nullptr);
    void requestRuntimeMetric();
    Connection getConnection() const { return connection; }
    client_id_t getId() const { return connection.id; }
signals:
    void connectionResolved(Connection connection);
    void clientUnresponsive();
    void runtimeMetricReceived(shared_ptr<RuntimeMetric> metrics);
    void systemInfoReceived(shared_ptr<SystemInfo> info);
private:
    void tryToConnect();
    void requestSystemInfo();
    void handleActiveConnection(shared_ptr<SystemInfo> info);
private slots:
    void onDataReceived(const vsock::Data &data);
    void onNoResponseSignal(metrics::metricid_t id);
    void onSystemInfoReceived(shared_ptr<SystemInfo> info);
private:
    ClientStreamHandler streamHandler;
    const ClientConfiguration config;
    ResponseParser parser;
    Connection connection;
};

}

#endif // CLIENTDISPATCHER_H
