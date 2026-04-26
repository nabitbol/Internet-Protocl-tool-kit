#include <icmp.h>

static const char *icmp_messages[] = {
	[ICMP_ECHOREPLY] = "Echo Reply",
	[ICMP_DEST_UNREACH] = "Destination Unreachable",
	[ICMP_SOURCE_QUENCH] = "Source Quench",
	[ICMP_REDIRECT] = "Redirect (change route)",
	[ICMP_ECHO] = "Echo Request",
	[ICMP_TIME_EXCEEDED] = "Time Exceeded",
	[ICMP_PARAMETERPROB] = "Parameter Problem",
	[ICMP_TIMESTAMP] = "Timestamp Request",
	[ICMP_TIMESTAMPREPLY] = "Timestamp Reply",
	[ICMP_INFO_REQUEST] = "Information Request",
	[ICMP_INFO_REPLY] = "Information Reply",
	[ICMP_ADDRESS] = "Address Mask Request",
	[ICMP_ADDRESSREPLY] = "Address Mask Reply"
};

void print_icmp(uint8_t icmp_type)
{
	if (icmp_type < (sizeof(icmp_messages) / sizeof(char *)) && icmp_messages[icmp_type])
		printf("%s\n", icmp_messages[icmp_type]);
	else
		printf("Unknown ICMP type: %u\n", icmp_type);
}
