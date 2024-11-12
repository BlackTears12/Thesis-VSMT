#ifndef VSOCK_HEADERS_HPP
#define VSOCK_HEADERS_HPP

#include <sys/socket.h>

#if defined(__QNX__)
/* Platform is QNX */

#include <vm_sockets.h>

#else
/* Platform is linux */

#include <linux/vm_sockets.h>
#include <linux/virtio_vsock.h>

#endif

#endif // VSOCK_HEADERS_HPP
