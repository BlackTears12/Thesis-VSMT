#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "coreloaddatamodel.hpp"
#include <QApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <clientconfigmodel.hpp>
#include <clientdescriptionmodel.hpp>
#include <clientstatusmodel.hpp>
#include <controller.hpp>
#include <cpuloaddatamodel.hpp>
#include <cpurangemodel.hpp>
#include <diskrangemodel.hpp>
#include <memory>
#include <memoryrangemodel.hpp>
#include <pagenavigator.hpp>
#include <processtablemodel.hpp>
#include <storagedatamodel.hpp>

namespace core
{

using qml::viewcontrollers::PageNavigator;

using std::unique_ptr;
using std::shared_ptr;

class UnknownClientException : std::exception{};

struct AppConfig
{
    string configDirectory;
};

using circular_gauge::CpuRangeModel;
using circular_gauge::DiskRangeModel;
using circular_gauge::MemoryRangeModel;

class Application : public QApplication
{
    Q_OBJECT
public:
    int startExecution();

    QQmlApplicationEngine& getEngine() { return qmlEngine; }
    PageNavigator& getNavigator() { return navigator; }
    ClientConfigListModel& getConfigModel() { return configModel; }
    ClientStatusModel& getStatusModel() { return statusModel; }
    CpuRangeModel& getCpuRangeModel() { return cpuRangeModel; }
    MemoryRangeModel& getMemoryRangeModel() { return memoryRangeModel; }
    DiskRangeModel& getDiskRangeModel() { return diskRangeModel; }
    ProcessTableModel& getProcessTable() { return processTable; }
    ClientDescriptionModel& getClientDescriptor() { return clientDescriptor; }
    CpuLoadDataModel& getCpuGraphModel() { return cpuLoadModel; }
    CoreLoadDataModelProvider& getCoreLoadProvider() { return coreLoadProvider; }
    StorageDataModel& getStorageDeviceModel() { return storageDeviceModel; }
    NetworkInterfaceModel& getNetworkInterfaceModel() { return networkInterfaceModel; }

    const ClientConfiguration getClientConfig(client_id id);
    QFile getSavedConfigFile() const;
private slots:
    void onWindowCreationFailed();
private:
    Application(int &argc,char** argv);

    QQmlApplicationEngine qmlEngine;
    PageNavigator& navigator;
    ClientConfigListModel& configModel;
    ClientStatusModel& statusModel;
    CpuRangeModel& cpuRangeModel;
    MemoryRangeModel& memoryRangeModel;
    DiskRangeModel& diskRangeModel;
    ProcessTableModel& processTable;
    ClientDescriptionModel& clientDescriptor;
    CpuLoadDataModel& cpuLoadModel;
    CoreLoadDataModelProvider& coreLoadProvider;
    StorageDataModel& storageDeviceModel;
    NetworkInterfaceModel& networkInterfaceModel;

    AppConfig config;
    Controller controller;
public:
    static void Init(int &argc,char** argv);
    static Application& Instance() { return *instance; }
private:
    static void registerMetatypes();

    static unique_ptr<Application> instance;

};

}

#endif // APPLICATION_HPP
