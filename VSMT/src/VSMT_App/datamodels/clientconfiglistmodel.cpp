#include "clientconfiglistmodel.hpp"

#include <application.hpp>
#include "util.hpp"

namespace datamodels
{

int ClientConfigListModel::rowCount(const QModelIndex &parent) const
{
    return configs.size();
}

QVariant ClientConfigListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    auto conf = configs.atIndex((client_id)index.row());
    switch (role) {
    case Roles::IdRole:
        return conf.getConfig().id;
    case Roles::NameRole:
        return conf.getConfig().name;
    case Roles::IsRemoteRole:
        return !conf.getConfig().isHost();
    case Roles::StatusRole:
        return conf.connectionStatus();
    case Roles::StatusMessageRole:
        return conf.connectionStatusMessage();
    default:
        return {};
    }
}

ClientConfiguration const* ClientConfigListModel::searchForClientConfig(common::client_id id)
{
    if(configs.contains(id))
        return &configs.get(id).getConfig();
    return nullptr;
}

void ClientConfigListModel::onSaveConfigClicked(QString newName,QString newCid,QString newPort)
{
    qDebug() << "Saved: " << configs.context().identifier();
    configs.context().setName(newName);
    /* TODO verify values */
    configs.context().setCid(newCid.toInt());
    configs.context().setPort(newPort.toInt());
    emit dataChanged(index(configs.contextIndex()),index(configs.contextIndex()));
    core::Application::Instance().getNavigator().closeClientConfigPage();
    saveConfigs();
}

void ClientConfigListModel::onRevertConfigClicked()
{
    core::Application::Instance().getNavigator().closeClientConfigPage();
    emit contextChanged();
}

void ClientConfigListModel::updateConfig(const ClientConfiguration &config)
{
    configs.context() = ClientConfigModel(config);
}

void ClientConfigListModel::notifyClientStatusChanged(comm::ConnectionStatus status, common::client_id id)
{
    configs.get(id).updateStatus(status);
    emit dataChanged(index(configs.indexOf(id)),index(configs.indexOf(id)));
}

void ClientConfigListModel::deleteConfig(common::client_id id)
{
    beginRemoveRows(QModelIndex(),rowCount()-1,rowCount()-1);
    configs.remove(id);
    endRemoveRows();
    emit dataChanged(index(0),index(rowCount()-1));
    emit contextChanged();
    saveConfigs();
}

ClientConfigListModel::ClientConfigListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    loadSavedConfigs();
    QObject::connect(this,&ClientConfigListModel::configEditClicked,this,&ClientConfigListModel::onConfigEditClicked);
    QObject::connect(this,&ClientConfigListModel::saveConfigClicked,this,&ClientConfigListModel::onSaveConfigClicked);
    QObject::connect(this,&ClientConfigListModel::revertConfigClicked,this,&ClientConfigListModel::onRevertConfigClicked);
    QObject::connect(this,&ClientConfigListModel::newConfigClicked,this,&ClientConfigListModel::onNewConfigClicked);
    contextModel = std::make_unique<ClientConfigModel>(configs.context());
}

void ClientConfigListModel::updateContext(common::client_id id)
{
    configs.setContext(id);
    auto &context = configs.context();
    contextModel->setIdentifier(context.identifier());
    contextModel->setName(context.name());
    contextModel->setCid(context.cid());
    contextModel->setPort(context.port());
    emit contextChanged();
}

void ClientConfigListModel::loadSavedConfigs()
{
    auto file = core::Application::Instance().getSavedConfigFile();
    file.open(QIODevice::ReadOnly);
    if(file.exists()) {
        QXmlStreamReader reader(&file);
        while(!reader.atEnd()) {
            auto tok = reader.readNext();
            if(tok == QXmlStreamReader::StartDocument)
                continue;
            if(tok == QXmlStreamReader::StartElement && reader.name().toString() != "root") {
                auto config = ClientConfigModel::load(reader);
                configs.append(config.identifier(),config);
            }
        }
        qDebug() << "configs loaded!";
    }
    file.close();
    if(configs.empty()) {
        configs.append(ClientConfiguration::hostId(),ClientConfigModel::hostConfiguration());
        saveConfigs();
    }
    qDebug() << configs.size();
    emit dataChanged(index(0),index(configs.size()-1));
}

void ClientConfigListModel::saveConfigs()
{
    auto file = core::Application::Instance().getSavedConfigFile();
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter writer(&file);
    writer.writeStartDocument();
    writer.writeStartElement("root");
    for(auto &e : configs) {
        e.save(writer);
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
    qDebug() << "configs saved!";
}


QHash<int, QByteArray> ClientConfigListModel::roleNames() const
{
    return {
        {IdRole,"identifier"},
        {NameRole,"name"},
        {IsRemoteRole,"isRemote"},
        {StatusRole,"status"},
        {StatusMessageRole,"statusMessage"}
    };
}

common::client_id ClientConfigListModel::availableId() const
{
    for(client_id i = 0;i < 256;i++) {
        if(!configs.contains(i))
            return i;
    }
    return 256;
}

ClientConfigModel* ClientConfigListModel::context()
{
    return contextModel.get();
}

void ClientConfigListModel::onNewConfigClicked()
{
    ClientConfiguration config {
        .id = availableId(),
        .name = "New Client",
        .address = {(uint32_t)vsock::Address::CID::Host,9000},
    };
    beginInsertRows(QModelIndex(),configs.size(),configs.size());
    configs.append(config.id,config);
    endInsertRows();
    saveConfigs();
    updateContext(config.id);
}

void ClientConfigListModel::onConfigEditClicked(client_id id)
{
    updateContext(id);
    core::Application::Instance().getNavigator().openClientConfigPage();
}

}
