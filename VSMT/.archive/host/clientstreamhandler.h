#ifndef CLIENTSTREAMHANDLER_H
#define CLIENTSTREAMHANDLER_H

#include <QObject>
#include <QTimer>
#include <set>
#include <mutex>
#include "../common/vsockmanager.h"
#include "../common/metrics.h"

namespace comm
{
using vsock::VSockManager;
using std::set;
using std::map;

class PendingRequestException : std::exception{};

/*
 * Handles the client vsock communication uncertainty, by resending request if no response is received
 * A request has to be sent than when a valid response is received has to be acknowledged
*/
class ClientStreamHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientStreamHandler(unsigned int cid,unsigned int port,unsigned int respTimeoutS,
                                 unsigned int maxReqResend,QObject *parent = nullptr);
    ~ClientStreamHandler();
    void send(const vsock::Data &data,metrics::metricid_t id);
    void acknowledge(metrics::metricid_t id);
    void cancelRequest(metrics::metricid_t id);
signals:
    void dataReceived(const vsock::Data &data);
    /* Gets emited if the client timeouts maxRequestResend times on @id request*/
    void noResponseSignal(metrics::metricid_t id);
private slots:
    /* Occours every time the timeout timer signals */
    void responseTimeout();
    void onDataReceived(const vsock::Data &data);
private:
    struct PendingRequestData
    {
        metrics::metricid_t id;
        vsock::Data data;
        uint8_t sendCtr = 0;
    };
private:
    VSockManager sockManager;
    unsigned int maxRequestResend;
    unsigned int responseTimeoutSec;
    QTimer timer;
    set<metrics::metricid_t> pendingRequests;
    map<metrics::metricid_t,PendingRequestData> pendingRequestLookup;
    std::mutex pendingRequestMutex;
};

}

#endif // CLIENTSTREAMHANDLER_H
