/** @file problem1_client.c
 *  @brief Problem Statement 1 : Program in C to connect two nodes on a network to communicate with each other, where one socket listens on a particular port at an IP, while other socket reaches out to the other to form a connection
 *  @author Ashutosh Chaubey
 */
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#define PORT 8080

/** @brief Problem Statement 1 entrypoint.
 */
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, val_read; 
    struct sockaddr_in serv_addr; 
    char *request = "Client requesting..."; 
    char buffer[1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed !!!!\n"); 
        return -1; 
    } 
    
    send(sock , request , strlen(request) , 0 ); 
    printf("Request message sent\n"); 
    val_read = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 