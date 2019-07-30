/** @file problem3.c 
 *  @brief Problem Statement 3 Ping a server. Use sudo <command> <hostname> <times>
 *
 *  @author Ashutosh
 */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h> 

/** @brief Function to get the IP address from the domain name
 *
 * @param host_addr The domain name.
 * @return a char* to the ip address.
 */
char *domain_name_server_lookup(char *host_addr) 
{ 
    printf("Resolving DNS..\n"); 
    struct hostent *host_entity; 
    char *ip=(char*)malloc(NI_MAXHOST*sizeof(char)); 
    int i; 
  
    if ((host_entity = gethostbyname(host_addr)) == NULL) 
    { 
        // No ip found for hostname 
        return NULL; 
    } 
      
    strcpy(ip, inet_ntoa(*(struct in_addr *) 
                          host_entity->h_addr)); 
  
    return ip; 
} 

/** @brief Problem Statement 3 entrypoint.
 *
 *  @param argc Count of the arguments
 *  @param argv Array of parameters
 */
int main(int argc, char *argv[]) {

    int count = 1; 
    char *ip_address; 
  
    if (getuid() != 0)
    {
        fprintf(stderr, "%s: root privelidges needed\n", *(argv + 0));
        exit(EXIT_FAILURE);
    }
 
    if(argc < 2) 
    { 
        printf("\nIncorrect Format %s <address>\n", argv[0]); 
        return 0; 
    } 

    if (argc == 3)
    {
        if(atoi(argv[2]) != 0)
            count = atoi(argv[2]);
    }
  
    ip_address = domain_name_server_lookup(argv[1]); 

    if(ip_address==NULL) 
    { 
        printf("\nCould not resolve hostname!\n"); 
        return 0; 
    } 

    printf("\nPING '%s' IP: %s\n", argv[1], ip_address); 
    
    // Creating Socket
    int s = socket(PF_INET, SOCK_RAW, 1);

    if(s <= 0)
    {
        perror("Socket Error");
        exit(0);
    }

    // Create the ICMP Struct Header
    typedef struct {
        uint8_t type;
        uint8_t code;
        uint16_t chksum;
        uint32_t data;
    } icmp_hdr;

    icmp_hdr pckt;

    // Set the appropriate values to our struct, which is our ICMP header
    pckt.type = 8;          // The echo request is 8
    pckt.code = 0;          // No need
    pckt.chksum = 0xfff7;   // Fixed checksum since the data is not changing
    pckt.data = 0;          // We don't send anything.

    // Creating a IP Header from a struct that exists in another library

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = inet_addr(ip_address);

    // Send our PING
    while(count > 0) 
    {
        count--;
        int actionSendResult = sendto(s, &pckt, sizeof(pckt),
                                      0, (struct sockaddr*)&addr, sizeof(addr));

        if(actionSendResult < 0)
        {
            perror("Ping Error");
            exit(0);
        }

        // Prepare all the necessary variable to handle the response
        unsigned int resAddressSize;
        unsigned char res[30] = "";
        struct sockaddr resAddress;

        // Read the response from the remote host
        int response = recvfrom(s, res, sizeof(res), 0, &resAddress,
                                 &resAddressSize);

        if( response > 0)
        {
            printf("Received %d bytes from %s : %s\n", response, ip_address, argv[1]);
        }
        else
        {
            perror("Response Error!!!!");
            exit(0);
        }
    }
    return 0;
}