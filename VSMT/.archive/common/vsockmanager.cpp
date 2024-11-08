#include "vsockmanager.h"
#include <linux/virtio_vsock.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>
#include <unistd.h>
#include "util.h"

namespace vsock
{

VSockManager::VSockManager(int cid_,int port_,QObject *parent)
    : QObject{parent},cid(cid_),port(port_)
{
    sock = socket(AF_VSOCK, SOCK_STREAM, 0);
    if(sock < 0){
        throw ConnectionError(util::getErrorStr());
    }

    sockaddr_vm sa = {
        .svm_family = SOCK_STREAM,
        .svm_reserved1 = 0,
        .svm_port = static_cast<unsigned int>(port),
        .svm_cid = static_cast<unsigned int>(cid),
    };

    if(::connect(sock,reinterpret_cast<sockaddr*>(&sa),sizeof(sa))){
        throw ConnectionError(util::getErrorStr());
    }
    listening = true;
    listenThr = std::thread(&VSockManager::listen,this);
}

VSockManager::~VSockManager()
{
    listening = false;
    listenThr.join();
}

int VSockManager::send(const Data &message)
{
    return ::send(sock, (char*)&message, sizeof(message), 0);
}

void VSockManager::listen()
{
    Data data;
    int nbytes;
    while(listening){
        nbytes = ::read(sock,(char*)&data,sizeof(Data));
        if(nbytes)
            emit dataReceived(data);
    }
}

}
