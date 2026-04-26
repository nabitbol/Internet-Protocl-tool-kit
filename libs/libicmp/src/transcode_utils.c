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

struct icmphdr *decode_datagram(uint64_t datagram)
{
	struct icmphdr *decoded_datagram = malloc(sizeof(struct icmphdr));

	if (!decoded_datagram)
		return NULL;

	decoded_datagram->type = (datagram & ICMP_TYPE_MASK) >> 56;
	decoded_datagram->code = (datagram & CODE_MASK) >> 48;
	decoded_datagram->checksum = (datagram & CHECKSUM_MASK) >> 32;
	decoded_datagram->un.echo.id = (datagram & ECHO_ID_MASK) >> 16;
	decoded_datagram->un.echo.sequence = (datagram & ECHO_SEQ_MASK);

	return decoded_datagram;
}
