#ifndef PROCESSTABLEMODEL_HPP
#define PROCESSTABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QObject>
#include "qmlsingleton.hpp"
#include "processindexer.hpp"
#include "clientconfiguration.hpp"

namespace datamodels
{

using common::client_id;

class ProcessTableModel : public QAbstractTableModel, public qml::QmlSingleton<ProcessTableModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(ProcessTableModel)
public:
    int rowCount(const QModelIndex & = QModelIndex()) const override { return indexer.size(); }
    int columnCount(const QModelIndex & = QModelIndex()) const override { return ProcessEntry::FieldCount; }

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
public slots:
    void sortByCol(size_t col,bool ascending) { indexer.setSortProperty((ProcessEntry::Field)col,ascending); }
public:
    void update(client_id id,const QVector<ProcessEntry> &processes);
    void remove(client_id id);
    void append(client_id id);

    void setContext(client_id id);
protected:
    explicit ProcessTableModel(QObject *parent = nullptr);
private:
    QString displayString(const QString str) const;

    ProcessIndexer indexer;
    std::map<client_id,QVector<ProcessEntry>> entries;
    client_id context = 0;
};

}

#endif // PROCESSTABLEMODEL_HPP
