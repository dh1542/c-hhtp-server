#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT "3490"

void handle_error(char *message[]){
    perror("%s\n", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints;
    struct addrinfo *servinfo, *rp;
    int s, socket_file_descriptor;
    int optval = 1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // IPv6 or IPv4 
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;    

    s = getaddrinfo(NULL, PORT, &hints, &servinfo);

    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for(rp = servinfo; rp != NULL; rp = rp -> ai_next){
        socket_file_descriptor = socket(rp -> ai_family, rp -> ai_socktype, rp -> ai_protocol);
        if(socket_file_descriptor == -1){
            perror("server: socket");
            continue;
        } 


        // to fix address already in use erro
        if(setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) != 0){
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }


        if(bind(socket_file_descriptor, rp -> ai_addr, rp -> ai_addrlen) == -1){
            close(socket_file_descriptor);
            perror("bind");
            exit(EXIT_FAILURE);
        }

        break;


    }


    freeaddrinfo(servinfo);
    
    if(rp == NULL){
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }


    printf("Correctly set up bind and socket\n");

    if(close(socket_file_descriptor) == -1){
        perror("close");
        exit(EXIT_FAILURE);
    }
    
    
    return 0;
}