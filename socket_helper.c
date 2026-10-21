#include "socket_helper.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <stdio.h>

int cr_serv_socket(int port) {
  int servSockD = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
  struct sockaddr_in servAddr;

  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(port);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  bind(servSockD, (struct sockaddr*)&servAddr,
        sizeof(servAddr));

  return servSockD;
}

int cr_client_socket() {
  int sockD = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );

  return sockD;
}

int connect_to_server(int sockD, int port, char *addr) {
  struct sockaddr_in servAddr;

  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(port);
  if(addr == NULL) {
    servAddr.sin_addr.s_addr = INADDR_ANY;
  }else{
    in_addr_t in_addr = inet_addr(addr);

    if(in_addr == 0) {
      perror("Invalid targer address\n");
      return -2;
    }
    servAddr.sin_addr.s_addr = in_addr;
  }

  int connect_status
    = connect(sockD, (struct sockaddr*)&servAddr,
              sizeof(servAddr));

  return connect_status;
}
