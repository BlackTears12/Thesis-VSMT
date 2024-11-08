#ifndef MENUBARMODEL_HPP
#define MENUBARMODEL_HPP

#include "qmlsingleton.hpp"

namespace qml::adapters
{

class MenubarModel : public QObject, public QmlSingleton<MenubarModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(MenubarModel)
signals:
    void increaseCpu();
    void decreaseCpu();
protected:
    MenubarModel(QObject* parent = nullptr): QObject{parent} {}
};

}

#endif // MENUBARMODEL_HPP
