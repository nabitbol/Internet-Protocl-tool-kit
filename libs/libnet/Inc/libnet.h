#ifndef LIBNET_H
#define LIBNET_H

#include <stdint.h>

int64_t sendIcmpDatagram(int host, int64_t datagram);
int64_t receivIcmpDatagram();

#endif
