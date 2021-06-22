#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdio.h>
#include <stdlib.h>

/*
* Macro de verificare a erorilo
* Exemplu: 
* 		int fd = open (file_name , O_RDONLY);	
* 		DIE( fd == -1, "open failed");
*/

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while(0)
	
/* Dimensiunea maxima a calupului de date */
#define BUFLEN 1600
#define MAX_CLIENTS 5
struct UDP_message
{
	char topic[51];
	char ip[17];
	char port[10];
	char type[20];
	unsigned int data_type; 
	int integer;
	float short_int;
	float fl;
	char msg[1501];
};

struct ClientRequest {
	char request[13];
	char topic[51];
	int SF;
};

struct Topic{
	int SF;
	char topic[51];
};

struct Client{
	//1 connected / 0 disconnected
	int status;
	char ID[11];
	int soc;
	int numTopics;
	struct Topic* topics;
	int numMessages;
	struct UDP_message* messages;
	int copy;
};

struct DB{
	int soc;
	char ID[11];
};

#endif
