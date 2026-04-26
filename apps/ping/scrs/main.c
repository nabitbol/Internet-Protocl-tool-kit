#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include "net.h"
#include "icmp.h"
#include "ping.h"

int main(int argc, char **argv)
{
	t_ping ping = {0};

	if (parse_args(argc, argv, &ping) != 0)
	{
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (resolve_hostname(ping.dest_name, ping.dest_ip) != 0)
	{
		fprintf(stderr, "%s: unknown host %s\n", argv[0], ping.dest_name);
		exit(EXIT_FAILURE);
	}

	init_address(&ping.dest_addr, ping.dest_ip);
	ping.id = getpid() & 0xFFFF;

	if ((ping.sock = create_raw_socket(IPPROTO_ICMP)) < 0)
		exit(EXIT_FAILURE);

	if (ping.ttl == 0)
		ping.ttl = 64;
	
	if (set_socket_ttl(ping.sock, ping.ttl) != 0)
		exit(EXIT_FAILURE);

	printf("PING %s (%s): 56 data bytes\n", ping.dest_name, ping.dest_ip);

	start_ping_loop(&ping);

	close(ping.sock);
	return 0;
}
