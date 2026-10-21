#include "massage_helper.h"
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <error.h>
#include <errno.h>
#define MS_SIZE 255

void* recv_massage(void* arg) {
  int sockD = (intptr_t)arg;
  char *str_data = malloc(sizeof(char) * MS_SIZE);
  int ret = 1;

  for(;;) {
    ret = recv(sockD, str_data, 255,0);
    printf("Message: %s\n", str_data);
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
    fgets(msg, 255, stdin);
    //scanf("%s", msg);
    printf("Massage to send %s\n", msg);

    ret = send(sockD, msg, strlen(msg), 0);
    if(ret <= 0) {
      printf("End\n");
      if(ret < 0) perror("error while trying to recive message");
      break;
    }

  }
  pthread_exit(NULL);
}
