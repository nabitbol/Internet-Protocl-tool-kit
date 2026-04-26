#include <string.h>
#include "ping.h"
#include "icmp.h"

void build_icmp_packet(struct icmphdr *icmp, int seq, int id)
{
	memset(icmp, 0, sizeof(struct icmphdr));

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = id;
	icmp->un.echo.sequence = seq;

	icmp->checksum = calculate_checksum(icmp, sizeof(struct icmphdr));
}
