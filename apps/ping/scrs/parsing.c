#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "ping.h"

void print_usage(char *name)
{
	printf("Usage: %s [-v] [-?] [--ttl=N] destination\n", name);
}

int parse_args(int argc, char **argv, t_ping *ping)
{
	int opt;
	int option_index = 0;
	static struct option long_options[] = {
		{"ttl", required_argument, 0, 't'},
		{0, 0, 0, 0}
	};

	opterr = 0; 
	while ((opt = getopt_long(argc, argv, "v?", long_options, &option_index)) != -1)
	{
		if (opt == 'v')
			ping->verbose = 1;
		else if (opt == 't')
			ping->ttl = atoi(optarg);
		else if (opt == '?' && optopt == 0)
		{
			print_usage(argv[0]);
			exit(EXIT_SUCCESS);
		}
		else
			return -1;
	}
	if (optind >= argc)
		return -1;
	ping->dest_name = argv[optind];
	return 0;
}
