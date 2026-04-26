#ifndef PING_H
#define PING_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <sys/time.h>

#define PAYLOAD_SIZE 56
#define PACKET_SIZE (sizeof(struct icmphdr) + PAYLOAD_SIZE)

typedef struct s_ping
{
	int verbose;
	int ttl;
	int seq;
	int id;
	int packets_sent;
	int packets_received;
	char *dest_name;
	char dest_ip[INET_ADDRSTRLEN];
	struct sockaddr_in dest_addr;
	int sock;
	
	double min_rtt;
	double max_rtt;
	double sum_rtt;
	double sum_sq_rtt;
	struct timeval start_time;
} t_ping;

void print_help(char *name);
int parse_args(int argc, char **argv, t_ping *ping);
void build_icmp_packet(void *buf, int seq, int id);
void start_ping_loop(t_ping *ping);

#endif
