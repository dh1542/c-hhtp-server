#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/**
 * @brief Pass an address as parameter to get the ip address of it
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: <port>\n");
        return 1;
    }


    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *p;
    char ip[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    int s = getaddrinfo(argv[1], NULL, &hints, &result);

    if(s != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 2;
    }

    printf("IP addresses for %s:\n\n", argv[1]);

    for(p = result; p != NULL; p = p -> ai_next){
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;


        //ipv4
        if(p -> ai_family == AF_INET){
            ipv4 = (struct sockaddr_in *)p -> ai_addr;
            addr = &(ipv4 -> sin_addr);
            ipver = "IPv4";
        }

        inet_ntop(p -> ai_family, addr, ip, sizeof ip);
        printf("  %s: %s\n", ipver, ip);


    }

    freeaddrinfo(result);
    





    
    return 0;
}