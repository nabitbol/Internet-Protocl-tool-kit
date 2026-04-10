#include <icmp.h>

char **get_icmp_logs()
{
	char **logs = (char **)malloc(sizeof(char *) * 19);

	logs[ICMP_ECHOREPLY] = "Echo Reply\n";
	logs[ICMP_DEST_UNREACH] = "Destination Unreachable\n";
	logs[ICMP_SOURCE_QUENCH] = "Source Quench\n";
	logs[ICMP_REDIRECT] = "Redirect (change route)\n";
	logs[ICMP_ECHO] = "Echo Request\n";
	logs[ICMP_TIME_EXCEEDED] = "Time Exceeded\n";
	logs[ICMP_PARAMETERPROB] = "Parameter Problem\n";
	logs[ICMP_TIMESTAMP] = "Timestamp Request\n";
	logs[ICMP_TIMESTAMPREPLY] = "Timestamp Reply\n";
	logs[ICMP_INFO_REQUEST] = "Information Request\n";
	logs[ICMP_INFO_REPLY] = "Information Reply\n";
	logs[ICMP_ADDRESS] = "Address Mask Request\n";
	logs[ICMP_ADDRESSREPLY] = "Address Mask Reply\n";

	return logs;
}

void print_icmp(uint8_t icmp_type)
{
	char **logs = get_icmp_logs();

	printf("%s\n", logs[icmp_type]);
}
