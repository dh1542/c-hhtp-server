#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    
    printf("Starting server\n");



    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0,  sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int socket = getaddrinfo(NULL, argv[0], &hints, &result);
    

    if (socket != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(socket));
        exit(EXIT_FAILURE);
    }

    for(rp = result; rp != NULL; rp = rp->ai_next){
        printf("domain %i", rp->ai_family);
    }






    


    
    
    return 0;
}