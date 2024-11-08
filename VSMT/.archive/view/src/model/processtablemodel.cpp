#include "processtablemodel.hpp"

namespace datamodels
{

QHash<int, QByteArray> ProcessTableModel::roleNames() const
{
    return {
        {Qt::DisplayRole, "display"}
    };
}

QVariant ProcessTableModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole || !index.isValid())
        return {};

    const ProcessEntry& entry = indexer[index.row()];
    switch (index.column()) {
    case 0:
        return entry.name;
    case 1:
        return entry.cpuUsage;
    case 2:
        return entry.memoryUsage;
    case 3:
        return entry.executable;
    default:
        return {};
    }
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return {};
    switch (section) {
    case 0:
        return "Name";
    case 1:
        return "Cpu Usage";
    case 2:
        return "Memory Usage";
    case 3:
        return "Executable";
    default:
        return {};
    }
}

ProcessTableModel::ProcessTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    QObject::connect(&indexer,&ProcessIndexer::dataChanged,this,[this](){
        emit dataChanged(createIndex(0,0),createIndex(rowCount()-1,columnCount()-1));
    });
}

}
