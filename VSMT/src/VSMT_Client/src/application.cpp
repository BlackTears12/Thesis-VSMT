#include "application.h"
#include <unistd.h>

Applicaton::Applicaton(int& argc,char** argv)
    : QCoreApplication{argc,argv},
    server(9999)
{
    QObject::connect(&server,&VSockSingletonServer::clientConnected,this,&Applicaton::onHypervisorConnected);
    QObject::connect(&server,&VSockSingletonServer::clientDisconnected,this,[this]() {
        timer.stop();
        qDebug() << "Hypervisor monitoring tool disconnected";
    });

    QObject::connect(&timer,&QTimer::timeout,this,&Applicaton::sendRuntimeMetric);
    timer.setSingleShot(false);
    timer.setInterval(1000);
}

Applicaton::~Applicaton()
{
}

int Applicaton::exec()
{
    return QCoreApplication::exec();
}

void Applicaton::sendRuntimeMetric()
{
    server.send(monitor.gatherRuntimeMetric());
}

void Applicaton::onHypervisorConnected()
{
    qDebug() << "Hypervisor monitoring tool connected";
    server.send(monitor.gatherSysInfo());
    timer.start();
}
