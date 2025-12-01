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
#include <sys/types.h>
#include <sys/wait.h> /// wait function
#include <time.h> // for time, records seconds since 1970


//// Pre-Compile Area /////
#include "helloworld.h" //// this includes the binary array and its length/ essentiall just a C file
//// uses cli command to make the binary file into 

time_t seconds; /// Time
time_t timeTwo = 0;
double TimeDif = 0; /// stores the difference in time

/// signal Handler Decleration
void heartbeat(int sig, siginfo_t *info, void *uc){ /// signal number recevied (looking for SIGUSR1), pointer to structure of signal, pointer to user context structure
	if(SIGUSR1 == sig){ ///user defined signal
		printf("baBump...");

		seconds = timeTwo; //// becomes old time

		timeTwo = time(NULL); //// gets current time
		
		TimeDif = timeTwo - seconds; //gets time difference
	}
}
void execute(void);
void deploy(void);
int main(void){
	 /// Declare time
	 seconds = time(NULL); // gets time since Jan 1 1970
	 printf("Time Since: %ld ", seconds);


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


	///// Signal Creation/////
	struct sigaction HB = {0}; /// create sigaction struct
	HB.sa_sigaction = &heartbeat; /// address of sig handler function, how to handle sig recevied function
	HB.sa_flags = SA_SIGINFO;  /// tells OS to use three arguement like sig handler function, fill the siginfo_t struct
	if(sigaction(SIGUSR1,&HB, NULL)== -1){ /// links sig number to signal handler function so when received do this
		perror("Sigaction: ");
		exit(1);
	}


	//////////////// Payload file processing ////////////////////////////////////////
	
		while(1) /// server loop always runs 
		{ /// recvfrom is the UDP protocol listening 
			bzero(buffer, 1024);
			recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size); //// waits for information
			printf("[+]Data recv: %s\n", buffer); /// stores the clients IP // sockect file descrip- pointer to buffer, max size of buffer, control flags
            

			//// recvfrom receives the buffer as a bytes
			
			buffer[strcspn(buffer, "\n")] = '\0'; /// searches for newline character and replaces with terminator 

            if(strcmp(buffer,"DEPLOY") == 0){ //// compares ASC11 values of buffer to a string, if 0 its equal
                printf("Loading\n"); /// Sender uses fgets()
				deploy();
				
            }

			if(strcmp(buffer,"EXECUTE") == 0){ //// compares ASC11 values of buffer to a string, if 0 its equal
               execute();
            }

			

			
		}

		
		
return 0;
}

void deploy(void){

		int fd = open("payload", O_WRONLY | O_CREAT, 0700);
		if(write(fd, helloworld, helloworld_len) == -1){//// helloworld binary 
			printf("Payload failed"); //// above writes the helloworld content to the file fd
		}
		close(fd);

	}

void execute(void){
	printf("Executing...\n"); /// Sender uses fgets()
	char *args[] = {"./payload", NULL}; /// makes const 
	int result = execv(args[0], args); /// call a fork here check if child call exec in child
    

	//// this will check if execution is alive ///
	while(1){
	if(TimeDif >= 5){ /// if time since heartbeat reaches more than five seconds redeploy and execute
				deploy();
				execute();

			}		
		}
			//// save PID once executed and saved to a table for user to view //////
}
