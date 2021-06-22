#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;
  int fd = open("test", O_RDONLY);
  int reader;
  char buff[8];
  int i = 0;
  while(1) {
    reader = read(fd, buff, 7);
    if(reader == 0) {
      break;
    }
    printf("[send] Sending message %d...\n", i++);
    sprintf(t.payload,"%s", buff);
    t.len = 8;
    send_message(&t);
    if (recv_message(&t)<0){
      perror("Receive error ...");
      return -1;
    }
    else {
      printf("[send] Got reply with payload: %s\n", t.payload);
    }
  }
  sprintf(t.payload,"%s", "ENDOFLE");
  send_message(&t);
  close(fd);
  return 0;
}
