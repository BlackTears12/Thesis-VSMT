#include "model.h"

namespace model
{

shared_ptr<metrics::SystemInfo> Model::getSystemInfo(comm::client_id_t id)
{
    if(clientInfos.count(id))
        return clientInfos[id];
    throw UnknownClientException();
}

ClientConfiguration Model::getClientConfig(comm::client_id_t id)
{
    for(auto& e : appConfig.clientConfigs){
        if(e.id == id)
            return e;
    }
    throw UnknownClientException();
}

void Model::setClientConfig(comm::client_id_t id, ClientConfiguration config)
{
    int i = 0;
    while(i < appConfig.clientConfigs.size() && appConfig.clientConfigs[i].id != id){
        ++i;
    }
    if(i == appConfig.clientConfigs.size())
        appConfig.clientConfigs.push_back(config);
    else
        appConfig.clientConfigs[i] = config;
}

void Model::saveAppConfig()
{

}

void Model::loadAppConfig()
{

}

}
