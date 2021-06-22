/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	client mini-server de backup fisiere
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "helpers.h"

void usage(char*file)
{
	fprintf(stderr,"Usage: %s ip_server port_server file\n",file);
	exit(0);
}

/*
*	Utilizare: ./client ip_server port_server nume_fisier_trimis
*/
int main(int argc,char**argv)
{
	if (argc!=4)
		usage(argv[0]);
	
	int fd;
	struct sockaddr_in to_station;
	char buf[BUFLEN];


	/*Deschidere socket*/
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == 0) {
		printf("SOCKET ERROR");
		exit(0);
	}

	
	/* Deschidere fisier pentru citire */
	DIE((fd=open(argv[3],O_RDONLY))==-1,"open file");
	
	/*Setare struct sockaddr_in pentru a specifica unde trimit datele*/
	to_station.sin_family = AF_INET;
	to_station.sin_port = htons(atoi(argv[2]));
	
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din fisier
	*		trimite pe socket
	*/	
	int in, size;;
	while(1) {
		DIE((in = read(fd, buf, BUFLEN)) < 0, "ERROR");
		DIE((size = sendto(sockfd, buf, in, 0, (struct socketaddr *)&to_station, sizeof(to_station))) < 0, "SEND ERROR");
		if(size == 0) {
			break;
		}
	}
	/*Inchidere socket*/
	close(sockfd);
	
	/*Inchidere fisier*/
	close(fd);
	return 0;
}
