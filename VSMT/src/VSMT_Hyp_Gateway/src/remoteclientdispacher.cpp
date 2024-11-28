#include "remoteclientdispacher.hpp"

namespace comm
{

RemoteClientDispatcher::RemoteClientDispatcher(const ClientConfiguration &conf, seconds timeout, QObject *parent) :
    ClientDispatcher{conf,parent},client(conf.address)
{
    QObject::connect(&client,&VSockClient::metricReceived,this,&RemoteClientDispatcher::onMetricReceived);
    QObject::connect(&timeoutTmr,&QTimer::timeout,this,&RemoteClientDispatcher::clientTimedOut);
    timeoutTmr.setInterval(timeout);
    timeoutTmr.setSingleShot(true);
}

void RemoteClientDispatcher::onMetricReceived(metrics::Metric metric)
{
    switch(metric.getType()){
    case Metric::RuntimeMetricRequest:
        timeoutTmr.start();
        emit runtimeMetricReceived(config.id,metric.asRuntimeMetric());
        break;
    case Metric::SystemInfoRequest:
        timeoutTmr.start();
        emit clientConnected(config.id,metric.asSysInfo());
        break;
    default:
        return;
    }
}

}
