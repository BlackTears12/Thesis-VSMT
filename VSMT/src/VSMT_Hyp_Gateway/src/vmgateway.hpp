#ifndef VMGATEWAY_H
#define VMGATEWAY_H

#include "clientconfiguration.hpp"
#include "clientconnector.hpp"
#include "localclientdispatcher.hpp"
#include "remoteclientdispacher.hpp"
#include "command.hpp"
#include <QObject>

using comm::client_id;
using comm::Connection;
using comm::ClientConnector;
using std::shared_ptr;

class VMGateway : public QObject
{
    Q_OBJECT
public:
    explicit VMGateway(QObject *parent = nullptr);
    void attemptLocalConnection();
public slots:
    void attemptRemoteConnection(vsock::Address address,client_id id);
    void disconnectFrom(client_id id);
signals:
    void clientConnected(common::client_id id,Connection conn);
    void clientConnectionFailed(common::client_id id,ConnectionStatus status);
    void clientDisconnected(common::client_id id);
    void metricReceived(common::client_id id,shared_ptr<metrics::RuntimeMetric> metric);
private slots:
    void onClientConnected(ConnectionStatus status,Connection connection);
    void onClientTimedOut(ConnectionStatus status,common::client_id id);
private:
    ClientConnector connector;
    std::map<client_id,shared_ptr<comm::ClientDispatcher>> vmDispatchers;
};

#endif // VMGATEWAY_H
