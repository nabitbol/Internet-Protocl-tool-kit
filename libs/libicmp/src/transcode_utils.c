#include <icmp.h>

void print_bits(uint64_t value)
{
	for (int i = 63; i >= 0; i--)
	{
		// Shift '1' to the left i times to create a mask, then bitwise AND
		unsigned char bit = (value >> i) & 1;
		printf("%u", bit);
	}
	printf(" ");
}

uint64_t encode_datagram(struct icmphdr datagram)
{
	uint64_t encoded_datagram = 0;

	encoded_datagram |= (uint64_t)datagram.type << 56;
	encoded_datagram |= (uint64_t)datagram.code << 48;
	encoded_datagram |= (uint64_t)datagram.checksum << 32;
	encoded_datagram |= (uint64_t)datagram.un.echo.id << 16;
	encoded_datagram |= (uint64_t)datagram.un.echo.sequence;
	return encoded_datagram;
}

void decode_datagram(uint64_t datagram, struct icmphdr *res)
{
	if (!res)
		return;
	res->type = (datagram & ICMP_TYPE_MASK) >> 56;
	res->code = (datagram & CODE_MASK) >> 48;
	res->checksum = (datagram & CHECKSUM_MASK) >> 32;
	res->un.echo.id = (datagram & ECHO_ID_MASK) >> 16;
	res->un.echo.sequence = (datagram & ECHO_SEQ_MASK);
}
