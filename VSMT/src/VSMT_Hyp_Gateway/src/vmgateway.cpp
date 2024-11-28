#include "vmgateway.hpp"

VMGateway::VMGateway(QObject *parent):
    QObject(parent)
{
    QObject::connect(&connector,&ClientConnector::clientConnected,this,&VMGateway::onClientConnected);
    QObject::connect(&connector,&ClientConnector::clientTimedOut,this,&VMGateway::onClientTimedOut);
}

void VMGateway::attemptLocalConnection()
{
    connector.attemptLocalConnection({
        .id = comm::ClientConfiguration::hostId(),
        .name = "host",
        .address = {0,0}
    });
}

void VMGateway::attemptRemoteConnection(vsock::Address address,client_id id)
{
    try {
        connector.attemptRemoteConnection({
            .id = id,
            .name = "VM",
            .address = address,
        });
    } catch(vsock::ConnectionError &e) {
        emit clientConnectionFailed(id,ConnectionStatus{
            .status = ConnectionStatus::Refused,
            .message = QString(e.what())
        });
    }
}

void VMGateway::disconnectFrom(comm::client_id id)
{
    if(vmDispatchers.count(id)) {
        vmDispatchers.erase(id);
    }
}

void VMGateway::onClientConnected(ConnectionStatus status, Connection connection)
{
    vmDispatchers.emplace(connection.dispatcher->getId(),connection.dispatcher);
    QObject::connect(connection.dispatcher.get(),&comm::ClientDispatcher::runtimeMetricReceived,[this](client_id id,auto rtMetric){
        emit metricReceived(id,rtMetric);
    });
    emit clientConnected(connection.dispatcher->getId(),connection);
}

void VMGateway::onClientTimedOut(ConnectionStatus status, common::client_id id)
{
    disconnectFrom(id);
    emit clientDisconnected(id);
}
