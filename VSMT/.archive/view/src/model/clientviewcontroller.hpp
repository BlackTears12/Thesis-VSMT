#ifndef CLIENTVIEWCONTROLLER_HPP
#define CLIENTVIEWCONTROLLER_HPP

#include <QObject>
#include "clientstatusmodel.hpp"
#include "memoryrangemodel.hpp"
#include "pagenavigator.hpp"
#include "cpurangemodel.hpp"
#include "menubarmodel.hpp"
#include "cpugraphdatamodel.hpp"
#include "processtablemodel.hpp"

using namespace datamodels;

class ClientViewController : public QObject
{
    Q_OBJECT
public:
    explicit ClientViewController(QObject *parent = nullptr);

signals:
protected:
    LinearGraphDataModel::GraphData memoryGraphData;
    LinearGraphDataModel::GraphData cpuGraphData;
    CpuGraphDataModel* cpuGraph;
};


class HostViewController : public ClientViewController
{

};

#endif // CLIENTVIEWCONTROLLER_HPP
