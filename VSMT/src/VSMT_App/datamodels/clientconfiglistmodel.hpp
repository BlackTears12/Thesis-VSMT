#ifndef CLIENTCONFIGLISTMODEL_H
#define CLIENTCONFIGLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <clientconnector.hpp>
#include "clientconfigmodel.hpp"
#include "clientdatacontainer.hpp"
#include "contiguousclientmapper.hpp"
#include "qmlsingleton.hpp"

namespace datamodels
{

using comm::ConnectionStatus;

class ClientConfigListModel : public QAbstractListModel,public qml::QmlSingleton<ClientConfigListModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(ClientConfigListModel)

    enum Roles {
        IdRole = Qt::UserRole+1,
        NameRole,
        IsRemoteRole,
        StatusRole,
        StatusMessageRole
    };

    Q_PROPERTY(ClientConfigModel* context READ context NOTIFY contextChanged)
public:
    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;
    ClientConfigModel* context();
public:
    ~ClientConfigListModel() { saveConfigs(); }
    ClientConfiguration const* searchForClientConfig(client_id id);

    void updateConfig(const ClientConfiguration &config);
    void notifyClientStatusChanged(ConnectionStatus status,client_id id);
    void deleteConfig(client_id id);
signals:
    void contextChanged();
signals:
    void newConfigClicked();
    void configEditClicked(client_id index);
    void configConnectClicked(client_id index);
    void deleteConfigClicked(client_id index);

    void saveConfigClicked(QString newName,QString newCid,QString newPort);
    void revertConfigClicked();
private slots:
    void onNewConfigClicked();
    void onConfigEditClicked(client_id id);
    void onSaveConfigClicked(QString newName,QString newCid,QString newPort);
    void onRevertConfigClicked();
protected:
    explicit ClientConfigListModel(QObject *parent = nullptr);
private:
    void updateContext(client_id id);
    QHash<int, QByteArray> roleNames() const override;
    client_id availableId() const;
    void saveConfigs();
    void loadSavedConfigs();

    ClientDataContainer<ClientConfigModel> configs;
    std::unique_ptr<ClientConfigModel> contextModel;
};

}
#endif // CLIENTCONFIGLISTMODEL_HPP
