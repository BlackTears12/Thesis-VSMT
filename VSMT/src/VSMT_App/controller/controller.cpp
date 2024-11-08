#include "controller.hpp"
#include <QApplication>
#include "application.hpp"
#include <QtConcurrent/QtConcurrent>

namespace core
{

using core::Application;

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&connector,&ClientConnector::clientConnected,this,&Controller::onClientConnectionSuccess);
    QObject::connect(&connector,&ClientConnector::clientTimedOut,this,&Controller::onClientConnectionFailed);
}

void Controller::startExecution()
{
    connector.attemptLocalConnection(Application::Instance().getClientConfig(common::ClientConfiguration::hostId()));
}

void Controller::setClientIntoContext(common::client_id id)
{
    try {
        auto& client = getViewController(id);
        client->setContext();
        Application::Instance().getNavigator().registerContext(id);
    } catch(UnknownClientException &e) {
        qDebug() << "Cannot open client overview: No such client";
    }
}

void Controller::onClientConnectionSuccess(ConnectionStatus status,Connection conn)
{
    Application::Instance().getConfigModel().notifyClientStatusChanged(status,conn.dispatcher->getId());
    auto viewController = std::make_unique<ClientViewController>(conn);
    QObject::connect(viewController.get(),&ClientViewController::timedOut,this,&Controller::onConnectedClientTimedOut);
    clients.insert({conn.dispatcher->getId(),std::move(viewController)});
}

void Controller::onClientConnectionFailed(ConnectionStatus status,common::client_id id)
{
    Application::Instance().getConfigModel().notifyClientStatusChanged(status,id);
}

void Controller::onConnectedClientTimedOut(common::client_id id)
{
    removeClient(id,{ConnectionStatus::TimedOut,"Timed out"});
    qDebug() << "Client timed out - " << id;
}

void Controller::removeClient(client_id id,ConnectionStatus status)
{
    auto &viewController = getViewController(id);
    Application::Instance().getConfigModel().notifyClientStatusChanged(status,id);
    Application::Instance().getNavigator().registerContext(ClientConfiguration::hostId());
    clients.erase(id);
}

void Controller::handleConnection(client_id id)
{
    qDebug("Trying to connect to client: ");

    ///if a dispatcher is already connected
    if(clients.count(id)){
        return;
    }

    try{
        connector.attemptRemoteConnection(Application::Instance().getClientConfig(id));
    }
    catch(vsock::ConnectionError &e){
        qDebug() << e.what();
    }
    catch(core::UnknownClientException &e){
    }
}

void Controller::handleConfigDelete(common::client_id id)
{
    if(!clients.count(id)) {
        Application::Instance().getConfigModel().deleteConfig(id);
        return;
    }
    qDebug() << "cannot remove config: Client is connected: " << Application::Instance().getClientConfig(id).name;
}

void Controller::handleDisconnectRequest(common::client_id id)
{
    if(id == common::ClientConfiguration::hostId())
        return;
    removeClient(id,{ConnectionStatus::Idle,"Disconnected from client"});
}

unique_ptr<ClientViewController> &Controller::getViewController(client_id id)
{
    auto iter = clients.find(id);
    if(iter == clients.end())
        throw UnknownClientException();
    return iter->second;
}

}
