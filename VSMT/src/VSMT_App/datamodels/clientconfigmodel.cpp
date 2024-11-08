#include "clientconfigmodel.hpp"

namespace datamodels
{

ClientConfigModel &ClientConfigModel::operator=(const ClientConfigModel &other)
{
    if(&other == this)
        return *this;
    this->config = other.config;
    return *this;
}

void ClientConfigModel::setName(QString name)
{
    if(name == config.name)
        return;
    config.name = name;
    emit nameChanged();
}

void ClientConfigModel::setIdentifier(const client_id &newIdentifier)
{
    if(newIdentifier == config.id)
        return;
    config.id = newIdentifier;
    emit identifierChanged();
}

void ClientConfigModel::setCid(unsigned int newCid)
{
    if(newCid == config.address.cid)
        return;
    config.address.cid = newCid;
    emit cidChanged();
}

void ClientConfigModel::setPort(unsigned int newPort)
{
    if(newPort == config.address.port)
        return;
    config.address.port = newPort;
    emit portChanged();
}

void ClientConfigModel::save(QXmlStreamWriter &writer) const
{
    writer.writeStartElement("client_config");
    writer.writeStartElement("id");
    writer.writeCharacters(QString::number(config.id));
    writer.writeEndElement();
    writer.writeStartElement("name");
    writer.writeCharacters(config.name);
    writer.writeEndElement();
    writer.writeStartElement("cid");
    writer.writeCharacters(QString::number(config.address.cid));
    writer.writeEndElement();
    writer.writeStartElement("port");
    writer.writeCharacters(QString::number(config.address.port));
    writer.writeEndElement();
    writer.writeEndElement();
}

void ClientConfigModel::updateStatus(const ConnectionStatus &status)
{
    connStatus = (ClientStatus::Status)status.status;
    connStatusMessage = status.message;
    emit connectionStatusMessageChaged();
    emit connectionStatusChanged();
}

ClientConfigModel ClientConfigModel::load(QXmlStreamReader &reader)
{
    reader.readNextStartElement();
    if(reader.name().toString() != "id") {
        throw std::exception();
    }
    client_id id = reader.readElementText().toInt();

    reader.readNextStartElement();
    if(reader.name().toString() != "name") {
        throw std::exception();
    }
    QString name = reader.readElementText();

    reader.readNextStartElement();
    if(reader.name().toString() != "cid") {
        throw std::exception();
    }
    uint32_t cid = reader.readElementText().toInt();

    reader.readNextStartElement();
    if(reader.name().toString() != "port") {
        throw std::exception();
    }
    uint32_t port = reader.readElementText().toInt();

    return ClientConfigModel(common::ClientConfiguration{
        id,name,vsock::Address{cid,port}
    });
}

ClientConfigModel ClientConfigModel::hostConfiguration()
{
    return ClientConfigModel(common::ClientConfiguration{
        .id = common::ClientConfiguration::hostId(),
        .name = "Host",
        .address = vsock::Address((uint32_t)vsock::Address::CID::Host,9999)
    });
}

}
