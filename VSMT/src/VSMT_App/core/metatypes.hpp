#ifndef METATYPES_HPP
#define METATYPES_HPP

#include "clientdispatcher.hpp"
#include <memory>

Q_DECLARE_METATYPE(common::client_id);
Q_DECLARE_METATYPE(std::shared_ptr<metrics::RuntimeMetric>);

#endif // METATYPES_HPP
