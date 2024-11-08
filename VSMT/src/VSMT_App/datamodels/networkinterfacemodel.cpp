#include "networkinterfacemodel.hpp"

namespace datamodels
{

int NetworkInterfaceModel::rowCount(const QModelIndex &parent) const
{
    if(networkInfos.empty())
        return 0;
    return rxDataModels.size(); //same as txDataModels/infos .size()
}

QVariant NetworkInterfaceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= rowCount())
        return {};
    const auto &loadInfo = networkInfos.at(context).getInfo(index.row());
    switch (role) {
    case Roles::NameRole:
        return loadInfo.name;
    case Roles::TypeRole:
        return loadInfo.typeAsStr();
    case Roles::RxValRole:
        return QString::number(loadInfo.rxBytes);
    case Roles::TxValRole:
        return QString::number(loadInfo.txBytes);
    case Roles::RxDataModelRole:
        return QVariant::fromValue(rxDataModels[index.row()]);
    case Roles::TxDataModelRole:
        return QVariant::fromValue(txDataModels[index.row()]);
    }
    return {};
}

NetworkInterfaceModel::~NetworkInterfaceModel()
{
    for(int i = 0; i < rxDataModels.size(); i++) {
        delete rxDataModels[i];
        delete txDataModels[i];
    }
}

void NetworkInterfaceModel::updateInterfaces(common::client_id id,const QVector<metrics::NetworkInterfaceInfo> &interfaces)
{
    networkInfos[id].update(interfaces);
    if(id == context) {
        refreshView();
    }
}

void NetworkInterfaceModel::append(common::client_id id)
{
    networkInfos.emplace(id,ClientNetworkInfo{});
}

void NetworkInterfaceModel::remove(common::client_id id)
{
    if(id == context) {
        setContext(common::ClientConfiguration::hostId());
    }
    networkInfos.erase(id);
}

void NetworkInterfaceModel::setContext(common::client_id id)
{
    context = id;
    refreshView();
}

NetworkInterfaceModel::NetworkInterfaceModel(QObject *parent) : QAbstractListModel{parent},context(0) {}

QHash<int, QByteArray> NetworkInterfaceModel::roleNames() const
{
    return {
        {Roles::NameRole,"name"},
        {Roles::TypeRole,"type"},
        {Roles::RxValRole,"rxValue"},
        {Roles::TxValRole,"txValue"},
        {Roles::RxDataModelRole,"rxDataModel"},
        {Roles::TxDataModelRole,"txDataModel"}
    };
}

void NetworkInterfaceModel::refreshView()
{
    auto &dataProvider = networkInfos.at(context).getDatas();
    beginRemoveRows(QModelIndex(),dataProvider.size(),rxDataModels.size()-1);
    for(int i = dataProvider.size(); i < rxDataModels.size(); i++) {
        delete rxDataModels[i];
        delete txDataModels[i];
    }
    auto initializedSize = std::min(rxDataModels.size(),(qsizetype)dataProvider.size());
    rxDataModels.resize(dataProvider.size());
    txDataModels.resize(dataProvider.size());

    beginInsertRows(QModelIndex(),initializedSize,dataProvider.size());
    for(int i = initializedSize; i < rxDataModels.size(); i++) {
        rxDataModels[i] = new NetworkLoadDataModel(dataProvider[i].getLoadData().rxBytes);
        txDataModels[i] = new NetworkLoadDataModel(dataProvider[i].getLoadData().txBytes);
    }
    endRemoveRows();
    endInsertRows();

    for(int i = 0; i < initializedSize; i++) {
        rxDataModels[i]->setDataprovider(dataProvider[i].getLoadData().rxBytes);
        txDataModels[i]->setDataprovider(dataProvider[i].getLoadData().txBytes);
    }

    emit dataChanged(index(0),index(rowCount()-1));
    emit overallTxChanghed();
    emit overallRxChanghed();
}

qint64 NetworkInterfaceModel::overallRx() const
{
    return networkInfos.at(context).overallRx();
}

qint64 NetworkInterfaceModel::overallTx() const
{
    return networkInfos.at(context).overallTx();
}

void ClientNetworkInfo::update(const QVector<metrics::NetworkInterfaceInfo> &interfaces)
{
    rxOverall = 0;
    txOverall = 0;
    for(const auto &e : interfaces) {
        rxOverall += e.rxBytes;
        txOverall += e.txBytes;
    }
    updateInterfaces(interfaces);
}

void ClientNetworkInfo::updateInterfaces(const QVector<metrics::NetworkInterfaceInfo> &interfaces)
{
    for(auto &newInterface : interfaces) {
        const QString& interfaceName = newInterface.name;
        auto iter = std::find_if(datas.begin(),datas.end(),[&interfaceName](auto &oldI) {
            return interfaceName == oldI.getInfo().name;
        });
        /* no interface found in the old data */
        if(iter == datas.end()) {
            datas.append(NetworkInterfaceData(newInterface));
        } /* interface already known */
        else {
            iter->update(newInterface.rxBytes,newInterface.txBytes);
        }
    }
    /* TODO remove old interfaces */
}

}
