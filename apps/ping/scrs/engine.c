#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include "ping.h"

static volatile sig_atomic_t keep_running = 1;

static void handle_sigint(int sig)
{
	(void)sig;
	keep_running = 0;
}

static void print_stats(t_ping *ping)
{
	printf("\n--- %s ping statistics ---\n", ping->dest_name);
	printf("%d packets transmitted, %d packets received\n",
		   ping->packets_sent, ping->packets_received);
}

static void receive_one_ping(t_ping *ping)
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
		return;

	ip = (struct iphdr *)buffer;
	icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));

	if (icmp->type == ICMP_ECHOREPLY && icmp->un.echo.id == ping->id)
	{
		ping->packets_received++;

		printf("%ld bytes from %s: icmp_seq=%d ttl=%d\n",
			   bytes_received - (ip->ihl * 4), ping->dest_ip,
			   icmp->un.echo.sequence, ip->ttl);
	}
}

static void wait_and_receive(t_ping *ping, struct timeval *last_send)
{
	struct timeval now, timeout;
	fd_set fd_read;
	long elapsed;

	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - last_send->tv_sec) * 1000000 + (now.tv_usec - last_send->tv_usec);

	if (elapsed >= 1000000)
		return;

	FD_ZERO(&fd_read);
	FD_SET(ping->sock, &fd_read);
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000000 - elapsed;

	if (select(ping->sock + 1, &fd_read, NULL, NULL, &timeout) > 0)
		receive_one_ping(ping);
}

static void send_one_ping(t_ping *ping)
{
	struct icmphdr packet;

	build_icmp_packet(&packet, ping->seq++, ping->id);

	if (sendto(ping->sock, &packet, sizeof(packet), 0,
			   (struct sockaddr *)&ping->dest_addr, sizeof(ping->dest_addr)) <= 0)
		perror("sendto");

	else
		ping->packets_sent++;
}

void start_ping_loop(t_ping *ping)
{
	struct timeval last_send, now;
	long elapsed;

	signal(SIGINT, handle_sigint);

	while (keep_running)
	{

		gettimeofday(&last_send, NULL);
		send_one_ping(ping);
		elapsed = 0;

		while (keep_running && elapsed < 1000000)
		{
			wait_and_receive(ping, &last_send);
			gettimeofday(&now, NULL);
			elapsed = (now.tv_sec - last_send.tv_sec) * 1000000 + (now.tv_usec - last_send.tv_usec);
		}
	}
	print_stats(ping);
}
