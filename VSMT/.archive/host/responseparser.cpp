#include "responseparser.h"

namespace metrics
{

template <>
vsock::Data ResponseParser::requestData<Metric::RuntimeMetricRequest>() const
{
    vsock::Data data = {0};
    data[0] = RuntimeMetric::IdByte;
    return data;
}

template <>
vsock::Data ResponseParser::requestData<Metric::SystemInfoRequest>() const
{
    vsock::Data data = {0};
    data[0] = SystemInfo::IdByte;
    return data;
}

std::unique_ptr<Metric> ResponseParser::parse(const vsock::Data &data) const
{
    if(data[0] == RuntimeMetric::IdByte)
        return std::make_unique<Metric>(parseRuntimeMetric(data),parseId(data));
    if(data[0] == SystemInfo::IdByte)
        return std::make_unique<Metric>(parseSystemInfo(data),parseId(data));
    return std::make_unique<Metric>(nullptr,parseId(data));
}

std::unique_ptr<SystemInfo> ResponseParser::parseSystemInfo(const vsock::Data &data) const
{
    auto totalRam = reinterpret_cast<const uint64_t*>(&data[1]);
    auto cores = reinterpret_cast<const uint8_t*>(&data[5]);

}

std::unique_ptr<RuntimeMetric> ResponseParser::parseRuntimeMetric(const vsock::Data &data) const
{
    return {};
}

metricid_t ResponseParser::parseId(const vsock::Data &data) const
{
    return 0;
}

}
