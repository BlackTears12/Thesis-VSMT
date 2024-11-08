#ifndef PROCESSINDEXER_HPP
#define PROCESSINDEXER_HPP

#include <QObject>
#include <QString>
#include <QVector>

namespace datamodels
{

struct ProcessEntry
{
    enum Field { Name = 0,Cpu,Memory,Executable, FieldCount };

    QString name;
    double cpuUsage;
    double memoryUsage;
    QString executable;

    template <Field F>
    bool compare(const ProcessEntry& other) const { return true; }
};

class ProcessIndexer : public QObject
{
    Q_OBJECT
public:
    ProcessIndexer(ProcessEntry::Field sortProperty=ProcessEntry::Name,QObject* parent=nullptr);

    size_t size() const { return entries.size(); }
    const ProcessEntry& operator[](size_t index) const { return indexer(this,index); }

    void update(const QVector<ProcessEntry> &entries);
    void setSortProperty(ProcessEntry::Field field);
signals:
    void dataChanged();
private:
    template <ProcessEntry::Field field>
    void sortByField();
    const ProcessEntry& normalIndex(size_t index) const { return entries[indicies[index]]; }
    const ProcessEntry& reverseIndex(size_t index) const { return entries[indicies[indicies.size()-1-index]]; }

    void sort();
    QVector<int> indicies;
    QVector<ProcessEntry> entries;
    ProcessEntry::Field sortedBy;
    bool reversed;
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
