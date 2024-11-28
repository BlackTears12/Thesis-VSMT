#ifndef VSOCKCLIENT_H
#define VSOCKCLIENT_H

#include <QDataStream>
#include <QThread>
#include "metrics.hpp"
#include "vsocket.hpp"

namespace vsock
{

using std::unique_ptr;

/*
 * Manages a vsocket to conform to the qt signal/slot framework
*/
class VSockClient : public QObject
{
    Q_OBJECT
public:
    explicit VSockClient(const Address &address,QObject *parent = nullptr);
    ~VSockClient();

    void manualDisconnect();
signals:
    void metricReceived(metrics::Metric metric);
private slots:
    void onMessageReceived(std::shared_ptr<Message> msg);
private:
    VSocket socket;
};

}

#endif //VSOCKCLIENT_H
