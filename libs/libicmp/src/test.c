#include <icmp.h>

int main()
{
	struct icmphdr datagram = {
		.type = ICMP_ECHOREPLY,
		.code = 7,
		.checksum = 5,
		.un.echo.id = 5,
		.un.echo.sequence = 7,
	};
	uint64_t test = encode_datagram(datagram);
	printf("%ld\n", test);
	print_bits(test);

	struct icmphdr *decoded_datagram = decode_datagram(test);
	print_bits(decoded_datagram->type);
	printf("\ntype %d\n", decoded_datagram->type);
	printf("code %d\n", decoded_datagram->code);
	printf("checksum %d\n", decoded_datagram->checksum);
	printf("echo id %d\n", decoded_datagram->un.echo.id);
	printf("echo seq %d\n", decoded_datagram->un.echo.sequence);

	print_icmp(datagram.type);
}
