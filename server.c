#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> // for socked APIs
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include "massage_helper.h"
#define PORT 9001

int main(int argc, char const* argv[]) {

  // create server socket similar to what was doen in
  // client program
  // local socked
  //int servSockD = socket(AF_INET, SOCK_STREAM, 0);
  // net socked
  int servSockD = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );

  // string store data to send to client
  char serMsg[255] = "Message from the server to the "
                     "client \'Hello Client\'";

  //defien server address
  struct sockaddr_in servAddr;

  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(PORT);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  printf("Use Port %d\n", servAddr.sin_addr.s_addr);

  //bind socket to the specified IP and port
  bind(servSockD, (struct sockaddr*)&servAddr,
       sizeof(servAddr));

  // listen for connections
  listen(servSockD, 1);

  // integer to hold clent socket.
  int clientSocket = accept(servSockD, NULL, NULL);
  printf("Connection established\n");

  char* msg = malloc(sizeof(char) * 10);
  char* end = ":q";

  pthread_t thread_1;
  pthread_t thread_2;
  pthread_create(&thread_1, NULL, recv_massage, (void*)(intptr_t)clientSocket);
  pthread_create(&thread_2, NULL, send_massage, (void*)(intptr_t)clientSocket);

  pthread_join(thread_1,NULL);
  pthread_join(thread_2,NULL);
  return 0;
}
