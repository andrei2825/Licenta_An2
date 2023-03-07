#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include "helpers.h"
//Am introdus aceasta functie pentru a transforma portul clientilor UDP. 
//Pentru un motiv sau altul, nu am reusit sa il transfer sub forma de int.
char* itoa(int num, char* buffer, int base)   
{  
    int current = 0;  
    if (num == 0) {  
        buffer[current++] = '0';  
        buffer[current] = '\0';  
        return buffer;  
    }  
    int num_digits = 0;  
    if (num < 0) {  
        if (base == 10) {  
            num_digits ++;  
            buffer[current] = '-';  
            current ++;  
            num *= -1;  
        }  
        else  
            return NULL;  
    }  
    num_digits += (int)floor(log(num) / log(base)) + 1;  
    while (current < num_digits)   
    {  
        int base_val = (int) pow(base, num_digits-1-current);  
        int num_val = num / base_val;  
         char value = num_val + '0';  
        buffer[current] = value;  
        current ++;  
        num -= base_val * num_val;  
    }  
    buffer[current] = '\0';  
    return buffer;  
} 

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	int sockTCP, sockUDP, newsockfd, portno, n, i, ret, s;
	int fdmax;			// valoare maxima fd din multimea read_fds
	int numSoc = 0;     // numarul de poeturi deschise (necesar pentru exit)
	int numClients = 0;	// numar total de clienti conectati(nu scade odata cu deconectarea clientilor)
	int position = 0;	// pozitia ultimului client conectat
	int checkId;		
	
	uint8_t dataType;
	char buffer[BUFLEN];
	struct ClientRequest *req;
	struct sockaddr_in serv_addr, cli_addr;
	req = malloc(sizeof(struct ClientRequest));
	struct Client **clients;
	clients = malloc(sizeof(struct Client*));
	struct Client *tmpClient;

	socklen_t clilen;

	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar

	if (argc < 2) {
		usage(argv[0]);
	}

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	// deschid socketii pentru TCP si UDP
	sockTCP = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockTCP < 0, "sockTCP");
	sockUDP = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sockUDP < 0, "sockUDP");

	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// leg socketii de adresa serverului
	ret = bind(sockTCP, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind tcp");
	ret = bind(sockUDP, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind udp");

	ret = listen(sockTCP, MAX_CLIENTS);
	DIE(ret < 0, "listen");

	// se adauga noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
	FD_SET(sockTCP, &read_fds);
	FD_SET(sockUDP, &read_fds);
	FD_SET(STDIN_FILENO, &tmp_fds);
	if (sockTCP > sockUDP) {
		fdmax = sockTCP;
	} else {
		fdmax = sockUDP;
	}
	while (1) {
		tmp_fds = read_fds; 
		FD_SET(sockUDP, &read_fds);
		FD_SET(STDIN_FILENO, &tmp_fds);
		memset(buffer, 0, BUFLEN);
		ret = select(fdmax + STDIN_FILENO + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");
		struct UDP_message *udpMessage;
		udpMessage = malloc(sizeof(struct UDP_message));
		if (FD_ISSET(STDIN_FILENO, &tmp_fds)) {
			fgets(buffer, BUFLEN - 1, stdin);
			// daca primesc mesajul exit de la STDIN, trimit un mesaj de exit tuturor clientilor
			if (strncmp(buffer, "exit", 4) == 0) {
				for (int j = 0; j < numSoc; j++)
				{
					s = send(clients[j]->soc, "exit", 4, 0);
					DIE(s < 0, "send");
				}
				break;
			}
		} else {
			for (i = 0; i <= fdmax; i++) {
				if (FD_ISSET(i, &tmp_fds)) {
					if (i == sockTCP) {
						// a venit o cerere de conexiune pe socketul inactiv (cel cu listen),
						// pe care serverul o accepta
						position = numClients;
						clilen = sizeof(cli_addr);
						newsockfd = accept(sockTCP, (struct sockaddr *) &cli_addr, &clilen);
						DIE(newsockfd < 0, "accept");

						// se adauga noul socket intors de accept() la multimea descriptorilor de citire
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) { 
							fdmax = newsockfd;
						}	
						// initializez valorile pentru noul client si ii aloc memorie			
						tmpClient = malloc(sizeof(struct Client));
						clients[position] = tmpClient;
						clients[position]->soc = newsockfd;
						clients[position]->numTopics = 0;
						clients[position]->numMessages = 0;
						clients[position]->topics = malloc(sizeof(struct Topic));
						clients[position]->messages = malloc(sizeof(struct UDP_message));
						clients[position]->status = 1;
						numSoc++;
						numClients++;
					}else if(i == sockUDP) {
						// daca primesc mesaj de la clientii UDP, separ mesajul in bucati folosind memset
						// si pun datele preluate din mesaj intr-o valiabila udpMessage de tip UDP_message 
						memset(buffer, 0, BUFLEN);
						recvfrom(sockUDP, buffer, BUFLEN, 0, (struct sockaddr*) &serv_addr, 0);
						memset(udpMessage->topic, 0, 51);
						memcpy(udpMessage->topic, buffer, 50);
						strcpy(udpMessage->ip, inet_ntoa(cli_addr.sin_addr));
						itoa(ntohs(cli_addr.sin_port), udpMessage->port, 10);
						dataType = buffer[50];
						udpMessage->data_type = dataType;
						// in functie de tipul de data promit, separ diferit ultima sectiune din mesaj,
						// conform tabelului din enunt
						if (dataType == 0) {
							int sign = buffer[51];
							uint32_t data;
							memset(&data, 0, sizeof(uint32_t));
							memcpy(&data, buffer + 52, sizeof(uint32_t));
							udpMessage->integer = ntohl(data);
							if (sign == 1) {
								udpMessage->integer = udpMessage->integer * (-1);
							}
							strcpy(udpMessage->type, "INT");

						} else if (dataType == 1) {
							uint16_t data;
							memset(&data, 0, sizeof(uint16_t));
							memcpy(&data, buffer + 51, sizeof(uint16_t));
							udpMessage->short_int = (float)ntohl(data)/100;
							strcpy(udpMessage->type, "SHORT_REAL");
						} else if (dataType == 2) {
							int sign = buffer[51];
							uint32_t data;
							memset(&data, 0, sizeof(uint32_t));
							memcpy(&data, buffer+52, sizeof(uint32_t));
							uint8_t exponential;
							memset(&exponential, 0, sizeof(uint8_t));
							memcpy(&exponential, buffer+52 + sizeof(uint32_t), sizeof(uint8_t));
							udpMessage->fl = ntohl(data) / (pow(10, exponential));
							if (sign == 1){
								udpMessage->fl = udpMessage->fl * (-1);
							}
							strcpy(udpMessage->type, "FLOAT");
						} else if(dataType == 3) {
							memset(udpMessage->msg, 0, 1500);
							memcpy(udpMessage->msg, buffer + 51, 1501);
							strcpy(udpMessage->type, "STRING");
						}
						for (int j = 0; j < numClients; j++)
						{
							for (int k = 0; k < clients[j]->numTopics; k++)
							{
								if (strcmp(clients[j]->topics[k].topic, udpMessage->topic) == 0) {
								 	if(clients[j]->status == 1) {
										 // daca clientul este online si este abonat la topicul mesajului mrimit, ii este 
										 // trimis mesajul
										s = send(clients[j]->soc, udpMessage, sizeof(struct UDP_message), 0);
										DIE(s < 0, "send");
										break;
									} else if(clients[j]->topics[k].SF == 1) {
										// daca acesta este offline, dar are SF-ul topicului setat pe 1, 
										// retin mesajul int-un array
										void *tmpPtr = realloc(clients[j]->messages, sizeof(clients[j]->messages) + sizeof(struct UDP_message));
										clients[j]->messages = tmpPtr;
										clients[j]->messages[clients[j]->numMessages].data_type = udpMessage->data_type;
										clients[j]->messages[clients[j]->numMessages].fl = udpMessage->fl;
										clients[j]->messages[clients[j]->numMessages].integer = udpMessage->integer;
										clients[j]->messages[clients[j]->numMessages].short_int = udpMessage->short_int;
										strcpy(clients[j]->messages[clients[j]->numMessages].ip, udpMessage->ip);
										strcpy(clients[j]->messages[clients[j]->numMessages].msg, udpMessage->msg);
										strcpy(clients[j]->messages[clients[j]->numMessages].port, udpMessage->port);
										strcpy(clients[j]->messages[clients[j]->numMessages].topic, udpMessage->topic);
										strcpy(clients[j]->messages[clients[j]->numMessages].type, udpMessage->type);
										clients[j]->numMessages++;
									}
								}
							}
							
						}
					} else {
						 
						// s-au primit date pe unul din socketii de client,
						// asa ca serverul trebuie sa le receptioneze
						memset(buffer, 0, BUFLEN);
						n = recv(i, req, sizeof(struct ClientRequest), 0);
						DIE(n < 0, "recv");
						if (n == 0) {
							// conexiunea s-a inchis
							if (clients[position]->copy != 1)
							{
								printf("Client %s disconnected.\n", clients[position]->ID);
								
							}
							clients[position]->status = 0;
							close(i);
							
							// se scoate din multimea de citire socketul inchis 
							FD_CLR(i, &read_fds);
						} else {
							if(strncmp(req->request, "subscribe", 9) == 0) {
								// daca se primeste comanda de subscribe, clientului curent i se adauga topicul la caare 
								// s-a abonat in lista de topicuri(subscrbtii)
								void *tmpPtr = realloc(clients[position]->topics,sizeof(clients[position]->topics) + sizeof(struct Topic));
								clients[position]->topics = tmpPtr;
								strcpy(clients[position]->topics[clients[position]->numTopics].topic, req->topic);
								clients[position]->topics[clients[position]->numTopics].SF = req->SF;
								clients[position]->numTopics++;
							} else if (strncmp(req->request, "unsubscribe", 11) == 0 && clients[position]->numTopics > 0) {
								// daca se primeste comanda de unsubscribe, clientului curent i se elimina topicul de la caare 
								// s-a dezabonat din lista de topicuri(subscrbtii)
								int temp;
								for (int j = 0; j < clients[position]->numTopics; j++) {
									if (strcmp(req->topic, clients[position]->topics[j].topic) == 0)
									{
										temp = j;
										break;
									}
								}
								for (int j = temp; j < clients[position]->numTopics-1; j++) {
									clients[position]->topics[j] = clients[position]->topics[j+1];
								}
								clients[position]->numTopics--;
							} else {
								// un nou client incearca sa se conecteze
								checkId = 0;
								for (int j = 0; j < numClients; j++) {
									if (strcmp(clients[j]->ID, req->request) == 0) {
										if(clients[j]->status == 1) {
											// daca clientul inceaca sa se conecteze cu id-ul unui client care este deja
											// conectat si este online, i se respinge conectarea si se afiseaza mesajul urmator
											printf("Client %s already connected.\n", req->request);
											checkId = 1;
											clients[position]->copy = 1;
											clients[position]->status = 0;
											numClients--;
											s = send(clients[position]->soc, "exit", 4, 0);
											DIE(s < 0, "send");
											position--;
											break;
										} else {
											// daca clientul inceaca sa se conecteze cu id-ul unui client care este deja
											// conectat dar care nu este online, serverul va considera ca noul client
											// este de0fapt clientul care se afla deja in baza de date.
											clients[position] = clients[j];
											clients[position]->status = 1;
											for (int j = 0; j < clients[position]->numMessages; j++)
											{
												s = send(clients[position]->soc, &clients[position]->messages[j], sizeof(clients[position]->messages[j]), 0);
												DIE(s < 0, "send");
											}
											clients[position]->numMessages = 0;
											free(clients[position]->messages);
											break;
										}
									}
								}
								if (checkId == 0) {
									// daca clientul s-a conectat cu succes afisez mesajul urmator
									strncpy(clients[position]->ID, req->request, 10);
									printf("New client %s connected from %s:%d.\n",
										clients[position]->ID, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
								}
								
							}
						}
					}
				}
			}
		}
	}
	//eliberez memoria alocata
	for (int j = 0; j < numClients; j++)
	{
		free(clients[j]);
	}
	free(clients);
	
	close(sockTCP);
	close(sockUDP);

	return 0;
}
