#ifndef VSOCKET_HPP
#define VSOCKET_HPP

#include "vsockmessage.hpp"

#include <QThread>
#include <exception>
#include <string>

namespace vsock
{

struct Address
{
    enum class CID {
        Any = -1,
        Hypervisor = 0,
        Reserved = 1,
        Host = 2
    };

    enum class Port {
        Any = -1
    };

    uint32_t cid;
    uint32_t port;

    Address(uint32_t cid_,uint32_t port_):
        cid(cid_), port(port_) {}
};

using std::exception;

struct ConnectionError : public exception
{
    ConnectionError(const std::string &errMsg) : error(errMsg){}
    virtual const char* what() const throw() { return error.c_str(); }

    std::string error;
};

using std::unique_ptr;

class VSockListener : public QThread
{
    Q_OBJECT
public:
    VSockListener(QObject* parent);

    void setSocketDescriptor(unsigned int sock);
    void run() override;
signals:
    void messageReceived(std::shared_ptr<Message> msg);
    void socketDisconnected();
private:
    unsigned int sock;
};

class VSocket : public QObject
{
    Q_OBJECT
public:    
    VSocket(QObject* parent = nullptr);
    ~VSocket();
    void connect(const Address &address);

    void sendMessage(const Message &msg);
    void disconnect();
signals:
    void messageReceived(std::shared_ptr<Message> msg);
    void disconnected();
private:
    void finalize();
private slots:
    void onDisconnect();
private:
    qintptr sock;
    VSockListener listener;
public:
    /* wraps an already opended client socket */
    static unique_ptr<VSocket> wrapSocket(qintptr socket);
};



}

#endif // VSOCKET_HPP
