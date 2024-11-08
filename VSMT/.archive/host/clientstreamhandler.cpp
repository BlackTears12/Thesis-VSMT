#include "clientstreamhandler.h"

namespace comm
{

ClientStreamHandler::ClientStreamHandler(unsigned int cid,unsigned int port,unsigned int respTimeoutS,
    unsigned int maxReqResend,QObject *parent) : QObject{parent},sockManager(cid,port),
    maxRequestResend(maxReqResend),responseTimeoutSec(respTimeoutS),timer(this)
{
    QObject::connect(&sockManager,&VSockManager::dataReceived,this,&ClientStreamHandler::onDataReceived);
    QObject::connect(&timer,&QTimer::timeout,this,&ClientStreamHandler::responseTimeout);
    timer.setSingleShot(false);
    timer.setInterval(responseTimeoutSec*60);
    timer.start();
}

ClientStreamHandler::~ClientStreamHandler()
{
    std::lock_guard<std::mutex> lock(pendingRequestMutex);
    pendingRequestLookup.clear();
    pendingRequests.clear();
}

void ClientStreamHandler::send(const vsock::Data &data,metrics::metricid_t id)
{
    sockManager.send(data);
    if(pendingRequests.count(id))
        throw PendingRequestException();
    std::lock_guard<std::mutex> lock(pendingRequestMutex);
    pendingRequests.emplace(id);
    pendingRequestLookup.emplace(id,PendingRequestData{id,data});
}

void ClientStreamHandler::acknowledge(metrics::metricid_t id)
{
    std::lock_guard<std::mutex> lock(pendingRequestMutex);
    pendingRequests.erase(id);
    pendingRequestLookup.erase(id);
}

void ClientStreamHandler::cancelRequest(metrics::metricid_t id)
{
    acknowledge(id);
}

void ClientStreamHandler::responseTimeout()
{
    std::lock_guard<std::mutex> lock(pendingRequestMutex);
    for(auto &e : pendingRequests){
        auto data = pendingRequestLookup[e];
        if(data.sendCtr >= maxRequestResend ){
            emit noResponseSignal(e);
            continue;
        }
        sockManager.send(data.data);
        data.sendCtr++;
    }
}

void ClientStreamHandler::onDataReceived(const vsock::Data &data)
{
    emit dataReceived(data);
}

}
