#ifndef DISKRANGEMODEL_H
#define DISKRANGEMODEL_H

#include <QObject>
#include "rangemodel.hpp"
#include "qmlsingleton.hpp"

namespace circular_gauge
{

class DiskRangeModel : public RangeModel, public qml::QmlSingleton<DiskRangeModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(DiskRangeModel)
public:
protected:
    explicit DiskRangeModel(QObject *parent = nullptr) : RangeModel(parent) {}

};


}
#endif // DISKRANGEMODEL_H
