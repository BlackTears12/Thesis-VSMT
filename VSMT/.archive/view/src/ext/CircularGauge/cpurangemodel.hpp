#ifndef CPURANGEMODEL_HPP
#define CPURANGEMODEL_HPP

#include <QObject>
#include "rangemodel.hpp"
#include "qmlsingleton.hpp"

namespace circular_gauge
{

class CpuRangeModel : public RangeModel, public qml::QmlSingleton<CpuRangeModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(CpuRangeModel)
public:

protected:
    explicit CpuRangeModel(QObject *parent = nullptr) : RangeModel(parent) {}
};


}
#endif // CPURANGEMODEL_HPP
