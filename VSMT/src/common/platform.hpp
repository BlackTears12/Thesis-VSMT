#ifndef PLATFORM_H
#define PLATFORM_H

enum Platform {
    Linux = 1,
    QNX = 2
};

#if defined(__QNX__)

namespace platform { const constexpr Platform current = Platform::QNX; }


#elif defined(__linux__)

namespace platform { const constexpr Platform current = Platform::Linux; }

#else

#error "Unknown platform"

#endif

#endif // PLATFORM_H
