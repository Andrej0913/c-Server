#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "massage_helper.h"

#define PORT 8080


int main(int argc, char const* argv[]) {
  // SOCK_STREAM -> TCP
  // local socked
  //int sockD = socket(AF_INET, SOCK_STREAM, 0);
  // net socked
  int sockD = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );

  struct sockaddr_in servAddr;

  servAddr.sin_family = AF_INET; // IPv4
  servAddr.sin_port = htons(9001); // use some unused port number
  servAddr.sin_addr.s_addr = INADDR_ANY;
  //servAddr.sin_addr.s_addr = inet_addr("x.x.x.x");

  printf("Use Port %d\n", servAddr.sin_addr.s_addr);

  int connectStatus
    = connect(sockD, (struct sockaddr*)&servAddr,
              sizeof(servAddr));
  printf("main SockD: %i\n", sockD);
  pthread_t thread_1;
  pthread_t thread_2;

  if (connectStatus == -1) {
    printf("Error...\n");
  }else{
    pthread_create(&thread_1, NULL, send_massage, (void*)sockD);
    pthread_create(&thread_2, NULL, recv_massage, (void*)sockD);
    /*
    char strData[255];
    char* end = ":q";
    for(;;) {
      recv(sockD, strData, sizeof(strData),0);

      printf("Message: %s\n", strData);
      if(!strncmp(strData, end, strlen(end))) {
        break;
      }
    }
    */

  }
  pthread_join(thread_1,NULL);
  return 0;
}
