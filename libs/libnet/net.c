#include "Inc/net.h"

int create_raw_socket(int protocol)
{
	int sock;

	sock = socket(AF_INET, SOCK_RAW, protocol);
	if (sock < 0)
	{
		perror("socket");
		return -1;
	}
	return sock;
}

int resolve_hostname(const char *hostname, char *ip_str)
{
	struct addrinfo hints, *res;
	struct sockaddr_in *ipv4;
	int status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_RAW;

	if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0)
		return -1;

	ipv4 = (struct sockaddr_in *)res->ai_addr;
	if (inet_ntop(res->ai_family, &(ipv4->sin_addr), ip_str, INET_ADDRSTRLEN) == NULL)
	{
		perror("inet_ntop");
		freeaddrinfo(res);
		return -1;
	}

	freeaddrinfo(res);
	return 0;
}

int set_socket_ttl(int sock, int ttl)
{
	if (setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
	{
		perror("setsockopt (IP_TTL)");
		return -1;
	}
	return 0;
}

void init_address(struct sockaddr_in *addr, const char *ip_str)
{
	memset(addr, 0, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	inet_pton(AF_INET, ip_str, &addr->sin_addr);
}
