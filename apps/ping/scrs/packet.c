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

	memset(&tmp, 0, sizeof(tmp));
	tmp.type = ICMP_ECHO;
	tmp.code = 0;
	tmp.un.echo.id = id;
	tmp.un.echo.sequence = seq;

	// On calcule d'abord le checksum sur un buffer temporaire
	memset(buf, 0, PACKET_SIZE);
	memcpy(buf, &tmp, sizeof(tmp));
	tv = (struct timeval *)(buf + sizeof(struct icmphdr));
	gettimeofday(tv, NULL);
	tmp.checksum = calculate_checksum(buf, PACKET_SIZE);

	// On utilise ton encodeur de libicmp
	encoded = encode_datagram(tmp);
	
	// On place les 64 bits encodés en respectant l'ordre réseau (Big Endian)
	// Ton encodeur place le Type à << 56, ce qui doit être le premier octet.
	for (int i = 0; i < 8; i++)
	{
		((unsigned char *)buf)[i] = (encoded >> (56 - (i * 8))) & 0xFF;
	}
}
