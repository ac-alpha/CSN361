/** @file problem1_server.c
 *  @brief Problem Statement 1 : Program in C to connect two nodes on a network to communicate with each other, where one socket listens on a particular port at an IP, while other socket reaches out to the other to form a connection
 *  @author Ashutosh Chaubey
 */
#include <unistd.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

#define PORT 8080 
/** @brief Problem Statement 1 entrypoint.
 */
int main(int argc, char const *argv[]) {
	
	int sockfd, new_socket, val_read;
	struct sockaddr_in address;
	int opt = 1;
	int len_addr = sizeof(address);
	char buffer[1024] = {0};
	char *response = "Response from the server!";	// Response message from server

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// File descripter for socket with IPv4 and TCP.

	if(sockfd == 0) {
		perror("socket failed!");
		exit(EXIT_FAILURE);
	}

	// Attach the socket to port 8080 forcefully
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; 	// For localhost
    address.sin_port = htons(PORT);

    // Bind the socket to port 8080 of local machine
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address))<0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

    printf("Server listening...\n");

    if (listen(sockfd, 3) < 0) {
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }

    // Extract the first connection from pending queue and establish connection b/w client and server by creating a new socket.
    if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&len_addr))<0) {
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }

    val_read = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , response , strlen(response) , 0 ); 
    printf("Response message sent\n"); 
    return 0;
}