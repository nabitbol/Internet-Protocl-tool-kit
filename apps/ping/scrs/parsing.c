#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "ping.h"

void print_help(char *name)
{
	printf("Usage: %s [OPTION...] HOST\n", name);
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	printf("  -v, --verbose              verbose output\n");
	printf("      --ttl=N                set N as the packet time-to-live\n");
	printf("  -?, --help                 give this help list\n");
}

int parse_args(int argc, char **argv, t_ping *ping)
{
	int opt;
	static struct option long_options[] = {
		{"ttl", required_argument, 0, 1},
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, 0, '?'},
		{0, 0, 0, 0}};

	opterr = 0;
	while ((opt = getopt_long(argc, argv, "v?", long_options, NULL)) != -1)
	{
		if (opt == 'v')
			ping->verbose = 1;
		else if (opt == 1)
			ping->ttl = atoi(optarg);
		else if (opt == '?')
		{
			if (optopt == 0 || optopt == '?')
			{
				print_help(argv[0]);
				exit(EXIT_SUCCESS);
			}
			return -1;
		}
	}
	if (optind >= argc)
		return -1;

	ping->dest_name = argv[optind];
	return 0;
}
