#include "clientstatusmodel.hpp"

namespace datamodels
{

ClientStatusModel::ClientStatusModel(QObject* parent)
{
}

QHash<int, QByteArray> ClientStatusModel::roleNames() const
{
    QHash<int, QByteArray> roles;
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
    auto& entry = entries[index.row()];
    switch (role) {
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
    entries.push_back(entry);
    endInsertRows();
}

void ClientStatusModel::update(uint16_t index, StatusEntry entry)
{
    entries[index] = entry;
    emit dataChanged(this->createIndex(index,0),this->createIndex(index,0));
}

}
