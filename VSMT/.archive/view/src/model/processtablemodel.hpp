#ifndef PROCESSTABLEMODEL_HPP
#define PROCESSTABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QObject>
#include "qmlsingleton.hpp"
#include "processindexer.hpp"

namespace datamodels
{

class ProcessTableModel : public QAbstractTableModel, public qml::QmlSingleton<ProcessTableModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(ProcessTableModel)
public:
    int rowCount(const QModelIndex & = QModelIndex()) const override { return indexer.size(); }
    int columnCount(const QModelIndex & = QModelIndex()) const override { return ProcessEntry::FieldCount; }
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
public slots:
    void headerClicked(size_t col) { indexer.setSortProperty((ProcessEntry::Field)col); }
public:
    void update(const QVector<ProcessEntry> &entries) { indexer.update(entries); }
protected:
    explicit ProcessTableModel(QObject *parent = nullptr);

    ProcessIndexer indexer;
};

}

#endif // PROCESSTABLEMODEL_HPP
