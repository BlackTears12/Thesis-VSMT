#include "clientviewcontroller.hpp"

#include <application.hpp>
#include <clientstatusmodel.hpp>

namespace core
{

ClientViewController::ClientViewController(Connection conn,QObject *parent):
    QObject{parent},connection(conn)
{
    QObject::connect(conn.dispatcher.get(),&ClientDispatcher::runtimeMetricReceived,this,&ClientViewController::onRuntimeMetricReceived);
    QObject::connect(conn.dispatcher.get(),&ClientDispatcher::clientTimedOut,this,[this](){
        emit timedOut(this->getId());
    });
    auto conf = Application::Instance().getClientConfig(getId());
    Application::Instance().getCpuGraphModel().append(conf.id,conn.systemInfo->cpuInfo.cores);
    Application::Instance().getStorageDeviceModel().append(conf.id);
    Application::Instance().getNetworkInterfaceModel().append(conf.id);
    Application::Instance().getProcessTable().append(conf.id);
    Application::Instance().getClientDescriptor().append(conf.id,{conf.name,*conn.systemInfo});
    Application::Instance().getStatusModel().add({conf.id,conf.name,0,0});
}

ClientViewController::~ClientViewController()
{
    if(connection.dispatcher->getId() == common::ClientConfiguration::hostId())
        return;
    auto id = connection.dispatcher->getId();
    Application::Instance().getCpuGraphModel().remove(id);
    Application::Instance().getStorageDeviceModel().remove(id);
    Application::Instance().getClientDescriptor().remove(id);
    Application::Instance().getNetworkInterfaceModel().remove(id);
    Application::Instance().getProcessTable().remove(id);
    Application::Instance().getStatusModel().remove(id);
}

void ClientViewController::setContext() const
{
    auto id = connection.dispatcher->getId();
    Application::Instance().getCpuGraphModel().setContext(id);
    Application::Instance().getStorageDeviceModel().setContext(id);
    Application::Instance().getNetworkInterfaceModel().setContext(id);
    Application::Instance().getProcessTable().setContext(id);
    Application::Instance().getClientDescriptor().setContext(id);
    Application::Instance().getNavigator().showClientOverviewPage(id);
}

void ClientViewController::onRuntimeMetricReceived(shared_ptr<metrics::RuntimeMetric> rtMetric)
{
    QVector<ProcessEntry> entries;
    entries.reserve(rtMetric->processes.size());
    for(auto& proc: rtMetric->processes) {
        entries.append(ProcessEntry(proc));
    }

    auto id = connection.dispatcher->getId();
    Application::Instance().getCpuGraphModel().updateLoads(id,rtMetric->overallCpuLoad(),rtMetric->coreLoads);
    Application::Instance().getStorageDeviceModel().updateLoads(id,rtMetric->memory.usedPercent(),rtMetric->overallStorageLoad());
    Application::Instance().getStorageDeviceModel().updateDevices(id,
        QVector<metrics::StorageInfo>(rtMetric->storageInfo.begin(),rtMetric->storageInfo.end()));
    Application::Instance().getNetworkInterfaceModel().updateInterfaces(id,
        QVector<metrics::NetworkInterfaceInfo>(rtMetric->networkInfo.begin(),rtMetric->networkInfo.end()));
    Application::Instance().getProcessTable().update(id,entries);
    Application::Instance().getStatusModel().updateRtValues(id,rtMetric->overallCpuLoad(),rtMetric->memory.usedPercent());
}

}
