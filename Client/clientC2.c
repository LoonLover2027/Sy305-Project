#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000        // Port number the server will listen on
#define BUFFER_SIZE 1024    // Size of buffer for incoming messages

int main(void){
 
  char *ip = "10.60.117.170";
  int port = PORT;
 
  int sockfd;
  struct sockaddr_in addr;
  char buffer[1024] = {0};
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  bzero(buffer, 1024);



  while(1)
  {	  
	  printf("Message options: 'DEPLOY', 'EXECUTE', 'STATUS', 'KILL'\n");
    printf(">>");
    if(fgets(buffer, sizeof(buffer),stdin) != NULL){
      buffer[strcspn(buffer, "\n")] = '\0';
      sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&addr, sizeof(addr));
    } else{
      printf("Error sending.");
    }
	  printf("[+]Data sent: %s\n", buffer);
    bzero(buffer, 1024);
	  // addr_size = sizeof(addr);
	  // recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
	  // printf("[+]Data recv: %s\n", buffer);
  }
  return 0;
}