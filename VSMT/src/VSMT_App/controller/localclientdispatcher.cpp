#include "localclientdispatcher.hpp"

namespace comm
{

LocalClientDispatcher::LocalClientDispatcher(const ClientConfiguration &conf, milliseconds metricInt, QObject *parent) :
    ClientDispatcher(conf,parent),metricInterval(metricInt)
{
    /*
     * finalizeDispatcher should be called after the object is constructed
     * for that we need a 5ms timer
    */
    QObject::connect(&intervalTimer,&QTimer::timeout,this,&LocalClientDispatcher::finalizeDispatcher);
    intervalTimer.setInterval(milliseconds(5));
    intervalTimer.setSingleShot(true);
    intervalTimer.start();
}

void LocalClientDispatcher::finalizeDispatcher()
{
    emit clientConnected(resourceMonitor.gatherSysInfo());

    QObject::disconnect(&intervalTimer,&QTimer::timeout,this,&LocalClientDispatcher::finalizeDispatcher);
    QObject::connect(&intervalTimer,&QTimer::timeout,this,&LocalClientDispatcher::onMetricDue);
    intervalTimer.setInterval(metricInterval);
    intervalTimer.setSingleShot(false);
    intervalTimer.start();
}

void LocalClientDispatcher::onMetricDue()
{
    emit runtimeMetricReceived(resourceMonitor.gatherRuntimeMetric());
}


}
