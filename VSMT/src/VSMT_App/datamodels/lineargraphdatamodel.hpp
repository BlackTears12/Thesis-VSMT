#ifndef LINEARGRAPHDATAMODEL_HPP
#define LINEARGRAPHDATAMODEL_HPP

#include <QAbstractTableModel>
#include <QPointF>
#include <flowbuffer.hpp>

namespace datamodels
{

class LinearGraphDataModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int maxSize READ maxSize CONSTANT)
public:
    static constexpr int MaxSize = 20;
    using GraphData = flowbuffer::FlowBuffer<double,MaxSize>;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    constexpr int maxSize() const { return MaxSize; }

    void setDataprovider(GraphData& data);
private slots:
    void onDataChanged();
protected:
    explicit LinearGraphDataModel(QObject *parent = nullptr);
    GraphData* dataProvider;
};

}

#endif // LINEARGRAPHDATAMODEL_HPP
