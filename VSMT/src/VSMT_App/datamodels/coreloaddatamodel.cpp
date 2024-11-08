#include "coreloaddatamodel.hpp"

namespace datamodels
{

CoreLoadDataModelProvider::~CoreLoadDataModelProvider()
{
    for(auto &e : models) {
        delete e;
    }
}

int CoreLoadDataModelProvider::rowCount(const QModelIndex &parent) const
{
    return models.size();
}

QVariant CoreLoadDataModelProvider::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= rowCount())
        return {};
    switch (role) {
    case DataModelRole:
        return QVariant::fromValue(models[index.row()]);
    case CoreIndexRole:
        return index.row();
    default:
        return {};
    }
}

QHash<int, QByteArray> CoreLoadDataModelProvider::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DataModelRole] = "datamodel";
    roles[CoreIndexRole] = "coreIndex";
    return roles;
}

void CoreLoadDataModelProvider::setDataProviders(QVector<GraphData*> &dataproviders)
{
    beginRemoveRows(QModelIndex(),dataproviders.size(),models.size()-1);
    for(int i = dataproviders.size(); i < models.size(); i++) {
        delete models[i];
    }
    auto initializedSize = std::min(models.size(),(qsizetype)dataproviders.size());
    models.resize(dataproviders.size());

    beginInsertRows(QModelIndex(),initializedSize,dataproviders.size());
    for(int i = initializedSize; i < models.size(); i++) {
        models[i] = new CoreLoadDataModel(*dataproviders[i]);
    }
    endRemoveRows();
    endInsertRows();

    for(int i = 0; i < initializedSize; i++) {
        models[i]->setDataprovider(*dataproviders[i]);
    }
}

}
