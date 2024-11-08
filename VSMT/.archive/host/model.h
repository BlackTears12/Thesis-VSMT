#ifndef MODEL_H
#define MODEL_H

#include "../common/metrics.h"
#include "clientdispatcher.h"

namespace model
{

using std::vector;
using comm::ClientConfiguration;
using std::string;
using std::shared_ptr;
using std::map;

class UnknownClientException : std::exception{};

struct AppConfig
{
    vector<ClientConfiguration> clientConfigs;
    string configDirectory;
};

class Model
{
public:
    explicit Model() = default;

    AppConfig getConfiguration() { return appConfig; }
    void setConfiguration(const AppConfig &config) { appConfig = config; }
    shared_ptr<metrics::SystemInfo> getSystemInfo(comm::client_id_t id);
    ClientConfiguration getClientConfig(comm::client_id_t id);
    void setClientInfo(comm::client_id_t id,shared_ptr<metrics::SystemInfo> info) { clientInfos[id] = info; }
    void setClientConfig(comm::client_id_t id,ClientConfiguration config);
private:
    void saveAppConfig();
    void loadAppConfig();
private:
    map<comm::client_id_t,shared_ptr<metrics::SystemInfo>> clientInfos;
    AppConfig appConfig;
};

}
#endif // MODEL_H
