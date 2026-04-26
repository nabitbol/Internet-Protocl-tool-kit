#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include "ping.h"

int receive_ping(t_ping *ping)
{
	char buffer[1024];
	struct sockaddr_in from;
	socklen_t from_len = sizeof(from);
	ssize_t bytes_received;
	struct iphdr *ip;
	struct icmphdr *icmp;

	bytes_received = recvfrom(ping->sock, buffer, sizeof(buffer), 0,
							  (struct sockaddr *)&from, &from_len);

	if (bytes_received < 0)
		return -1;

	ip = (struct iphdr *)buffer;
	icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));

	if (icmp->type == ICMP_ECHOREPLY && icmp->un.echo.id == ping->id)
	{
		ping->packets_received++;
		printf("%ld bytes from %s: icmp_seq=%d ttl=%d\n",
			   bytes_received - (ip->ihl * 4),
			   ping->dest_ip,
			   icmp->un.echo.sequence,
			   ip->ttl);
		return 0;
	}

	return -1;
}
