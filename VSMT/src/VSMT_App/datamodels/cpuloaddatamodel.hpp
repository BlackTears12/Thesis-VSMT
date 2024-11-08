#ifndef CPULOADDATAMODEL_H
#define CPULOADDATAMODEL_H

#include "coreloaddatamodel.hpp"
#include "lineargraphdatamodel.hpp"
#include "qmlsingleton.hpp"
#include "clientconfiguration.hpp"

namespace datamodels
{

using std::vector;
using common::client_id;

struct CpuLoadData
{
    CpuLoadData(size_t size)
    {
        coreLoads.resize(size);
        for(auto &e : coreLoads)
            e = new LinearGraphDataModel::GraphData();
    }
    CpuLoadData() = default;
    ~CpuLoadData() { for(auto &e : coreLoads) { delete e; } }

    LinearGraphDataModel::GraphData overallLoad;
    QVector<LinearGraphDataModel::GraphData*> coreLoads;
};

class CpuLoadDataModel : public LinearGraphDataModel, public qml::QmlSingleton<CpuLoadDataModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(CpuLoadDataModel)
public:
    void updateLoads(client_id id,double overallLoad,const vector<double> &coreLoads);
    void setContext(client_id id);
    void append(client_id id,size_t coreSize);
    void remove(client_id id);
protected:
    CpuLoadDataModel(QObject* parent=nullptr) : LinearGraphDataModel(parent) {}

    std::map<client_id,unique_ptr<CpuLoadData>> loadData;
    client_id context;
};

}
#endif // CPULOADDATAMODEL_H
