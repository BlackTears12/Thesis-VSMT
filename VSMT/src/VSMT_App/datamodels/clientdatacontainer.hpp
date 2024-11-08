#ifndef CLIENTITEMCONTAINER_HPP
#define CLIENTITEMCONTAINER_HPP

#include <vector>
#include "contiguousclientmapper.hpp"

namespace datamodels
{

template <typename T>
class ClientDataContainer
{
public:
    using Container = std::vector<T>;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    using index_t = ContiguousClientMapper::index_t;

    ClientDataContainer() = default;

    const T& atIndex(index_t index) const { return container[index]; }
    T& atIndex(index_t index) { return container[index]; }
    const T& get(client_id id) const { return atIndex(mapper.indexOf(id)); }
    T& get(client_id id) { return atIndex(mapper.indexOf(id)); }
    index_t const indexOf(client_id id) { return mapper.indexOf(id); }

    void remove(client_id id);
    void append(client_id id,const T &item);
    void append(client_id id,T &&item);

    bool contains(client_id id) const { return mapper.containsClient(id); }
    size_t size() const { return container.size(); }
    bool empty() const { return container.empty(); }

    iterator begin() { return container.begin(); }
    iterator end() { return container.end(); }
    const_iterator begin() const { return container.begin(); }
    const_iterator end() const { return container.end(); }
    const_iterator cbegin() const { return container.cbegin(); }
    const_iterator cend() const { return container.cend(); }

    T& context() { return container[mapper.indexOf(contextClient)]; }
    const T& context() const { return container[mapper.indexOf(contextClient)]; }
    constexpr index_t contextIndex() const { return mapper.indexOf(contextClient); }

    void setContext(client_id id);
private:
    ContiguousClientMapper mapper;
    Container container;
    client_id contextClient = common::ClientConfiguration::hostId();
};

template<typename T>
inline void ClientDataContainer<T>::remove(common::client_id id)
{
    container.erase(container.begin()+mapper.indexOf(id));
    mapper.removeClient(id);
    if(id == contextClient) {
        contextClient = common::ClientConfiguration::hostId();
    }
}

template<typename T>
inline void ClientDataContainer<T>::append(common::client_id id, const T &item)
{
    container.push_back(item);
    mapper.appendClient(id);
}

template<typename T>
inline void ClientDataContainer<T>::append(common::client_id id,T &&item)
{
    container.push_back(std::move(item));
    mapper.appendClient(id);
}

template<typename T>
inline void ClientDataContainer<T>::setContext(common::client_id id)
{
    contextClient = id;
}

}

#endif // CLIENTITEMCONTAINER_HPP
