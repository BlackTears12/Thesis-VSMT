#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <cstddef>
namespace datamodels
{

class DataDispatcher : QObject
{
    Q_OBJECT
signals:
    void dataChanged();
    void sizeChanged(size_t size);
};

template <typename Container>
class DataProvider
{
public:
    DataProvider(Container &cont): container(cont) {}
    auto operator[](size_t index) const { return container[index]; }
    size_t size() const { return container.size(); }
    const DataDispatcher& getDispatcher() const { return dispatcher; }

    void setSource(Container& cont);
private:
    Container& container;
    DataDispatcher dispatcher;
};

template<typename Container>
inline void DataProvider<Container>::setSource(Container &cont)
{
    if(&container == &cont)
        return;
    size_t oldSize = container.size();
    container = cont;
    if(oldSize != container.size())
        emit dispatcher.sizeChanged(cont.size());
    emit dispatcher.dataChanged();
}

}

#endif // DATAPROVIDER_H
