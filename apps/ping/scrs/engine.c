#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include "ping.h"
#include "icmp.h"

static volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig)
{
	(void)sig;
	keep_running = 0;
}

static double ft_sqrt(double n)
{
	double x = n, y = 1, e = 0.000001;
	if (n < 0) return 0;
	while (x - y > e) { x = (x + y) / 2; y = n / x; }
	return x;
}

static void print_stats(t_ping *p)
{
	double avg, mdev, var;
	printf("\n--- %s ping statistics ---\n", p->dest_name);
	printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n",
	       p->packets_sent, p->packets_received,
	       (p->packets_sent > 0) ? ((p->packets_sent - p->packets_received) / (double)p->packets_sent) * 100 : 0);
	if (p->packets_received > 0)
	{
		avg = p->sum_rtt / p->packets_received;
		var = (p->sum_sq_rtt / p->packets_received) - (avg * avg);
		mdev = ft_sqrt(var);
		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", p->min_rtt, avg, p->max_rtt, mdev);
	}
}

static void receive_one_ping(t_ping *p)
{
	char buf[1024];
	struct sockaddr_in f;
	socklen_t fl = sizeof(f);
	struct iphdr *ip;
	struct icmphdr ic;
	uint64_t raw_ic = 0;
	struct timeval *tv_s, tv_r;
	double rtt;

	if (recvfrom(p->sock, buf, sizeof(buf), 0, (struct sockaddr *)&f, &fl) < 0) return;
	gettimeofday(&tv_r, NULL);
	ip = (struct iphdr *)buf;
	for (int i = 0; i < 8; i++)
		raw_ic |= (uint64_t)((unsigned char)buf[(ip->ihl * 4) + i]) << (56 - (i * 8));
	decode_datagram(raw_ic, &ic);
	if (ic.type == ICMP_ECHOREPLY && ic.un.echo.id == p->id)
	{
		p->packets_received++;
		tv_s = (struct timeval *)(buf + (ip->ihl * 4) + sizeof(struct icmphdr));
		rtt = (tv_r.tv_sec - tv_s->tv_sec) * 1000.0 + (tv_r.tv_usec - tv_s->tv_usec) / 1000.0;
		if (p->packets_received == 1 || rtt < p->min_rtt) p->min_rtt = rtt;
		if (p->packets_received == 1 || rtt > p->max_rtt) p->max_rtt = rtt;
		p->sum_rtt += rtt; p->sum_sq_rtt += rtt * rtt;
		printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n", p->dest_ip, ic.un.echo.sequence, ip->ttl, rtt);
	}
	else if (p->verbose)
	{
		char pr_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &f.sin_addr, pr_ip, INET_ADDRSTRLEN);
		printf("From %s: ", pr_ip);
		print_icmp(ic.type);
	}
}

void start_ping_loop(t_ping *p)
{
	struct timeval ls, now, to;
	fd_set r;
	char buf[PACKET_SIZE];

	signal(SIGINT, handle_sigint);
	while (keep_running)
	{
		gettimeofday(&ls, NULL);
		build_icmp_packet(buf, p->seq++, p->id);
		if (sendto(p->sock, buf, PACKET_SIZE, 0, (struct sockaddr *)&p->dest_addr, sizeof(p->dest_addr)) > 0) p->packets_sent++;
		long el = 0;
		while (keep_running && el < 1000000)
		{
			gettimeofday(&now, NULL);
			el = (now.tv_sec - ls.tv_sec) * 1000000 + (now.tv_usec - ls.tv_usec);
			if (el >= 1000000) break;
			FD_ZERO(&r); FD_SET(p->sock, &r);
			to.tv_sec = 0; to.tv_usec = 1000000 - el;
			if (select(p->sock + 1, &r, NULL, NULL, &to) > 0) receive_one_ping(p);
		}
	}
	print_stats(p);
}
