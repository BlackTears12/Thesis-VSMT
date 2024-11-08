#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QWidget>
#include <QtQuickWidgets/QtQuickWidgets>

class GaugeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GaugeWidget(QWidget *parent = nullptr);
    void
signals:


private:
    QQuickWidget *speedometer;
};

#endif // GAUGEWIDGET_H
