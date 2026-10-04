#include "massage_helper.h"
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void end_com(int clientSocket) {
  send(clientSocket, ENDOFCOM, strlen(ENDOFCOM), 0);
}

void* recv_massage(void* arg) {
  int sockD = (int)arg;
  char strData[255];
  char* end = ":q";
  for(;;) {
    recv(sockD, strData, sizeof(strData),0);

    printf("Message: %s\n", strData);
    if(!strncmp(strData, ENDOFCOM, strlen(ENDOFCOM))) {
      break;
    }
  }
  pthread_exit(NULL);
}

void* send_massage(void* arg) {
  int sockD = (int)arg;
  char* msg = malloc(sizeof(char) * 255);
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
    send(sockD, msg, sizeof(msg), 0);
  }
  pthread_exit(NULL);
}
