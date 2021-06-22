#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
  msg r;
  init(HOST,PORT);
  int i = 0;
  int fd = open("fis_primit", O_WRONLY|O_CREAT,0644);
  while(1) {
    if (recv_message(&r)<0){
      perror("Receive message");
      return -1;
    }
    if(!strcmp(r.payload, "ENDOFLE")) {
      break;
    }
    printf("[recv] Got msg with payload: <%s>, sending ACK %d...\n", r.payload, i);
    write(fd, r.payload, 7);
    sprintf(r.payload,"%s %d", "ACK", i++);
    r.len = strlen(r.payload) + 1;
    send_message(&r);
    printf("[recv] ACK sent\n");
  }
  close(fd);
  return 0;
}
