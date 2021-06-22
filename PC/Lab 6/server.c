/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
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
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	if (argc!=3)
		usage(argv[0]);
	
	struct sockaddr_in my_sockaddr, from_station ;
	char buf[BUFLEN];


	/*Deschidere socket*/
	int sck = socket(AF_INET, SOCK_DGRAM, 0);
	if(sck < 0) {
		printf("SOCKET ERROR");
		exit(0);
	}

	
	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
	from_station.sin_family = AF_INET;
	from_station.sin_port = htons(atoi(argv[1]));
	from_station.sin_addr.s_addr = INADDR_ANY;
	
	/* Legare proprietati de socket */
	bind(sck, (struct sockaddr *)&from_station, sizeof(from_station));
	
	
	/* Deschidere fisier pentru scriere */
	DIE((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/
	int size;
	while(1) {
		socklen_t len = sizeof(from_station);
		DIE((size = recvfrom(sck, buf, BUFLEN, 0, (struct sockaddr*)&from_station, (socklen_t *)&len)) == -1, "ERROR");
		write(fd, buf, size);
		if(size == 0) {
			break;
		}
	}
	/*Inchidere socket*/	
	close(sck);
	
	/*Inchidere fisier*/
	close(fd);
	return 0;
}
