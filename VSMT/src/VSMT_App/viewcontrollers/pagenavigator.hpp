#ifndef PAGENAVIGATOR_HPP
#define PAGENAVIGATOR_HPP

#include <QObject>
#include "qmlsingleton.hpp"

namespace qml::viewcontrollers
{

using client_id = uint16_t;

class PageNavigator : public QObject, public QmlSingleton<PageNavigator>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(PageNavigator)

    Q_PROPERTY(client_id clientContext READ clientContext NOTIFY clientContextChanged)
signals:
    /* Signals used in qml view */
    void mainPageRequested();
    void clientOverviewPageRequested();
    void clientCpuPageRequested();
    void clientDiskPageRequested();
    void clientMemoryPageRequested();
    void clientNetworkPageRequested();
    void requestDisconnect();
    void openClientConfigPageRequested();
    void closeClientConfigPageRequested();
signals:
    void clientContextChanged(client_id newId);
signals:
    void clientDisconnectRequested(client_id id);
public:
    void showClientOverviewPage(client_id id);
    void showMainPage() { emit mainPageRequested(); }
    void showClientCpuPage() { emit clientCpuPageRequested(); }
    void showClientMemoryPage() { emit clientMemoryPageRequested(); }
    void showClientDiskPage() { emit clientDiskPageRequested(); }
    void showClientNetworkPage() { emit clientNetworkPageRequested(); }
    void openClientConfigPage() { emit openClientConfigPageRequested(); }
    void closeClientConfigPage() { emit closeClientConfigPageRequested(); }
    int clientContext() const;
    void registerContext(client_id context) { currentContext = context; emit clientContextChanged(currentContext); }

protected:
    explicit PageNavigator(QObject *parent = nullptr);
    client_id currentContext;
};

}

#endif // PAGENAVIGATOR_HPP
