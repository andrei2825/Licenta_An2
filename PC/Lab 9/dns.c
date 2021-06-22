// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result;

	// TODO: set hints
    hints.ai_family = AF_INET;    

	// TODO: get addresses
	ret = getaddrinfo(name, NULL, &hints, &result);
	if (ret < 0)
	{
		printf("eroare getIp");
		exit(0);
	} 
	
	char dest[10];
	// TODO: iterate through addresses and print them
	while (result != NULL)
	{
		inet_ntop(AF_INET, result->ai_addr, dest, sizeof(result->ai_addr));
		printf("%s\n", dest);
		result = result->ai_next;
	}
	
 
    freeaddrinfo(result);
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	// TODO: fill in address data
	addr.sin_family = AF_INET;
	inet_aton(ip, &addr.sin_addr);

	// TODO: get name and service
	ret = getnameinfo((struct sockaddr *) &addr, sizeof(struct sockaddr), host, sizeof(host), service, sizeof(service), 0);
	if (ret < 0)
	{
		printf("eraore getName");
		exit(0);
	}
	
	// TODO: print name and service
	printf("%s, %s", host, service);
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
