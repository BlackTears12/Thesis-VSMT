#ifndef RANGEMODEL_HPP
#define RANGEMODEL_HPP

#include <QObject>

namespace circular_gauge
{

class RangeModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged USER true)
    Q_PROPERTY(qreal minimumValue READ minimum CONSTANT)
    Q_PROPERTY(qreal maximumValue READ maximum CONSTANT)
    Q_PROPERTY(qreal stepSize READ stepSize CONSTANT)
public:        
    qreal stepSize() const { return 1; }
    qreal minimum() const { return 0; }
    qreal maximum() const { return 100; }

    qreal value() const { return currentValue; }
    void setValue(qreal val);
signals:
    void valueChanged(qreal value);
    void activated();
protected:
    explicit RangeModel(QObject *parent = nullptr) : currentValue(0) {}
    qreal currentValue;
};

inline void RangeModel::setValue(qreal val)
{
    if(val >= minimum() && val <= maximum() && val != currentValue) {
        currentValue = val;
        emit valueChanged(currentValue);
    }
}

}

#endif // RANGEMODEL_HPP
