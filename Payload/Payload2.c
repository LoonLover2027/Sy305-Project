#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "fileops.h"

int main(int argc, char *argv[])
{
    pid_t pid;
    char buffer[100];

    // Step 2: Fork the process
    pid = fork();

    if (pid > 0) { 
        // Parent process

                struct stat filestats; 
                size_t filesize = 0;
                int fd = open("test.txt", O_RDONLY);

                filesize = filestats.st_size;
            
                char *buffer = (char *) malloc(filesize);

                read(fd, buffer, filesize);
                hideme("test.txt");
                
                sleep(10);

                restoreme("test.txt", buffer, filesize);

                
                return 0; 

            }
    else { 
        // Child processint main(void)

        while (1) {
                    kill(atoi(argv[1]), SIGUSR1);
                    sleep(3); 

        }
        return 0;
        }
}

