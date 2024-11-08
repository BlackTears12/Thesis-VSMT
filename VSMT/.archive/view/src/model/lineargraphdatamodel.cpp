#include "lineargraphdatamodel.hpp"
#include <QPointF>

namespace datamodels
{

LinearGraphDataModel::LinearGraphDataModel(QObject *parent)
    : QAbstractTableModel{parent},dataProvider() {}
{
}

QVariant LinearGraphDataModel::data(const QModelIndex &index, int role) const
{
    if(index.column() == 0)
        return index.row()+1;
    else
        return dataProvider[index.row()];
}

int LinearGraphDataModel::rowCount(const QModelIndex &parent) const
{
    return dataProvider.size();
}

int LinearGraphDataModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

void LinearGraphDataModel::setProvider(const DataProvider<double> provider)
{
    dataProvider = provider;
    emit dataChanged(createIndex(0,0),createIndex(rowCount()-1,1));
}

}
