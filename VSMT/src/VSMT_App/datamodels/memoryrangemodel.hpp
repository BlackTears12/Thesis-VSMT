#ifndef MEMORYRANGEMODEL_HPP
#define MEMORYRANGEMODEL_HPP

#include <QObject>
#include "rangemodel.hpp"
#include "qmlsingleton.hpp"

namespace circular_gauge
{

class MemoryRangeModel : public RangeModel, public qml::QmlSingleton<MemoryRangeModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(MemoryRangeModel)
public:

protected:
    explicit MemoryRangeModel(QObject *parent = nullptr) : RangeModel(parent) {}
};


}

#endif // MEMORYRANGEMODEL_HPP
