#ifndef CLIENTVIEWCONTROLLER_HPP
#define CLIENTVIEWCONTROLLER_HPP

#include <QObject>
#include <lineargraphdatamodel.hpp>
#include <networkinterfacemodel.hpp>
#include "clientconnector.hpp"
#include "clientdispatcher.hpp"

namespace core
{

using namespace datamodels;
using comm::ClientDispatcher;
using std::unique_ptr;
using std::shared_ptr;
using comm::client_id;
using std::vector;
using comm::Connection;

class ClientViewController : public QObject
{
    Q_OBJECT
public:
    explicit ClientViewController(Connection connection,QObject *parent = nullptr);
    ~ClientViewController();

    client_id getId() const { return connection.dispatcher->getId(); }
    void setContext() const;
signals:
    void timedOut(client_id id);
private slots:
    void onRuntimeMetricReceived(shared_ptr<metrics::RuntimeMetric> rtMetric);
protected:
    Connection connection;
};

}

#endif // CLIENTVIEWCONTROLLER_HPP
