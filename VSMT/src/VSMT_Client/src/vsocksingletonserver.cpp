#include "vsocksingletonserver.hpp"
#include "metricserializer.hpp"
#include "util.hpp"

#include <netinet/in.h>
#include <QFile>
#include <unistd.h>
#include <linux/vm_sockets.h>

namespace vsock
{

VSockSingletonServer::VSockSingletonServer(unsigned int port,QObject *parent)
    : QObject{parent},worker(this)
{
    QObject::connect(&worker,&ServerWorker::clientConnected,this,&VSockSingletonServer::onClientConnected);

    sock = socket(AF_VSOCK, SOCK_STREAM, 0);

    if(sock < 0){
        qDebug() << "Socket creation failed";
        throw ConnectionError(util::getErrorStr());
    }

    sockaddr_vm address;
    memset(&address,0,sizeof(address));
    address.svm_family = AF_VSOCK;
    address.svm_cid = (unsigned int)vsock::Address::CID::Any;
    address.svm_port = port;

    if(bind(sock,(sockaddr*)(&address),sizeof(address))){
        qDebug() << "Socket bind failed";
        throw ConnectionError(util::getErrorStr());
    }

    if(listen(sock,3)) {
        qDebug() << "Socket listen failed";
        throw ConnectionError(util::getErrorStr());
    }

    worker.setSocketDescriptor(sock);
    worker.start();
}

VSockSingletonServer::~VSockSingletonServer()
{
    worker.requestInterruption();
    worker.terminate();
    worker.wait();
    ::close(sock);
}

void VSockSingletonServer::send(const metrics::Metric &metric)
{
    Message msg;
    metrics::serialization::serialize(msg.getDataStream(),metric);
    socketDevice->sendMessage(msg);
}

void VSockSingletonServer::send(unique_ptr<metrics::RuntimeMetric> rtInfo)
{
    send(metrics::Metric(std::move(rtInfo),1));
}

void VSockSingletonServer::send(unique_ptr<metrics::SystemInfo> sysInfo)
{
    send(metrics::Metric(std::move(sysInfo),1));
}

void VSockSingletonServer::onClientConnected(qintptr socket)
{
    worker.requestInterruption();
    worker.terminate();
    socketDevice = VSocket::wrapSocket(socket);
    QObject::connect(socketDevice.get(),&VSocket::disconnected,this,&VSockSingletonServer::onClientDisconnected);
    emit clientConnected();
}

void VSockSingletonServer::onClientDisconnected()
{
    QObject::disconnect(socketDevice.get(),&VSocket::disconnected,this,&VSockSingletonServer::onClientDisconnected);
    qDebug() << "Client disconected";
    socketDevice = nullptr;
    worker.start();
    emit clientDisconnected();
}

ServerWorker::ServerWorker(QObject* p):
    QThread{p} {}

void ServerWorker::setSocketDescriptor(unsigned int s)
{
    sock = s;
}

void ServerWorker::run()
{
    qDebug() << "Started listening";
    qintptr clientSock;
    sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    while(!isInterruptionRequested()){
        clientSock = accept(sock, (struct sockaddr*)&address, &addrlen);
        if ((clientSock) > -1) {
            emit clientConnected(clientSock);
        }
    }
}

}
