#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <thread>
#include "clientstatusmodel.hpp"
#include "memoryrangemodel.hpp"
#include "pagenavigator.hpp"
#include "cpurangemodel.hpp"
#include "menubarmodel.hpp"
#include "cpugraphdatamodel.hpp"
#include "processtablemodel.hpp"

using namespace qml::adapters;
using namespace datamodels;
using circular_gauge::CpuRangeModel;
using circular_gauge::MemoryRangeModel;

/*
    A singelton class which controls the GUI
*/
class View : public QObject
{
    Q_OBJECT
public:
    explicit View(QObject *parent = nullptr);

    void TEST() {
        std::thread runner { [this](){ this->__tester__(); } };
        runner.detach();
    }

    void __tester__(){
        while(true) {
            cpuGraphModel.push(rand()%100);
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
signals:
private:
    QQmlApplicationEngine qmlEngine;
    ClientStatusModel& sideBarModel;
    PageNavigator& navigator;
    CpuRangeModel& cpuUsageModel;
    MemoryRangeModel& memoryUsageModel;
    MenubarModel& menubarModel;
    CpuGraphDataModel& cpuGraphModel;
    ProcessTableModel& processModel;
};

#endif // VIEW_H
