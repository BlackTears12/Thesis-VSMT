#ifndef CLIENTSTATUSMODEL_HPP
#define CLIENTSTATUSMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include "clientconfiguration.hpp"
#include "clientdatacontainer.hpp"
#include "contiguousclientmapper.hpp"
#include "qmlsingleton.hpp"

namespace datamodels
{

using std::string;
using std::vector;
using common::client_id;

struct StatusEntry
{
    StatusEntry(client_id id_,QString name_,double cpu_,double memory_):
        id(id_),name(name_),cpu(cpu_),memory(memory_) {}
    client_id id;
    QString name;
    double cpu;
    double memory;
};

class ClientStatusModel : public QAbstractListModel, public qml::QmlSingleton<ClientStatusModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(ClientStatusModel)
public:
    enum Roles {
        IdRole = Qt::UserRole+1,
        NameRole,
        CpuRole,
        MemoryRole
    };

    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;

    void add(StatusEntry entry);
    void remove(client_id id);
    void update(client_id id,StatusEntry entry);
    void updateRtValues(client_id id,double cpu,double memory);
signals:
    void itemTriggered(unsigned int index);
protected:
    ClientStatusModel(QObject* parent=nullptr);
    QHash<int, QByteArray> roleNames() const override;

    ClientDataContainer<StatusEntry> entries;
};

}
#endif // CLIENTSTATUSMODEL_HPP
