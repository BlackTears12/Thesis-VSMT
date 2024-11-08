#include "util.h"
#include <errno.h>
#include <cstring>

namespace util
{

string getErrorStr() noexcept
{
    return string(strerror(errno));
}


}
