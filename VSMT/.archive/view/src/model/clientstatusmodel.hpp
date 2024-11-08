#ifndef CLIENTSTATUSMODEL_H
#define CLIENTSTATUSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "qmlsingleton.hpp"

namespace datamodels
{

using std::string;
using std::vector;

struct StatusEntry
{
    StatusEntry(QString name_,double cpu_,double memory_) : name(name_),cpu(cpu_),memory(memory_) {}
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
        NameRole = Qt::UserRole+1,
        CpuRole,
        MemoryRole
    };

    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;

    void add(StatusEntry entry);
    void update(uint16_t index,StatusEntry entry);
signals:
    void itemTriggered(int index);
protected:
    ClientStatusModel(QObject* parent=nullptr);
    QHash<int, QByteArray> roleNames() const override;

    vector<StatusEntry> entries;
};

}
#endif // CLIENTSTATUSMODEL_H
