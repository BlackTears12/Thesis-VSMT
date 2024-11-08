#ifndef VSOCKMANAGER_H
#define VSOCKMANAGER_H

#include <QThread>

namespace vsock
{

using std::exception;

struct ConnectionError : public exception
{
    ConnectionError(const std::string &errMsg) : error(errMsg){}
    std::string error;
};

using std::array;
typedef array<char,16> Data;

/*
 * Manages a vsocket to conform to the qt signal/slot framework
*/
class VSockManager : public QObject
{
    Q_OBJECT
public:
    explicit VSockManager(int cid_,int port_,QObject *parent = nullptr);
    ~VSockManager();
signals:
    void dataReceived(Data &message);
public slots:
    int send(const Data &message);
private:
    void listen();

    int cid;
    int port;
    int sock;
    bool listening;
    std::thread listenThr;
};

}

#endif //VSOCKMANAGER_H
