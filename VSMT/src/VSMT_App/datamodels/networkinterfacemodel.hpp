#ifndef NETWORKINTERFACEMODEL_HPP
#define NETWORKINTERFACEMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include <lineargraphdatamodel.hpp>
#include <memory>
#include "clientconfiguration.hpp"
#include "metrics.hpp"
#include "qmlsingleton.hpp"

namespace datamodels
{

using std::unique_ptr;

class NetworkLoadDataModel : public LinearGraphDataModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(NetworkLoadDataModel)

    Q_PROPERTY(qint32 maxValue READ maxValue NOTIFY maxValueChanged)
public:
    explicit NetworkLoadDataModel(GraphData &data,QObject *parent = nullptr):
        LinearGraphDataModel{parent} { setDataprovider(data); }

    qint32 maxValue() const { return m_maxValue; }
signals:
    void maxValueChanged();
private:
    qint32 m_maxValue = 500;
};

struct NetworkLoadData
{
    using Data = NetworkLoadDataModel::GraphData;

    NetworkLoadData() = default;
    void push(double rx,double tx) { rxBytes.push(rx); txBytes.push(tx); }

    Data rxBytes;
    Data txBytes;
};

using std::shared_ptr;

class NetworkInterfaceData
{
public:
    NetworkInterfaceData(const metrics::NetworkInterfaceInfo &inf): info(inf)
    {
        loadData = std::make_shared<NetworkLoadData>();
    }

    NetworkInterfaceData(const NetworkInterfaceData&) = default;
    NetworkInterfaceData() = default;

    metrics::NetworkInterfaceInfo getInfo() const { return info; }
    NetworkLoadData& getLoadData() const { return *loadData; }

    void update(double rx,double tx)
    {
        loadData->push(rx,tx);
        info.rxBytes = rx;
        info.txBytes = tx;
    }
private:
    metrics::NetworkInterfaceInfo info;
    shared_ptr<NetworkLoadData> loadData;
};

class ClientNetworkInfo
{
public:
    ClientNetworkInfo() = default;

    void update(const QVector<metrics::NetworkInterfaceInfo> &interfaces);

    constexpr qint64 overallRx() const { return rxOverall; }
    constexpr qint64 overallTx() const { return txOverall; }
    metrics::NetworkInterfaceInfo getInfo(unsigned int index) const { return datas.at(index).getInfo(); }
    QVector<NetworkInterfaceData>& getDatas() { return datas; }
private:
    void updateInterfaces(const QVector<metrics::NetworkInterfaceInfo> &interfaces);

    QVector<NetworkInterfaceData> datas;
    qint64 rxOverall = 0;
    qint64 txOverall = 0;
};

using common::client_id;
class NetworkInterfaceModel : public QAbstractListModel, public qml::QmlSingleton<NetworkInterfaceModel>
{
    Q_OBJECT
    NAMED_QML_SINGLETON(NetworkInterfaceModel)

    Q_PROPERTY(qint64 overallRx READ overallRx NOTIFY overallRxChanghed)
    Q_PROPERTY(qint64 overallTx READ overallTx NOTIFY overallTxChanghed)


    enum Roles {
        NameRole = Qt::UserRole+1,
        TypeRole,
        RxValRole,
        TxValRole,
        RxDataModelRole,
        TxDataModelRole
    };
public:
    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;
    qint64 overallRx() const;
    qint64 overallTx() const;
public:
    ~NetworkInterfaceModel();
    void updateInterfaces(client_id id,const QVector<metrics::NetworkInterfaceInfo> &interfaces);
    void append(client_id id);
    void remove(client_id id);

    void setContext(client_id id);
signals:
    void overallRxChanghed();
    void overallTxChanghed();

protected:
    explicit NetworkInterfaceModel(QObject *parent = nullptr);
private:
    QHash<int, QByteArray> roleNames() const override;
    void refreshView();

    /* unique ptrs cannot be used becouse QVector might try to copy on appending */
    QVector<NetworkLoadDataModel*> rxDataModels;
    QVector<NetworkLoadDataModel*> txDataModels;

    std::map<client_id,ClientNetworkInfo> networkInfos;
    client_id context = 0;
};

}

#endif // NETWORKINTERFACEMODEL_HPP
