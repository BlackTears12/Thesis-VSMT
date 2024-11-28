#include "controller.hpp"
#include "controller.hpp"
#include "blockreader.hpp"
#include "blockwriter.hpp"
#include <QTcpSocket>

Controller::Controller(QObject* parent): QObject(parent)
{
    QObject::connect(&server,&QTcpServer::newConnection,this,&Controller::onPendigConnectionAvailable);
    QObject::connect(&gateway,&VMGateway::clientConnected,this,&Controller::onClientConnected);
    QObject::connect(&gateway,&VMGateway::clientConnectionFailed,this,&Controller::onClientConnectionFailed);
    QObject::connect(&gateway,&VMGateway::clientDisconnected,this,&Controller::onClientDisconnected);
    QObject::connect(&gateway,&VMGateway::metricReceived,this,&Controller::onMetricReceived);
}

void Controller::startExecution()
{
    if(!server.listen(QHostAddress::Any,HYPERVISOR_TCP_PORT)) {
        throw std::exception();
    }
}

void Controller::onReadyRead()
{
    Request req;
    BlockReader(monitorConnection).stream() >> req;
    handleRequest(req);
}

void Controller::onPendigConnectionAvailable()
{
    monitorConnection = server.nextPendingConnection();
    qDebug() << "CONNECTED TO MONITOR";
    QObject::connect(monitorConnection,&QTcpSocket::disconnected,[this](){
        this->server.listen(QHostAddress::AnyIPv4,HYPERVISOR_TCP_PORT);
    });
    QObject::connect(monitorConnection,&QTcpSocket::readyRead,[this](){
        onReadyRead();
    });
    gateway.attemptLocalConnection();
    server.close();
}

void Controller::onClientConnected(common::client_id id, Connection conn)
{
    Response resp;
    resp.id = id;
    resp.metric = std::make_shared<metrics::Metric>(conn.systemInfo,metrics::Metric::SystemInfoRequest);
    resp.type = Response::Connected;
    resp.status = ConnectionStatus {
        .status = ConnectionStatus::Alive,
        .message = "Connected"
    };
    qDebug() << "sending sysinfo";
    sendToMonitor(resp);
    qDebug() << "sysinfo sent";
}

void Controller::onClientConnectionFailed(common::client_id id, ConnectionStatus status)
{
    Response resp;
    resp.id = id;
    resp.status = status;
    resp.type = Response::ConnectFailed;
    sendToMonitor(resp);
}

void Controller::onClientDisconnected(common::client_id id)
{
    Response resp;
    resp.id = id;
    resp.status = {
        .status = ConnectionStatus::TimedOut,
        .message = "Client timed out"
    };
    resp.type = Response::Disconnected;
    sendToMonitor(resp);
    qDebug() << "sent disconnected";
}

void Controller::onMetricReceived(common::client_id id, shared_ptr<metrics::RuntimeMetric> metric)
{
    Response resp;
    resp.id = id;
    resp.metric = std::make_shared<metrics::Metric>(metric,metrics::Metric::RuntimeMetricRequest);
    resp.status = {
        .status = ConnectionStatus::Alive
    };
    resp.type = Response::MetricReceived;
    qDebug() << "metric sending";
    sendToMonitor(resp);
    qDebug() << "metric sent";
}

void Controller::sendToMonitor(const Response &resp)
{
    socketMutex.lock();
    BlockWriter(monitorConnection).stream() << resp;
    socketMutex.unlock();
}

void Controller::handleRequest(Request &req)
{
    switch (req.type) {
    case Request::Connect:
        qDebug() << req.id;
        gateway.attemptRemoteConnection(req.address,req.id);
        break;
    case Request::Disconnect:
        gateway.disconnectFrom(req.id);
        break;
    }
}
