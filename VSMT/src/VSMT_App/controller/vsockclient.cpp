#include "vsockclient.hpp"
#include <linux/virtio_vsock.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>
#include <unistd.h>
#include "metricserializer.hpp"

namespace vsock
{

VSockClient::VSockClient(const Address &address, QObject *parent) :
    QObject{parent}, socket()
{
    QObject::connect(&socket,&VSocket::messageReceived,this,&VSockClient::onMessageReceived);
    socket.connect(address);
}

VSockClient::~VSockClient()
{
    socket.disconnect();
}

void VSockClient::manualDisconnect()
{
    socket.disconnect();
}

void VSockClient::onMessageReceived(std::shared_ptr<Message> msg)
{
    metrics::Metric metric = metrics::serialization::deserialize(msg->getDataStream());
    if(metric.valid())
        emit metricReceived(metric);
}

}
