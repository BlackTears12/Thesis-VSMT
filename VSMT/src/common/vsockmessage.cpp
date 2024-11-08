#include "vsockmessage.hpp"
#include <qdebug.h>
#include <unistd.h>

namespace vsock
{

Message::Message(header_t h): byteArray(h,Qt::Initialization::Uninitialized)
{
    buffer.setBuffer(&byteArray);
    buffer.open(QIODevice::ReadWrite);
    dataStream.setDevice(&buffer);
}

void Message::send(qint64 sock) const
{
    header_t netHeader = toNetwork(byteArray.size());
    ::send(sock,&netHeader,HeaderSize,MSG_NOSIGNAL);
    ::send(sock,byteArray.data(),byteArray.size(),MSG_NOSIGNAL);
}

std::shared_ptr<Message> Message::receive(qint64 sock)
{
    header_t header;
    size_t size = ::recv(sock,&header,HeaderSize,MSG_NOSIGNAL);
    if(size < HeaderSize)
        return nullptr;
    header = fromNetwork(header);
    auto msg = std::make_shared<Message>(header);
    /* if the read amount is equal to the message size or is a disconnect msg return*/
    if(::recv(sock,msg->byteArray.data(),header,0) == header || header == 0)
        return msg;
    return nullptr;
}

const Message Message::disconnectMessage{0};

}
