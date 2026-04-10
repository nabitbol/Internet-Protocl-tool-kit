#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>

// Masks (Assuming: Type(8) | Code(8) | Checksum(16) | Rest(32))
#define ICMP_TYPE_MASK 0xFF00000000000000ULL
#define CODE_MASK 0x00FF000000000000ULL
#define CHECKSUM_MASK 0x0000FFFF00000000ULL
#define ECHO_ID_MASK 0x00000000FFFF0000ULL
#define ECHO_SEQ_MASK 0x000000000000FFFFULL

uint64_t encode_datagram(struct icmphdr icmphdr);
struct icmphdr *decode_datagram(uint64_t datagram);
void print_icmp(uint8_t icmp_type);
void print_bits(uint64_t value);

#endif
