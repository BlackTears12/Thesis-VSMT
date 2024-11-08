#pragma once
#include <string>
#include <vector>

namespace util
{

/* Extend the lifetime of a std::unique_ptr until the end of scope */
#define KEEP_ALIVE(uniq_ptr) auto __keep_ALIVE__ptr__##uniq_ptr = std::move(uniq_ptr);

using std::string;

string getErrorStr() noexcept;

double average(std::vector<double> const &vec);

inline constexpr double normalizeFloat(const double v) { return ((int)(v*100) / 100); }

inline constexpr double percentof(const uint64_t &nom,const uint64_t denom) { return normalizeFloat(((double)nom/denom)*100); }

inline constexpr uint64_t byteToKb(const uint64_t &bytes) { return bytes/(1024*1024); }

}
