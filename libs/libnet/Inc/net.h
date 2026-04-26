#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int create_raw_socket(int protocol);
int resolve_hostname(const char *hostname, char *ip_str);
int set_socket_ttl(int sock, int ttl);
void init_address(struct sockaddr_in *addr, const char *ip_str);

#endif
