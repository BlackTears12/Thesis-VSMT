#ifndef CORELOADDATAMODEL_H
#define CORELOADDATAMODEL_H

#include <QObject>
#include <QtQmlIntegration>
#include "lineargraphdatamodel.hpp"
#include "qmlsingleton.hpp"

namespace datamodels
{

using std::unique_ptr;
using std::vector;

class CoreLoadDataModel : public LinearGraphDataModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CoreLoadDataModel)
public:
    explicit CoreLoadDataModel(GraphData &data,QObject *parent = nullptr):
        LinearGraphDataModel{parent} { setDataprovider(data); }
};

class CoreLoadDataModelProvider : public QAbstractListModel, public qml::QmlSingleton<CoreLoadDataModelProvider>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(CoreLoadDataModelProvider)
public:
    enum Roles {
        DataModelRole = Qt::UserRole+1,
        CoreIndexRole
    };

    ~CoreLoadDataModelProvider();
    using GraphData = LinearGraphDataModel::GraphData;

    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setDataProviders(QVector<GraphData*> &dataproviders);
protected:
    CoreLoadDataModelProvider(QObject* parent = nullptr):
        QAbstractListModel{parent} {}

    /* unique ptrs cannot be used becouse QVector might try to copy on appending */
    QVector<CoreLoadDataModel*> models;
};

}
#endif // CORELOADDATAMODEL_H
