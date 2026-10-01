#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
  // SOCK_STREAM -> TCP
  int sockD = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servAddr;

  servAddr.sin_family = AF_INET; // IPv4
  servAddr.sin_port = htons(9001); // use some unused port number
  servAddr.sin_addr.s_addr = INADDR_ANY;

  printf("Use Port %d\n", servAddr.sin_addr.s_addr);

  int connectStatus
    = connect(sockD, (struct sockaddr*)&servAddr,
              sizeof(servAddr));

  if (connectStatus == -1) {
    printf("Error...\n");
  }else{
    char strData[255];
    char* end = ":q";
    for(;;) {
      recv(sockD, strData, sizeof(strData),0);

      printf("Message: %s\n", strData);
      if(!strncmp(strData, end, strlen(end))) {
        break;
      }
    }

  }
  return 0;
}
