# Protocoale de comunicatii
# Laborator 7 - TCP
# Echo Server
# Makefile

CFLAGS = -Wall -g

# Portul pe care asculta serverul
PORT = 

# Adresa IP a serverului
IP_SERVER = 

all: server subscriber 

# Compileaza server.c
server: server.c -lm

# Compileaza client.c
subscriber: subscriber.c

.PHONY: clean run_server run_subscriber

# Ruleaza serverul
run_server:
	./server ${IP_SERVER} ${PORT}

# Ruleaza clientul 	
run_subscriber:
	./subscriber ${IP_SERVER} ${PORT}

clean:
	rm -f server subscriber
