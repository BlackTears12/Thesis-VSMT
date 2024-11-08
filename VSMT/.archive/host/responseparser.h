#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include "../common/metrics.h"
#include "../common/vsockmanager.h"

namespace metrics
{

#define CONNECTION_HANDSHAKE_ID 0

class ResponseParser
{
public:
    ResponseParser() = default;

    vsock::Data toData(const RuntimeMetric &metric) const;
    template <Metric::Type type>
    vsock::Data requestData() const;

    /*
     * Parses vsock data
     * does not return nullptr,but the Metric has to be checked for corruption
    */
    unique_ptr<Metric> parse(const vsock::Data &data) const;
public:
    metrics::metricid_t nextId() { return currentId++; }
private:
    unique_ptr<SystemInfo> parseSystemInfo(const vsock::Data &data) const;
    unique_ptr<RuntimeMetric> parseRuntimeMetric(const vsock::Data &data) const;
    metrics::metricid_t parseId(const vsock::Data &data) const;
    void parseStringFromBinary(const vsock::Data &data,unsigned int start=0);

    metrics::metricid_t currentId = CONNECTION_HANDSHAKE_ID;
};


}
#endif // RESPONSEPARSER_H
