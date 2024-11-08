#include "metrics.h"

namespace metrics
{

Metric::Metric(unique_ptr<metrics::RuntimeMetric> metric,metricid_t id_) : type(metric.get() ? RuntimeMetricRequest : Corrupt),data(std::move(metric)),id(id_)
{}

Metric::Metric(unique_ptr<metrics::SystemInfo> info,metricid_t id_) : type(info.get() ? SystemInfoRequest : Corrupt),data(std::move(info)),id(id_)
{}

}
