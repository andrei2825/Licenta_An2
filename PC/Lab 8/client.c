#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, n, s, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];

	if (argc < 3) {
		usage(argv[0]);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	ret = inet_aton(argv[1], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");
	fd_set tmp_fds;	
	
	while (1) {
		FD_SET(sockfd, &tmp_fds);
		FD_SET(STDIN_FILENO, &tmp_fds);
  		// se citeste de la tastatura
		ret = select(sockfd + STDIN_FILENO + 1, &tmp_fds, NULL, NULL, NULL);
		memset(buffer, 0, BUFLEN);
		DIE(ret < 0, "select");
		if(FD_ISSET(STDIN_FILENO, &tmp_fds)){
			fgets(buffer, BUFLEN - 1, stdin);
			if (strncmp(buffer, "exit", 4) == 0) {
				break;
			}
			// se trimite mesaj la server
			n = send(sockfd, buffer, sizeof(buffer), 0);
			DIE(n < 0, "send");
		} else {
			s = recv(sockfd, buffer, sizeof(buffer), 0);
			DIE(s < 0, "recv");
			printf("Mesaj primit: %s", buffer);
		}
		
	}

	close(sockfd);

	return 0;
}
