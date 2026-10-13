#include "massage_helper.h"
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <error.h>

void end_com(int clientSocket) {
  send(clientSocket, ENDOFCOM, strlen(ENDOFCOM), 0);
}

void* recv_massage(void* arg) {
  int sockD = (intptr_t)arg;
  char strData[255];
  char* end = ":q";
  int ret;
  for(;;) {
    ret = recv(sockD, strData, sizeof(strData),0);
    if(ret < 0) perror("error while trying to recieve message");
    printf("Message: %s\n", strData);
    if(!strncmp(strData, ENDOFCOM, strlen(ENDOFCOM))) {
      break;
    }
  }
  pthread_exit(NULL);
}

void* send_massage(void* arg) {
  int sockD = (intptr_t)arg;
  char* msg = malloc(sizeof(char) * 255);
  int ret;
  for(;;) {
    printf("Type a message\n");
    msg[0] = '\0';
    scanf("%s", msg);

    if(!strncmp(msg, ENDOFCOM, strlen(ENDOFCOM))) {
      printf("End\n");
      end_com(sockD);
      break;
    }

    // send's messages to client client socket
    ret = send(sockD, msg, sizeof(msg), 0);
    if(ret < 0) perror("error while trying to recive message");
  }
  pthread_exit(NULL);
}
