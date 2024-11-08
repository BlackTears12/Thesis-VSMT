#include "clientstatusmodel.hpp"

namespace datamodels
{

ClientStatusModel::ClientStatusModel(QObject* parent)
{
}

QHash<int, QByteArray> ClientStatusModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "clientId";
    roles[NameRole] = "name";
    roles[CpuRole] = "cpu";
    roles[MemoryRole] = "memory";
    return roles;
}

int ClientStatusModel::rowCount(const QModelIndex &parent) const
{
    return entries.size();
}

QVariant ClientStatusModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() < 0 || index.row() >= entries.size())
        return {};
    auto& entry = entries.atIndex(index.row());
    switch (role) {
    case IdRole:
        return entry.id;
    case NameRole:
        return entry.name;
    case CpuRole:
        return entry.cpu;
    case MemoryRole:
        return entry.memory;
    default:
        return {};
    }
}

void ClientStatusModel::add(StatusEntry entry)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    entries.append(entry.id,entry);
    endInsertRows();
}

void ClientStatusModel::remove(client_id id)
{
    beginRemoveRows(QModelIndex(),id,id);
    entries.remove(id);
    endRemoveRows();
}

void ClientStatusModel::update(client_id id, StatusEntry entry)
{
    entries.get(id) = entry;
    auto index = entries.indexOf(id);
    emit dataChanged(this->createIndex(index,0),this->createIndex(index,0));
}

void ClientStatusModel::updateRtValues(client_id id, double cpu, double memory)
{
    entries.get(id).cpu = cpu;
    entries.get(id).memory = memory;
    auto index = entries.indexOf(id);
    emit dataChanged(this->createIndex(index,0),this->createIndex(index,0));
}

}
