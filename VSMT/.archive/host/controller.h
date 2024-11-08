#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>
#include <string>
#include "model.h"
#include "clientdispatcher.h"

using comm::ClientDispatcher;
using model::Model;
using std::vector;
using std::string;
using std::map;
using std::unique_ptr;
using std::shared_ptr;
using comm::Connection;
using model::UnknownClientException;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    int exec(int &argc,char** argv);
    void simulate();
public slots:
    void handleConnection(comm::client_id_t id);
    void requestRuntimeMetric(comm::client_id_t id);
    void requestSystemInfo(comm::client_id_t id);
public slots:
    void getAppConfig();    

///signals for client handling
signals:
    void clientUnresponsive(comm::client_id_t id);
    void runtimeMetricReceived(comm::client_id_t id,shared_ptr<metrics::RuntimeMetric> metric);
    void systemInfoReceived(comm::client_id_t id,shared_ptr<metrics::SystemInfo> metric);
private:
    void setupClient(unique_ptr<ClientDispatcher> &client);
    unique_ptr<ClientDispatcher>& getDispatcher(comm::client_id_t id);
private:
    map<comm::client_id_t,unique_ptr<ClientDispatcher>> clients;
    Model model;
};

#endif // CONTROLLER_H
