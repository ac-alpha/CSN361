/** @file problem4.c
 *  @brief Problem Statement 4 get the host name and the IP address of your computer.
 *         <command> <devicename>
 *  @author Ashutosh
 */

#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


/** @brief Prolem Statement 4 entrypoint.
 *  
 *  @param argc Count of the arguments
 *  @param argv Array of parameters
 */  
int main(int argc, char *argv[]) {

   if(argc < 2) 
   { 
      fprintf(stderr,"usage: <command> <devicename>\n");
      return 0; 
   } 
   int n;
   struct ifreq ifr;
   char* array = argv[1];
   char host[256];
   struct hostent *host_entry;
   int host_name;

   // Get the host name
   host_name = gethostname(host, sizeof(host));
   if (host_name == -1) {
      perror("gethost_name");
      exit(1);
   }

   n = socket(AF_INET, SOCK_DGRAM, 0);

   //Type of address to retrieve - IPv4 IP address
   ifr.ifr_addr.sa_family = AF_INET;

   //Copy the interface name in the ifreq structure
   strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);

   ioctl(n, SIOCGIFADDR, &ifr);
   close(n);

   //display result
   printf("Host Name: %s\n", host);
   printf("IP Address is = %s\n" , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
   return 0;
}