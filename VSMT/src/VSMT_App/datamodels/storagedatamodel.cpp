#include "storagedatamodel.hpp"
#include "application.hpp"

namespace datamodels
{

int StorageDataModel::rowCount(const QModelIndex &parent) const
{
    if(infos.empty())
        return 0;
    return infos.at(context).size();
}

QVariant StorageDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    auto &info = infos.at(context)[index.row()];
    switch (role) {
    case Roles::NameRole:
        return info.name;
    case Roles::FSTypeRole:
        return info.fileSystemType;
    case Roles::DeviceRole:
        return info.device;
    case Roles::TotalBytesRole:
        return info.mbytesTotal;
    case Roles::FreeBytesRole:
        return info.mbytesFree;
    case Roles::UsedPercentRole:
        return info.usedPerced();
    }
    return {};
}

void StorageDataModel::updateLoads(client_id id,double memoryLoad,double diskLoad)
{
    if(id != context)
        return;
    core::Application::Instance().getMemoryRangeModel().setValue(memoryLoad);
    core::Application::Instance().getDiskRangeModel().setValue(diskLoad);

}

void StorageDataModel::updateDevices(common::client_id id, const QVector<StorageInfo> &info)
{
    infos[id] = info;
    if(id == context)
        refreshView();
}

void StorageDataModel::remove(common::client_id id)
{
    if(context == id) {
        setContext(common::ClientConfiguration::hostId());
    }
    infos.erase(id);
}

void StorageDataModel::setContext(common::client_id id)
{
    context = id;
    refreshView();
}

void StorageDataModel::refreshView()
{
    emit dataChanged(index(0),index(rowCount()-1));
}

StorageDataModel::StorageDataModel(QObject *parent) : QAbstractListModel{parent} {}

QHash<int, QByteArray> StorageDataModel::roleNames() const
{
    return {
        {Roles::NameRole,"name"},
        {Roles::FSTypeRole,"fileFsType"},
        {Roles::DeviceRole,"device"},
        {Roles::TotalBytesRole,"bytesTotal"},
        {Roles::FreeBytesRole,"bytesFree"},
        {Roles::UsedPercentRole,"usedPercent"}
    };
}



}
