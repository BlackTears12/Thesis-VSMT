#ifndef MAINPAGEADAPTER_HPP
#define MAINPAGEADAPTER_HPP

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "qmlsingleton.hpp"

namespace qml::adapters
{

class MainPageAdapter : public QObject, public QmlSingleton<MainPageAdapter>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(MainPageAdapter)
protected:
    explicit MainPageAdapter(QObject *parent = nullptr);
signals:

};

}
#endif // MAINPAGEADAPTER_HPP
