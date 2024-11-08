#ifndef CLIENTCONFIGURATION_HPP
#define CLIENTCONFIGURATION_HPP

#include <cstdint>
#include <QString>
#include "vsocket.hpp"

namespace common
{

using client_id = uint16_t;

struct ClientConfiguration
{
    client_id id;
    QString name;
    vsock::Address address;

    constexpr bool isHost() const { return id == hostId(); }
    static constexpr client_id hostId() { return 0; }
};

}

#endif // CLIENTCONFIGURATION_HPP
