#ifndef VSOCKMESSAGE_HPP
#define VSOCKMESSAGE_HPP

#include <QBuffer>
#include <QDataStream>
#include <cstddef>
#include <memory>
#include <netinet/in.h>

namespace vsock
{

class Message
{
public:
    using header_t = uint32_t;

    Message(header_t header = MaxSize);

    QDataStream& getDataStream() { return dataStream; }

    void send(qint64 sock) const;
    bool isDisconnect() { return byteArray.size() == 0; }
private:
    QBuffer buffer;
    QByteArray byteArray;
    QDataStream dataStream;
public:
    static header_t fromNetwork(header_t header) { return ntohl(header); }
    static header_t toNetwork(header_t header) { return htonl(header); }
    static std::shared_ptr<Message> receive(qint64 sock);
    static const Message disconnectMessage;

    static constexpr size_t MaxSize = 1024;
    static constexpr size_t HeaderSize = sizeof(header_t);
};

}

#endif // VSOCKMESSAGE_HPP
