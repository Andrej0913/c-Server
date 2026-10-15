#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdint.h>
#include "massage_helper.h"
#include "socket_helper.h"

#define PORT 9001


int main(int argc, char const* argv[]) {
  // SOCK_STREAM -> TCP
  // local socked
  //int sockD = socket(AF_INET, SOCK_STREAM, 0);
  // net socked
  //int sockD = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
  int sockD = cr_client_socket();
  /*
  struct sockaddr_in servAddr;

  servAddr.sin_family = AF_INET; // IPv4
  servAddr.sin_port = htons(PORT); // use some unused port number
  servAddr.sin_addr.s_addr = INADDR_ANY;
  //servAddr.sin_addr.s_addr = inet_addr("x.x.x.x");

  printf("Use Port %d\n", servAddr.sin_addr.s_addr);

  int connectStatus
    = connect(sockD, (struct sockaddr*)&servAddr,
              sizeof(servAddr));

  */
  int connect_status = connect_to_server(sockD,PORT,NULL);
  printf("main SockD: %i\n", sockD);
  pthread_t thread_1;
  pthread_t thread_2;
  if (connect_status <= -1) {
    printf("Error...\n");
    printf("connectin status: %i\n", connect_status);
  }else{
    pthread_create(&thread_1, NULL, send_massage, (void*)(intptr_t)sockD);
    pthread_create(&thread_2, NULL, recv_massage, (void*)(intptr_t)sockD);

  }
  pthread_join(thread_1,NULL);
  pthread_join(thread_2,NULL);
  return 0;
}
