#include "application.hpp"
#include "controller.hpp"

namespace core
{

int Application::startExecution()
{
    const QUrl url("qrc:/view/AppWindow.qml");
    qmlEngine.load(url);
    navigator.showMainPage();
    controller.startExecution();
    return exec();
}

const ClientConfiguration Application::getClientConfig(common::client_id id)
{
    auto res = configModel.searchForClientConfig(id);
    if(res)
        return *res;
    throw UnknownClientException();
}

QFile Application::getSavedConfigFile() const
{
    return QFile("configs.xml");
}

void Application::onWindowCreationFailed()
{
    qDebug() << "Cannot load application window";
    qDebug() << "Exiting...";
    exit();
}

Application::Application(int &argc, char **argv) :
    QApplication(argc,argv),
    navigator(*PageNavigator::create(&qmlEngine,&qmlEngine)),
    configModel(*ClientConfigListModel::create(&qmlEngine,&qmlEngine)),
    statusModel(*ClientStatusModel::create(&qmlEngine,&qmlEngine)),
    cpuRangeModel(*CpuRangeModel::create(&qmlEngine,&qmlEngine)),
    memoryRangeModel(*MemoryRangeModel::create(&qmlEngine,&qmlEngine)),
    diskRangeModel(*DiskRangeModel::create(&qmlEngine,&qmlEngine)),
    processTable(*ProcessTableModel::create(&qmlEngine,&qmlEngine)),
    clientDescriptor(*ClientDescriptionModel::create(&qmlEngine,&qmlEngine)),
    cpuLoadModel(*CpuLoadDataModel::create(&qmlEngine,&qmlEngine)),
    coreLoadProvider(*CoreLoadDataModelProvider::create(&qmlEngine,&qmlEngine)),
    storageDeviceModel(*StorageDataModel::create(&qmlEngine,&qmlEngine)),
    networkInterfaceModel(*NetworkInterfaceModel::create(&qmlEngine,&qmlEngine))
{
    QObject::connect(&qmlEngine,&QQmlApplicationEngine::objectCreationFailed,this,&Application::onWindowCreationFailed);
    QObject::connect(&configModel,&ClientConfigListModel::configConnectClicked,&controller,&Controller::handleConnection);
    QObject::connect(&configModel,&ClientConfigListModel::deleteConfigClicked,&controller,&Controller::handleConfigDelete);
    QObject::connect(&statusModel,&ClientStatusModel::itemTriggered,&controller,&Controller::setClientIntoContext);
    QObject::connect(&navigator,&PageNavigator::clientDisconnectRequested,&controller,&Controller::handleDisconnectRequest);

    QObject::connect(&cpuRangeModel,&CpuRangeModel::activated,&navigator,&PageNavigator::showClientCpuPage);
    QObject::connect(&memoryRangeModel,&MemoryRangeModel::activated,&navigator,&PageNavigator::showClientMemoryPage);
    QObject::connect(&diskRangeModel,&DiskRangeModel::activated,&navigator,&PageNavigator::showClientDiskPage);
}

void Application::Init(int &argc, char **argv)
{
    instance = std::unique_ptr<Application>(new Application(argc,argv));
}

void Application::registerMetatypes()
{
    qRegisterMetaType<common::client_id>("common::client_id");
    qRegisterMetaType<shared_ptr<metrics::RuntimeMetric>>("shared_ptr<metrics::RuntimeMetric>");
}

unique_ptr<Application> Application::instance = nullptr;

}
