#ifndef STORAGEDATAMODEL_H
#define STORAGEDATAMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "clientconfiguration.hpp"
#include "qmlsingleton.hpp"
#include "metrics.hpp"

namespace datamodels
{

using metrics::StorageInfo;
using common::client_id;

class StorageDataModel : public QAbstractListModel, public qml::QmlSingleton<StorageDataModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(StorageDeviceModel)

    enum Roles {
        NameRole = Qt::DisplayRole+1,
        FSTypeRole,
        DeviceRole,
        TotalBytesRole,
        FreeBytesRole,
        UsedPercentRole
    };
public:
    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;
public:
    void updateLoads(client_id id,double memoryLoad,double diskLoad);
    void updateDevices(client_id id,const QVector<StorageInfo> &info);

    void append(client_id id) { infos.emplace(id,QVector<StorageInfo>{}); }
    void remove(client_id id);

    void setContext(client_id id);
protected:
    void refreshView();
    explicit StorageDataModel(QObject* parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;

    std::map<client_id,QVector<StorageInfo>> infos;
    client_id context = 0;
};

}

#endif // STORAGEDATAMODEL_H
