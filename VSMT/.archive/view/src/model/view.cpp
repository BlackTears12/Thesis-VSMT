#include "view.hpp"


View::View(QObject *parent)
    : QObject{parent},
    sideBarModel(*ClientStatusModel::create(&qmlEngine,&qmlEngine)),
    navigator(*PageNavigator::create(&qmlEngine,&qmlEngine)),
    cpuUsageModel(*CpuRangeModel::create(&qmlEngine,&qmlEngine)),
    memoryUsageModel(*MemoryRangeModel::create(&qmlEngine,&qmlEngine)),
    menubarModel(*MenubarModel::create(&qmlEngine,&qmlEngine)),
    cpuGraphModel(*CpuGraphDataModel::create(&qmlEngine,&qmlEngine)),
    processModel(*ProcessTableModel::create(&qmlEngine,&qmlEngine))
{
    QObject::connect(&sideBarModel,&ClientStatusModel::itemTriggered,&navigator,&PageNavigator::clientOverviewPageRequested);
    QObject::connect(&cpuUsageModel,&CpuRangeModel::activated,&navigator,&PageNavigator::clientCpuPageRequested);
    QObject::connect(&memoryUsageModel,&MemoryRangeModel::activated,&navigator,&PageNavigator::clientMemoryPageRequested);

    QObject::connect(&menubarModel,&MenubarModel::decreaseCpu,this,[this](){
        cpuUsageModel.setValue(10);
        memoryUsageModel.setValue(10);
    });
    QObject::connect(&menubarModel,&MenubarModel::increaseCpu,this,[this](){
        cpuUsageModel.setValue(80);
        memoryUsageModel.setValue(80);
    });
    sideBarModel.add({"client",1.0,1.0});
    QVector<ProcessEntry> entries = {
        ProcessEntry{"A",10,50,"a"},
        ProcessEntry{"B",20,30,"b"},
        ProcessEntry{"C",70,10,"c"},
        ProcessEntry{"D",16,90,"d"}
    };
    processModel.update(entries);

    const QUrl url("qrc:/view/src/AppWindow.qml");
    //QObject::connect(&qmlEngine,&QQmlApplicationEngine::objectCreationFailed,this,&PageManager::pageCreationFailed);
    qmlEngine.load(url);
}

