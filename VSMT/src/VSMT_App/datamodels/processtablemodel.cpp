#include "processtablemodel.hpp"

namespace datamodels
{

QVariant ProcessTableModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole || !index.isValid())
        return {};

    const ProcessEntry& entry = indexer[index.row()];
    switch (index.column()) {
    case 0:
        return entry.pid;
    case 1:
        return entry.status;
    case 2:
        return entry.cpuUsage;
    case 3:
        return entry.memoryUsage;
    case 4:
        return displayString(entry.executable);
    case 5:
        return displayString(entry.args);
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
        return "Pid";
    case 1:
        return "Status";
    case 2:
        return "Cpu Usage(%)";
    case 3:
        return "Memory Usage(%)";
    case 4:
        return "Executable";
    case 5:
        return "Arguments";
    default:
        return {};
    }
}

void ProcessTableModel::update(common::client_id id, const QVector<ProcessEntry> &processes)
{
    entries[id] = processes;
    if(id == context) {
        indexer.update(processes);
    }
}

void ProcessTableModel::remove(common::client_id id)
{
    if(id == context) {
        setContext(common::ClientConfiguration::hostId());
    }
    entries.erase(id);
}

void ProcessTableModel::append(common::client_id id)
{
    entries.emplace(id,QVector<ProcessEntry>{});
}

void ProcessTableModel::setContext(common::client_id id)
{
    context = id;
    indexer.update(entries[id]);
}

ProcessTableModel::ProcessTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    QObject::connect(&indexer,&ProcessIndexer::dataChanged,this,[this](){
        emit dataChanged(createIndex(0,0),createIndex(rowCount()-1,columnCount()-1));
    });
}

QString ProcessTableModel::displayString(const QString str) const
{
    if(str.size()>20)
        return str.left(17) + "...";
    return str;
}

}
