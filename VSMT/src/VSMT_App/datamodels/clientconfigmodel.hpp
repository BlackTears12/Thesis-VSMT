#ifndef CLIENTCONFIGMODEL_HPP
#define CLIENTCONFIGMODEL_HPP

#include <QObject>
#include <QQmlEngine>
#include <QXmlStreamWriter>
#include <clientconfiguration.hpp>
#include <clientconnector.hpp>

namespace datamodels
{

using common::ClientConfiguration;
using common::client_id;
using comm::ConnectionStatus;

class ClientStatus : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ClientStatus)
    QML_UNCREATABLE("Only creatable from C++")
public:
    enum Status {
        IDLE,ALIVE,TIMED_OUT,REFUSED
    };
    Q_ENUM(Status);

};

class ClientConfigModel : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ClientConfigModel)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(client_id identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged)
    Q_PROPERTY(unsigned int cid READ cid WRITE setCid NOTIFY cidChanged)
    Q_PROPERTY(unsigned int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool isRemote READ isRemote CONSTANT)
    Q_PROPERTY(ClientStatus::Status connectionStatus READ connectionStatus NOTIFY connectionStatusChanged)
    Q_PROPERTY(QString connectionStatusMessage READ connectionStatusMessage NOTIFY connectionStatusMessageChaged)
public:
    ClientConfigModel(const ClientConfiguration &conf) :  config(conf) {}
    ClientConfigModel(const ClientConfigModel &other) : config(other.config) {}
    ClientConfigModel() : config(hostConfiguration().config) {}
    ClientConfigModel& operator=(const ClientConfigModel &other);

    QString name() const { return config.name; }
    void setName(QString name);

    client_id identifier() const { return config.id; }
    void setIdentifier(const client_id &newIdentifier);

    unsigned int cid() const { return config.address.cid; }
    void setCid(unsigned int newCid);

    unsigned int port() const { return config.address.port; }
    void setPort(unsigned int newPort);

    bool isRemote() const { return !config.hostId(); }

    ClientStatus::Status connectionStatus() const { return connStatus; }
    QString connectionStatusMessage() const { return connStatusMessage; }
signals:
    void nameChanged();
    void identifierChanged();
    void cidChanged();
    void portChanged();
    void connectionStatusChanged();
    void connectionStatusMessageChaged();
public:
    const ClientConfiguration& getConfig() const { return config; }
    void save(QXmlStreamWriter &writer) const;
    void updateStatus(const ConnectionStatus &status);
private:
    ClientConfiguration config;
    ClientStatus::Status connStatus;
    QString connStatusMessage;

public:
    static ClientConfigModel load(QXmlStreamReader &reader);
    static ClientConfigModel hostConfiguration();;
};

}

#endif // CLIENTCONFIGMODEL_HPP
