#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include "vsocksingletonserver.hpp"
#include "resourcemonitor.hpp"
#include "linux/resourcemonitor_linux.hpp"

using ResourceMonitor = metrics::monitor::ResourceMonitor<platform::current>;
using vsock::VSockSingletonServer;

class Applicaton : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Applicaton(int& argc,char** argv);
    ~Applicaton();
    int exec();

    void sendRuntimeMetric();
private slots:
    void onHypervisorConnected();
private:
    VSockSingletonServer server;
    ResourceMonitor monitor;
    QTimer timer;
};

#endif // APPLICATION_H
