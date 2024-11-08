#ifndef PROCESSINDEXER_HPP
#define PROCESSINDEXER_HPP

#include <QObject>
#include <QString>
#include <QVector>
#include "metrics.hpp"

namespace datamodels
{

struct ProcessEntry
{
    ProcessEntry() = default;
    ProcessEntry(const metrics::ProcessInfo &info);

    enum Field { Pid,Status,Cpu,Memory,Executable,Args,FieldCount };

    uint16_t pid;
    QString status;
    double cpuUsage;
    double memoryUsage;
    QString executable;
    QString args;


    template <Field F>
    bool compare(const ProcessEntry& other) const { return true; }
private:
    static QString cropExecutable(const QString &exec);
};

class ProcessIndexer : public QObject
{
    Q_OBJECT
public:
    ProcessIndexer(ProcessEntry::Field sortProperty=ProcessEntry::Executable,QObject* parent=nullptr);

    size_t size() const { return entries.size(); }
    const ProcessEntry& operator[](size_t index) const { return indexer(this,index); }

    void update(const QVector<ProcessEntry> &entries);
    void setSortProperty(ProcessEntry::Field field,bool ascending = true);
signals:
    void dataChanged();
private:
    void sort();
    template <ProcessEntry::Field field>
    void sortByField();
    const ProcessEntry& ascendingIndex(size_t index) const { return entries[indicies[index]]; }
    const ProcessEntry& descendingIndex(size_t index) const { return entries[indicies[indicies.size()-1-index]]; }

    QVector<int> indicies;
    QVector<ProcessEntry> entries;
    ProcessEntry::Field sortedBy;
    std::function<const ProcessEntry&(const ProcessIndexer*,size_t index)> indexer;
};

template <ProcessEntry::Field field>
void ProcessIndexer::sortByField()
{
    auto& entries = this->entries;
    std::stable_sort(indicies.begin(), indicies.end(),
        [&entries](size_t i1, size_t i2) { return entries[i1].compare<field>(entries[i2]); });
}

}

#endif // PROCESSINDEXER_HPP
