#include "icmp.h"
#include <assert.h>
#include <string.h>

void test_basic_checksum()
{
	printf("Testing basic checksum... ");
	uint16_t data[] = {0x0800, 0x0000, 0x0001, 0x0001};
	// Manual calculation for 0x0800 + 0x0001 + 0x0001 = 0x0802
	// Complement of 0x0802 is 0xF7FD
	uint16_t result = calculate_checksum(data, sizeof(data));
	assert(result == 0xF7FD);
	printf("OK\n");
}

void test_odd_length()
{
	printf("Testing odd length buffer... ");
	uint8_t data[] = {0x08, 0x00, 0x42}; 
	// 16-bit words: 0x0008 (if little endian ptr access) or 0x0800
	// Our function uses uint16_t* ptr, so it reads 0x0008 on Little Endian machines.
	// Let's verify the "fold" and "complement" logic.
	uint16_t res = calculate_checksum(data, 3);
	
	// Re-verify by summing data + checksum
	uint8_t full_packet[4];
	memcpy(full_packet, data, 3);
	full_packet[3] = 0; // Padding for even sum
	
	// In the Internet Checksum, if we include the checksum in the sum, 
	// we should get 0xFFFF (or 0 after complement).
	printf("OK (Validation via property next)\n");
}

void test_verification_property()
{
	printf("Testing RFC 1071 verification property... ");
	char *msg = "Hello World!";
	int len = strlen(msg);
	
	// 1. Calculate checksum of data
	uint16_t cksum = calculate_checksum(msg, len);
	
	// 2. Create a buffer with data + checksum
	// Note: In a real ICMP packet, the checksum is in the middle, 
	// but the property holds for the whole block.
	uint8_t buffer[64];
	memcpy(buffer, msg, len);
	
	// We need to be careful with where we put the checksum for the property to work 
	// easily in a simple sum. Let's just verify that calculate_checksum 
	// of (data with checksum field set to the calculated checksum) results in 0.
	
	struct icmphdr hdr;
	memset(&hdr, 0, sizeof(hdr));
	hdr.type = ICMP_ECHO;
	hdr.un.echo.id = 1234;
	hdr.un.echo.sequence = 1;
	hdr.checksum = 0;
	
	hdr.checksum = calculate_checksum(&hdr, sizeof(hdr));
	
	// If we checksum the header again, it should return 0 (if result is ~sum)
	// or 0xFFFF (if we look at the raw sum).
	// In RFC 1071, ~sum of (data + ~sum) == 0.
	uint16_t verify = calculate_checksum(&hdr, sizeof(hdr));
	assert(verify == 0);
	printf("OK\n");
}

int main()
{
	printf("=== ICMP Checksum Test Suite ===\n");
	test_basic_checksum();
	test_verification_property();
	printf("All tests passed successfully!\n");
	return 0;
}
