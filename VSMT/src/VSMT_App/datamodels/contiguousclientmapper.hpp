#ifndef CONTIGUOUSCLIENTMAPPER_HPP
#define CONTIGUOUSCLIENTMAPPER_HPP

#include "clientconfiguration.hpp"
#include <qdebug.h>

namespace datamodels
{

using common::client_id;

class ContiguousClientMapper
{
public:
    using index_t = unsigned int;
    ContiguousClientMapper();

    index_t indexOf(client_id id) const;
    client_id clientAt(index_t index) const;
    void removeClient(client_id id);
    index_t appendClient(client_id id);

    bool containsClient(client_id id) const;
private:
    std::map<client_id,index_t> indexLookup;
    std::vector<client_id> clientLookup;
    std::mutex modifyMutex;
};

}

#endif // CONTIGUOUSCLIENTMAPPER_HPP
