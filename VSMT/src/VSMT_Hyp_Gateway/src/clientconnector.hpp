#ifndef CLIENTCONNECTOR_HPP
#define CLIENTCONNECTOR_HPP

#include <QMutex>
#include <QObject>
#include <QTimer>
#include <command.hpp>
#include "clientdispatcher.hpp"

namespace comm
{

using std::unique_ptr;

struct Connection
{
    shared_ptr<ClientDispatcher> dispatcher;
    shared_ptr<SystemInfo> systemInfo;
};

class ClientConnector : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnector(milliseconds timeout = seconds(5),QObject *parent = nullptr);

    void attemptRemoteConnection(const ClientConfiguration &config);
    void attemptLocalConnection(const ClientConfiguration &config);
signals:
    void clientConnected(ConnectionStatus status,Connection connection);
    void clientTimedOut(ConnectionStatus status,common::client_id id);
private slots:
    void resolveClients();
    void onClientConnected(client_id id,shared_ptr<SystemInfo> sysInfo);
private:
    void addConnectingDispatcher(const shared_ptr<ClientDispatcher> disp);

    std::map<common::client_id,shared_ptr<ClientDispatcher>> unresolvedClients;
    QTimer clientResolveTimer;
    QMutex unresolvedClientsLock;
};

}

#endif // CLIENTCONNECTOR_HPP
