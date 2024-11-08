#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <vector>
#include <string>
#include <pagenavigator.hpp>
#include "clientdispatcher.hpp"
#include "clientconfiglistmodel.hpp"
#include "clientviewcontroller.hpp"
#include "clientconnector.hpp"

namespace core
{

using comm::ClientDispatcher;
using comm::ClientConnector;
using comm::ConnectionStatus;
using qml::viewcontrollers::PageNavigator;
using std::vector;
using std::string;
using std::map;
using std::unique_ptr;
using std::shared_ptr;
using common::client_id;

using datamodels::ClientConfigListModel;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    void startExecution();
public slots:
    void handleConnection(client_id id);
    void handleConfigDelete(client_id id);
    void handleDisconnectRequest(client_id id);
    void setClientIntoContext(client_id id);

    void onClientConnectionSuccess(ConnectionStatus status,Connection conn);
    void onClientConnectionFailed(ConnectionStatus status,client_id id);
    void onConnectedClientTimedOut(client_id id);
private:
    void removeClient(client_id id,ConnectionStatus status);
    unique_ptr<ClientViewController>& getViewController(client_id id);

    map<client_id,unique_ptr<ClientViewController>> clients;
    ClientConnector connector;
};

}

#endif // CONTROLLER_HPP
