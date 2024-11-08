#ifndef PAGENAVIGATOR_HPP
#define PAGENAVIGATOR_HPP

#include <QObject>
#include "qmlsingleton.hpp"

namespace qml::adapters
{

using client_id = uint16_t;

class PageNavigator : public QObject, public QmlSingleton<PageNavigator>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(PageNavigator)
signals:
    /* Signals used in qml view */
    void mainPageRequested();
    void clientOverviewPageRequested();
    void clientCpuPageRequested();
    void clientMemoryPageRequested();
signals:
    void clientContextChanged(client_id newId);
public:
    void showMainPage() { emit mainPageRequested(); }
    void showClientCpuPage() { emit clientCpuPageRequested(); }
    void showClientMemoryPage() { emit clientMemoryPageRequested(); }

    void showClientOverviewPage(client_id id)
    {
        if(id != currentContext) {
            currentContext = id;
            emit clientContextChanged(id);
        }
        emit clientOverviewPageRequested();
    }
protected:
    explicit PageNavigator(QObject *parent = nullptr);
    client_id currentContext;
};

}

#endif // PAGENAVIGATOR_HPP
