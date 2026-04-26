#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include "net.h"
#include "icmp.h"
#include "ping.h"

int main(int argc, char **argv)
{
	t_ping ping = {0};
	int sock;
	struct icmphdr packet;

	if (parse_args(argc, argv, &ping) != 0)
	{
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (resolve_hostname(ping.dest_name, ping.dest_ip) != 0)
		exit(EXIT_FAILURE);

	init_address(&ping.dest_addr, ping.dest_ip);
	ping.id = getpid() & 0xFFFF;
	ping.seq = 0;

	if ((sock = create_raw_socket(IPPROTO_ICMP)) < 0)
		exit(EXIT_FAILURE);

	printf("PING %s (%s): 56 data bytes\n", ping.dest_name, ping.dest_ip);

	build_icmp_packet(&packet, ping.seq++, ping.id);

	if (sendto(sock, &packet, sizeof(packet), 0,
			   (struct sockaddr *)&ping.dest_addr, sizeof(ping.dest_addr)) <= 0)
	{
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	(void)ping.verbose;
	close(sock);
	return 0;
}
