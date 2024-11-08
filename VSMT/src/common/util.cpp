#include "util.hpp"
#include <errno.h>
#include <cstring>
#include <numeric>

namespace util
{

string getErrorStr() noexcept
{
    return string(strerror(errno));
}

double average(const std::vector<double> &vec)
{
    if(vec.empty())
        return 0;
    return std::reduce(vec.begin(),vec.end()) / (double)vec.size();
}


}
