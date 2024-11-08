#include "lineargraphdatamodel.hpp"
#include <QPointF>

namespace datamodels
{

LinearGraphDataModel::LinearGraphDataModel(QObject *parent)
    : QAbstractTableModel{parent},dataProvider(nullptr)
{
}

QVariant LinearGraphDataModel::data(const QModelIndex &index, int role) const
{
    if(index.column() == 0)
        return index.row()+1;
    else
        return (*dataProvider)[index.row()];
}

int LinearGraphDataModel::rowCount(const QModelIndex &parent) const
{
    if(dataProvider)
        return dataProvider->size();
    return 0;
}

int LinearGraphDataModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

void LinearGraphDataModel::setDataprovider(GraphData &data)
{
    if(dataProvider)
        QObject::disconnect(&dataProvider->signalHandler,&flowbuffer::SignalHandler::dataChanged,this,&LinearGraphDataModel::onDataChanged);
    QObject::connect(&data.signalHandler,&flowbuffer::SignalHandler::dataChanged,this,&LinearGraphDataModel::onDataChanged);
    dataProvider = &data;
    onDataChanged();
}

void LinearGraphDataModel::onDataChanged()
{
    emit dataChanged(createIndex(0,0),createIndex(dataProvider->size()-1,0));
}

}
