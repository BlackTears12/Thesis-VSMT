#include "vsocket.hpp"
#include "util.hpp"
#include "vsock_headers.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <QDebug>

namespace vsock
{

VSocket::VSocket(QObject *parent):
    listener(this) {}

VSocket::~VSocket()
{
    listener.requestInterruption();
    listener.wait();
    ::close(sock);
}

void VSocket::connect(const Address &address)
{
    sock = socket(AF_VSOCK, SOCK_STREAM, 0);

    if(sock < 0){
        qDebug() << "Socket creation failed";
        throw ConnectionError(util::getErrorStr());
    }

    sockaddr_vm sa = {
        .svm_family = AF_VSOCK,
        .svm_reserved1 = 0,
        .svm_port = address.port,
        .svm_cid = address.cid
    };

    qDebug() << "Socked created";

    if(::connect(sock,(sockaddr*)(&sa),sizeof(sa))){
        qDebug() << "Socket connect failed";
        throw ConnectionError(util::getErrorStr());
    }

    qDebug() << "Connected";

    finalize();
}

void VSocket::sendMessage(const Message &msg)
{
    msg.send(sock);
}

void VSocket::disconnect()
{
    listener.requestInterruption();
    sendMessage(Message::disconnectMessage);
}

void VSocket::finalize()
{
    QObject::connect(&listener,&VSockListener::messageReceived,this,&VSocket::messageReceived);
    QObject::connect(&listener,&VSockListener::socketDisconnected,this,&VSocket::onDisconnect);
    listener.setSocketDescriptor(sock);
    listener.start();
}

void VSocket::onDisconnect()
{
    listener.requestInterruption();
    listener.terminate();
    emit disconnected();
}

unique_ptr<VSocket> VSocket::wrapSocket(qintptr sock)
{
    auto device = std::make_unique<VSocket>();
    device->sock = sock;
    device->finalize();
    return std::move(device);
}

VSockListener::VSockListener(QObject *parent):
    QThread{parent} {}

void VSockListener::setSocketDescriptor(unsigned int s)
{
    sock = s;
}

void VSockListener::run()
{
    while(!isInterruptionRequested()) {
        auto msgPtr = Message::receive(sock);
        if(!msgPtr)
            continue;
        if(msgPtr->isDisconnect()) {
            emit socketDisconnected();
        }
        else {
            emit messageReceived(msgPtr);
        }
    }
}

}
