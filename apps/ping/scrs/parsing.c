#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ping.h"

void print_usage(char *name)
{
	printf("Usage: %s [-v] [-?] destination\n", name);
}

int parse_args(int argc, char **argv, t_ping *ping)
{
	int opt;

	opterr = 0; 
	while ((opt = getopt(argc, argv, "v?")) != -1)
	{
		if (opt == 'v')
			ping->verbose = 1;
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
