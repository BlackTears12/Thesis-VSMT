#include "processindexer.hpp"

namespace datamodels
{

template <>
bool ProcessEntry::compare<ProcessEntry::Pid>(const ProcessEntry& other) const { return pid < other.pid; }

template <>
bool ProcessEntry::compare<ProcessEntry::Status>(const ProcessEntry& other) const { return status < other.status; }

template <>
bool ProcessEntry::compare<ProcessEntry::Cpu>(const ProcessEntry& other) const { return cpuUsage < other.cpuUsage; }

template <>
bool ProcessEntry::compare<ProcessEntry::Memory>(const ProcessEntry& other) const { return memoryUsage < other.memoryUsage; }

template <>
bool ProcessEntry::compare<ProcessEntry::Executable>(const ProcessEntry& other) const { return executable < other.executable; }

template <>
bool ProcessEntry::compare<ProcessEntry::Args>(const ProcessEntry& other) const { return args < other.args; }


ProcessIndexer::ProcessIndexer(ProcessEntry::Field sortProperty,QObject* parent):
    QObject{parent},sortedBy(sortProperty)
{
    indexer = &ProcessIndexer::ascendingIndex;
}

void ProcessIndexer::update(const QVector<ProcessEntry> &entries)
{
    this->entries = entries;
    indicies.resize(entries.size());
    std::iota(indicies.begin(), indicies.end(), 0);
    sort();
    emit dataChanged();
}

void ProcessIndexer::setSortProperty(ProcessEntry::Field field,bool ascending)
{
    if(ascending)
        indexer = &ProcessIndexer::ascendingIndex;
    else
        indexer = &ProcessIndexer::descendingIndex;
    sortedBy = field;
    sort();
    emit dataChanged();
}

void ProcessIndexer::sort()
{
    switch (sortedBy) {
    case ProcessEntry::Pid:
        sortByField<ProcessEntry::Pid>();
        break;
    case ProcessEntry::Status:
        sortByField<ProcessEntry::Status>();
        break;
    case ProcessEntry::Cpu:
        sortByField<ProcessEntry::Cpu>();
        break;
    case ProcessEntry::Memory:
        sortByField<ProcessEntry::Memory>();
        break;
    case ProcessEntry::Executable:
        sortByField<ProcessEntry::Executable>();
        break;
    case ProcessEntry::Args:
        sortByField<ProcessEntry::Args>();
        break;
    default:
        break;
    }
}

ProcessEntry::ProcessEntry(const metrics::ProcessInfo &info):
    pid(info.pid),status(info.StatusToStr()),
    cpuUsage(info.processorUsage),memoryUsage(info.memoryPercent),
    executable(cropExecutable(info.executable)),args(info.args) {}

QString ProcessEntry::cropExecutable(const QString &exec)
{
    auto parts = exec.split('/');
    if(parts.last().size() < 10 && parts.size() >= 2)
        return parts[parts.size()-2] + "/" +parts.last();
    return parts.last();
}

}
