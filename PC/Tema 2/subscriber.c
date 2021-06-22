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
#include <netinet/tcp.h>


void usage(char *file)
{
	fprintf(stderr, "Usage: %s id_client server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	int sockfd, n, s, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];
	char *tok;
	char *request;
	char *topic;
	char *SF;
	struct UDP_message *messageFromServer;
	messageFromServer = malloc(sizeof(struct UDP_message));

	// ferificare argumente
	if (argc < 4) {
		usage(argv[0]);
	}
	DIE(strlen(argv[1]) > 10, "sizeId");

	// deschid socket spre server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[3]));
	ret = inet_aton(argv[2], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	// conectez clientul sa server
	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");
	int yes = 1;
	int result = setsockopt(sockfd,
                        IPPROTO_TCP,
                        TCP_NODELAY,
                        (char *) &yes, 
                        sizeof(int)); 
	
	// trimit id-ul clientului catre server
	ret = send(sockfd, argv[1], strlen(argv[1]) + 1, 0);
	DIE(ret < 0, "send id");
	fd_set tmp_fds;	
	while (1) {
		FD_SET(sockfd, &tmp_fds);
		FD_SET(STDIN_FILENO, &tmp_fds);
  		// se citeste de la tastatura
		ret = select(sockfd + STDIN_FILENO + 1, &tmp_fds, NULL, NULL, NULL);
		memset(buffer, 0, BUFLEN);
		DIE(ret < 0, "select");
		struct ClientRequest *req;
		// aloc memorie pentru variabila in care voi stoca requesturile
		req = malloc(sizeof(struct ClientRequest));
		
		if(FD_ISSET(STDIN_FILENO, &tmp_fds)){
			// daca primesc ceva de la STDIN merg pe una din ramurile urmatoare
			fgets(buffer, BUFLEN - 1, stdin);	
			request = strtok(buffer, " ");
			DIE(request == NULL, "request null pointer1");
			if (strncmp(request, "exit", 4) == 0) {
				// daca primesc comanda de exit, inchid clientul
				close(sockfd);
				break;
			}else if (strcmp(request, "unsubscribe") == 0) {
				//daca priemsc comanda de unsubscribe, adaug in request aceasta comanda
				strcpy(req->request, request);
				topic = strtok(NULL, " ");
				DIE(topic == NULL, "topic null pointer2");
				strncpy(req->topic, topic, strlen(topic) - 1);
				
			} else if (strcmp(request, "subscribe") == 0) {
				//daca priemsc comanda de subscribe, adaug in request aceasta comanda si adaug SF-ul dat
				strcpy(req->request, request);
				topic = strtok(NULL, " ");
				DIE(topic == NULL, "topic null pointer2");
				strcpy(req->topic, topic);
				
				SF = strtok(NULL, " ");
				DIE(SF == NULL, "sf null pointer3");
				if (SF[0] == '0') {
					req->SF = 0;
				} else {
					req->SF = 1;
				}
			} else {
				continue;
			}
			// trimit requestul catre server
			ret = send(sockfd, req, sizeof(struct ClientRequest), 0);
			DIE(ret < 0, "SENDING ERROR");
			// afisez requestul ales
			if (strcmp(req->request, "subscribe") == 0)
			{
				printf("Subscribed to %s.\n", req->topic);
			} else if (strcmp(req->request, "unsubscribe") == 0) {
				printf("Unsubscribed from %s.\n", req->topic);
			}
		} else {
			// daca primesc date de la server, le pun intr-o variabila de tip UDP_message
			s = recv(sockfd, messageFromServer, sizeof(buffer), 0);
			DIE(s < 0, "recv");
			if (strncmp(messageFromServer->topic, "exit", 4) == 0) {
				// daca primesc comanda de exit, inchi clientul
				break;
			}
			//in functie de tipul de data a mesajului primit, afisez mesajul primit de la server in modul corespunzator
			if(strlen(messageFromServer->topic) > 0) {
				switch (messageFromServer->data_type) {
					case 0: {
						printf("%s:%s - %s - %s - %d\n", messageFromServer->ip, messageFromServer->port, messageFromServer->topic, messageFromServer->type, messageFromServer->integer);
						break;
					}	
					case 1: {
						printf("%s:%s - %s - %s - %.2f\n", messageFromServer->ip, messageFromServer->port, messageFromServer->topic, messageFromServer->type, messageFromServer->short_int);
						break;
					}
					case 2: {
						printf("%s:%s - %s - %s - %f\n", messageFromServer->ip, messageFromServer->port, messageFromServer->topic, messageFromServer->type,messageFromServer->fl);
						break;
					}
					case 3: {
						printf("%s:%s - %s - %s - %s\n", messageFromServer->ip, messageFromServer->port, messageFromServer->topic, messageFromServer->type,messageFromServer->msg);
						break;
					}
					default: break;
				}
			}
		}
	}

	close(sockfd);

	return 0;
}
