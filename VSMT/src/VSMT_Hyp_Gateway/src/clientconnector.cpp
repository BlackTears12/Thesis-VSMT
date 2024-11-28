#include "clientconnector.hpp"

#include "localclientdispatcher.hpp"
#include "remoteclientdispacher.hpp"

namespace comm
{

ClientConnector::ClientConnector(milliseconds timeout,QObject *parent)
    : QObject{parent}
{
    clientResolveTimer.setSingleShot(true);
    clientResolveTimer.setInterval(timeout);
    QObject::connect(&clientResolveTimer,&QTimer::timeout,this,&ClientConnector::resolveClients);
}

void ClientConnector::attemptRemoteConnection(const ClientConfiguration &config)
{
    if(!unresolvedClients.count(config.id))
        addConnectingDispatcher(std::make_shared<RemoteClientDispatcher>(config));
}

void ClientConnector::attemptLocalConnection(const ClientConfiguration &config)
{
    addConnectingDispatcher(std::make_shared<LocalClientDispatcher>(config));
}

void ClientConnector::resolveClients()
{
    unresolvedClientsLock.lock();
    for(auto &e : unresolvedClients) {
        emit clientTimedOut(ConnectionStatus{
            .status = ConnectionStatus::TimedOut,
            .message = "Timed out"
        },e.second->getId());
    }
    unresolvedClients.clear();
    unresolvedClientsLock.unlock();
}

void ClientConnector::onClientConnected(common::client_id id, shared_ptr<SystemInfo> sysInfo)
{
    unresolvedClientsLock.lock();
    auto disp = unresolvedClients[id];
    unresolvedClients.erase(id);
    unresolvedClientsLock.unlock();
    emit clientConnected(ConnectionStatus(),{
        .dispatcher = disp,
        .systemInfo = sysInfo
    });
}

void ClientConnector::addConnectingDispatcher(const shared_ptr<ClientDispatcher> disp)
{
    QObject::connect(disp.get(),&ClientDispatcher::clientConnected,this,&ClientConnector::onClientConnected);
    unresolvedClientsLock.lock();
    unresolvedClients.emplace(disp->getId(),disp);
    clientResolveTimer.start();
    unresolvedClientsLock.unlock();
}


}
