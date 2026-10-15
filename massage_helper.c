#include "massage_helper.h"
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <error.h>

void* recv_massage(void* arg) {
  int sockD = (intptr_t)arg;
  char strData[255];
  char* end = ":q";
  int ret = 1;
  for(;;) {
    ret = recv(sockD, strData, sizeof(strData),0);
    printf("Message: %s\n", strData);
    if(ret <= 0) {
      if(ret < 0) perror("error while trying to recieve message");
      break;
    }
  }
  pthread_exit(NULL);
}

void* send_massage(void* arg) {
  int sockD = (intptr_t)arg;
  char* msg = malloc(sizeof(char) * 255);
  int ret = 1;
  for(;;) {
    printf("Type a message\n");
    msg[0] = '\0';
    scanf("%s", msg);

    ret = send(sockD, msg, sizeof(msg), 0);
    if(ret <= 0) {
      printf("End\n");
      if(ret < 0) perror("error while trying to recive message");
      break;
    }

  }
  pthread_exit(NULL);
}
