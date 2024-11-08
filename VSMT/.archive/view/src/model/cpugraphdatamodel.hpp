#ifndef CPUGRAPHDATAMODEL_HPP
#define CPUGRAPHDATAMODEL_HPP

#include "lineargraphdatamodel.hpp"
#include "qmlsingleton.hpp"

namespace datamodels
{

class CpuGraphDataModel : public LinearGraphDataModel, public qml::QmlSingleton<CpuGraphDataModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(CpuGraphDataModel)
protected:
    CpuGraphDataModel(QObject* parent=nullptr) : LinearGraphDataModel(parent){}
};

}
#endif // CPUGRAPHDATAMODEL_HPP
