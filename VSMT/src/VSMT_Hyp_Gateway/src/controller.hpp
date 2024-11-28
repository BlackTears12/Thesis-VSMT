#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "vmgateway.hpp"

#include <QObject>
#include <QCoreApplication>
#include <QtNetwork/QTcpServer>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    void startExecution();
private slots:
    void onReadyRead();
    void onPendigConnectionAvailable();

    void onClientConnected(common::client_id id,Connection conn);
    void onClientConnectionFailed(common::client_id id,ConnectionStatus status);
    void onClientDisconnected(common::client_id id);
    void onMetricReceived(common::client_id id,shared_ptr<metrics::RuntimeMetric> metric);
private:
    void sendToMonitor(const Response &resp);
    void handleRequest(Request &req);

    QTcpServer server;
    QTcpSocket* monitorConnection;
    VMGateway gateway;
    QMutex socketMutex;
};
#endif // CONTROLLER_HPP
