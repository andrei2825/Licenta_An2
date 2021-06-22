CC=gcc
CFLAGS=-I.

client: client.c helpers.c requests.c buffer.c
	$(CC) -o client client.c helpers.c requests.c parson.c buffer.c -Wall 

run: client
	./client

clean:
	rm -f *.o client
