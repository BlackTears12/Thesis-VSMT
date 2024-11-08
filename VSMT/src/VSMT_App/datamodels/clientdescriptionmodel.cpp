#include "clientdescriptionmodel.hpp"

namespace datamodels
{

void ClientDescriptionModel::remove(common::client_id id)
{
    auto oldContext = infos.contextIndex();
    infos.remove(id);
    if(oldContext == id)
        emitDataChanged();
}

void ClientDescriptionModel::update(client_id id,const ClientDescriptionInfo &info)
{
    infos.get(id) = info;
    if(id == infos.contextIndex())
        emitDataChanged();
}

void ClientDescriptionModel::emitDataChanged()
{
    emit platformChanged();
    emit distributionChanged();
    emit cpuCoresChanged();
    emit cpuModelChanged();
    emit cpuSpeedChanged();
    emit nameChanged();
}

}
