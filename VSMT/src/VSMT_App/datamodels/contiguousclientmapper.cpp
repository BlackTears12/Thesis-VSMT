#include "contiguousclientmapper.hpp"

namespace datamodels
{

ContiguousClientMapper::ContiguousClientMapper() {}

ContiguousClientMapper::index_t ContiguousClientMapper::indexOf(common::client_id id) const
{
    return indexLookup.at(id);
}

common::client_id ContiguousClientMapper::clientAt(index_t index) const
{
    return clientLookup[index];
}

void ContiguousClientMapper::removeClient(common::client_id id)
{
    modifyMutex.lock();
    auto index = indexOf(id);
    indexLookup.erase(id);
    for(int i = index; i <= clientLookup.size()-2; i++) {
        clientLookup[i] = clientLookup[i+1];
        indexLookup[clientLookup[i]] = i;
    }
    clientLookup.pop_back();
    modifyMutex.unlock();
}

ContiguousClientMapper::index_t ContiguousClientMapper::appendClient(common::client_id id)
{
    modifyMutex.lock();
    indexLookup.insert({id,clientLookup.size()});
    clientLookup.push_back(id);
    modifyMutex.unlock();
    return clientLookup.size()-1;
}

bool ContiguousClientMapper::containsClient(client_id id) const
{
    return indexLookup.count(id);
}

}
