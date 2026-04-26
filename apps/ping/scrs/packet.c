#include <string.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "ping.h"
#include "icmp.h"

void build_icmp_packet(void *buf, int seq, int id)
{
	struct icmphdr tmp;
	uint64_t encoded;
	struct timeval *tv;
	unsigned char *ptr = (unsigned char *)buf;

	memset(&tmp, 0, sizeof(tmp));
	tmp.type = ICMP_ECHO;
	tmp.code = 0;
	tmp.un.echo.id = id;
	tmp.un.echo.sequence = seq;
	tmp.checksum = 0;

	memset(buf, 0, PACKET_SIZE);
	encoded = encode_datagram(tmp);
	for (int i = 0; i < 8; i++)
		ptr[i] = (encoded >> (56 - (i * 8))) & 0xFF;

	tv = (struct timeval *)(buf + 8);
	gettimeofday(tv, NULL);
	for (size_t i = 8 + sizeof(struct timeval); i < PACKET_SIZE; i++)
		((char *)buf)[i] = i;

	tmp.checksum = htons(calculate_checksum(buf, PACKET_SIZE));

	encoded = encode_datagram(tmp);
	for (int i = 0; i < 8; i++)
		ptr[i] = (encoded >> (56 - (i * 8))) & 0xFF;
}
