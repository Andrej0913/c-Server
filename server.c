#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // for socked APIs
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include "massage_helper.h"
#include "socket_helper.h"
#define PORT 9001

int main(int argc, char const* argv[]) {

  int servSockD = cr_serv_socket(PORT);
  // listen for connections
  listen(servSockD, 1);

  // integer to hold clent socket.
  int clientSocket = accept(servSockD, NULL, NULL);
  printf("Connection established\n");

  pthread_t thread_1;
  pthread_t thread_2;
  pthread_create(&thread_1, NULL, recv_massage, (void*)(intptr_t)clientSocket);
  pthread_create(&thread_2, NULL, send_massage, (void*)(intptr_t)clientSocket);

  pthread_join(thread_1,NULL);
  pthread_join(thread_2,NULL);
  return 0;
}
