#include "icmp.h"

uint16_t calculate_checksum(void *addr, int len)
{
	uint32_t sum = 0;
	uint16_t *ptr = addr;

	// Sum 16-bit words
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}

	// Add left-over byte, if any (padding with 0)
	if (len == 1)
		sum += *(uint8_t *)ptr;

	// Fold 32-bit sum to 16 bits (add carries)
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	// Final bitwise NOT (one's complement)
	return (uint16_t)~sum;
}
