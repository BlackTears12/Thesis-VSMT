#ifndef CLIENTDESCRIPTIONMODEL_HPP
#define CLIENTDESCRIPTIONMODEL_HPP

#include "clientdatacontainer.hpp"
#include "metrics.hpp"
#include <QAbstractListModel>
#include <QObject>
#include <qmlsingleton.hpp>

namespace datamodels
{

struct ClientDescriptionInfo
{
    QString name;
    metrics::SystemInfo info;
};

class ClientDescriptionModel : public QObject, public qml::QmlSingleton<ClientDescriptionModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(ClientDescriptionModel)

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString platform READ platform NOTIFY platformChanged)
    Q_PROPERTY(QString distribution READ distribution NOTIFY distributionChanged)
    Q_PROPERTY(QString cpuModel READ cpuModel NOTIFY cpuModelChanged)
    Q_PROPERTY(qint32 cpuCores READ cpuCores NOTIFY cpuCoresChanged)
    Q_PROPERTY(QString cpuSpeed READ cpuSpeed NOTIFY cpuSpeedChanged)
public:
    QString name() const { return infos.context().name; }
    QString platform() const { return infos.context().info.platform; }
    QString distribution() const { return infos.context().info.distribution; }
    QString cpuModel() const { return infos.context().info.cpuInfo.model; }
    qint32 cpuCores() const { return infos.context().info.cpuInfo.cores; }
    QString cpuSpeed() const { return infos.context().info.cpuInfo.speed; }

    void append(client_id id,ClientDescriptionInfo info) { infos.append(id,info); }
    void remove(client_id id);
    void update(client_id id,const ClientDescriptionInfo &info);
    void setContext(client_id id) { infos.setContext(id); emitDataChanged(); }
signals:
    void nameChanged();
    void platformChanged();
    void distributionChanged();
    void cpuModelChanged();
    void cpuCoresChanged();
    void cpuSpeedChanged();
protected:
    explicit ClientDescriptionModel(QObject *parent = nullptr) : QObject{parent} {}
    void emitDataChanged();

    ClientDataContainer<ClientDescriptionInfo> infos;
};

}

#endif // CLIENTDESCRIPTIONMODEL_HPP
