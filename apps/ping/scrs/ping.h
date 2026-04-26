#ifndef PING_H
#define PING_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <signal.h>

typedef struct s_ping
{
	int verbose;
	int seq;
	int id;
	int packets_sent;
	int packets_received;
	char *dest_name;
	char dest_ip[INET_ADDRSTRLEN];
	struct sockaddr_in dest_addr;
	int sock;
} t_ping;

void print_usage(char *name);
int parse_args(int argc, char **argv, t_ping *ping);
void build_icmp_packet(struct icmphdr *icmp, int seq, int id);
void start_ping_loop(t_ping *ping);

#endif
