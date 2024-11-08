#include "processindexer.hpp"

namespace datamodels
{

template <>
bool ProcessEntry::compare<ProcessEntry::Name>(const ProcessEntry& other) const { return name < other.name; }

template <>
bool ProcessEntry::compare<ProcessEntry::Cpu>(const ProcessEntry& other) const { return cpuUsage < other.cpuUsage; }

template <>
bool ProcessEntry::compare<ProcessEntry::Memory>(const ProcessEntry& other) const { return memoryUsage < other.memoryUsage; }

template <>
bool ProcessEntry::compare<ProcessEntry::Executable>(const ProcessEntry& other) const { return executable < other.executable; }


ProcessIndexer::ProcessIndexer(ProcessEntry::Field sortProperty,QObject* parent):
    QObject{parent},sortedBy(sortProperty)
{
    indexer = &ProcessIndexer::normalIndex;
}

void ProcessIndexer::update(const QVector<ProcessEntry> &entries)
{
    this->entries = entries;
    indicies.resize(entries.size());
    std::iota(indicies.begin(), indicies.end(), 0);
    sort();
}

void ProcessIndexer::setSortProperty(ProcessEntry::Field field)
{
    if(sortedBy == field) {
        reversed = !reversed;
        if(reversed)
            indexer = &ProcessIndexer::reverseIndex;
        else
            indexer = &ProcessIndexer::normalIndex;
    }
    else {
        reversed = false;
        indexer = &ProcessIndexer::normalIndex;
        sortedBy = field;
        sort();
    }
    emit dataChanged();
}

void ProcessIndexer::sort()
{
    switch (sortedBy) {
    case ProcessEntry::Name:
        sortByField<ProcessEntry::Name>();
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
    default:
        break;
    }
}

}
