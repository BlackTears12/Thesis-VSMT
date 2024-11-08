#ifndef VSOCKSINGLETONSERVER_HPP
#define VSOCKSINGLETONSERVER_HPP

#include "vsocket.hpp"
#include <QObject>
#include <QDataStream>
#include <metrics.hpp>

namespace vsock
{
/* Runs a separate thread to listen for connections on port */
class ServerWorker : public QThread
{
    Q_OBJECT
public:
    ServerWorker(QObject* parent = nullptr);
    void setSocketDescriptor(unsigned int sock);

    void run() override;
signals:
    void clientConnected(qint64 socket);
private:
    unsigned int sock;
};

/* Creates a server on the port which only accepts a single client */
class VSockSingletonServer : public QObject
{
    Q_OBJECT
public:
    explicit VSockSingletonServer(unsigned int port,QObject *parent = nullptr);
    ~VSockSingletonServer();

    void send(const metrics::Metric &metric);
    void send(unique_ptr<metrics::RuntimeMetric> rtInfo);
    void send(unique_ptr<metrics::SystemInfo> sysInfo);
signals:
    void clientConnected();
    void clientDisconnected();
private slots:
    void onClientConnected(qintptr socket);
    void onClientDisconnected();
private:
    unique_ptr<VSocket> socketDevice;
    ServerWorker worker;
    qint64 sock;
};

}
#endif // VSOCKSINGLETONSERVER_HPP
