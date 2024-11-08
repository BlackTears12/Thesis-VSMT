#include "clientdispatcher.h"

namespace comm
{

ClientDispatcher::ClientDispatcher(const ClientConfiguration &conf,unsigned int responseTimeoutS, unsigned int maxReqResend, QObject *parent):
    QObject{parent},streamHandler(conf.cid,conf.port,responseTimeoutS,maxReqResend),config(conf)
{
    QObject::connect(&streamHandler,&ClientStreamHandler::dataReceived,this,&ClientDispatcher::onDataReceived);
    QObject::connect(&streamHandler,&ClientStreamHandler::noResponseSignal,this,&ClientDispatcher::onNoResponseSignal);
    tryToConnect();    
}


void ClientDispatcher::requestRuntimeMetric()
{
    streamHandler.send(parser.requestData<Metric::RuntimeMetricRequest>(),parser.nextId());
}

void ClientDispatcher::tryToConnect()
{
    requestSystemInfo();
}

void ClientDispatcher::requestSystemInfo()
{
    streamHandler.send(parser.requestData<Metric::SystemInfoRequest>(),parser.nextId());
}

void ClientDispatcher::handleActiveConnection(shared_ptr<SystemInfo> info)
{
    connection = {
        .id = config.id,
        .state = Connection::Active,
        .system = info
    };
    emit connectionResolved(connection);
}

void ClientDispatcher::onDataReceived(const vsock::Data &data)
{
    auto metr = parser.parse(data);
    if(metr->getType() == Metric::Corrupt){
        /* Corrupt packet */
        return;
    }

    streamHandler.acknowledge(metr->getId());
    switch(metr->getType()){
    case Metric::SystemInfoRequest:
        emit systemInfoReceived(metr->moveDataAsSysInfo());
        break;
    case Metric::RuntimeMetricRequest:
        emit runtimeMetricReceived(metr->moveDataAsMetric());
        break;
    default:
        return;
    }
}

void ClientDispatcher::onNoResponseSignal(metricid_t id)
{
    streamHandler.cancelRequest(id);
    if(id == CONNECTION_HANDSHAKE_ID)
        emit connectionResolved({
            .id = config.id,
            .state = Connection::Timeout,
            .system = nullptr
        });
    else
        emit clientUnresponsive();
}

void ClientDispatcher::onSystemInfoReceived(shared_ptr<SystemInfo> info)
{
    handleActiveConnection(info);
}

}
