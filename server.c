#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char* argv[]){
	int sockfd, new_fd;//sockfd listens, new_fd is new connection
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; //connector's socket info
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1; //What the hell, Past Ibbolia?
	char s[INET6_ADDRSTRLEN];
	char buffer[256];
	int rv;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	if((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	
	p = servinfo;
	while(p != NULL){
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }
	
		p=p->ai_next;
		break;
	}
	
	if (p == NULL)  {//couldn't find useful socket
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }
	
	freeaddrinfo(servinfo); //done with this
	
	if(listen(sockfd, 5) == -1){
		perror("listen");
		exit(1);
	}
	
	printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

		/*
        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            if (send(new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
		*/
		if (send(new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
        
		int iRes;
		//printf("Recieving\n");
		
		if((iRes = recv(new_fd, buffer, sizeof(buffer) - 1, 0)) == -1){
			printf("Error\n");
		}
		
		else{
			//printf("%d\n", iRes);
			//buffer[iRes+ 1] = '\0';
			printf("%s", buffer);
			if(strstr("GET", buffer)){
				if (send(new_fd, "GETs only", 10, 0) == -1)
                perror("send");
			}
			else{
				char arg[256];
				strcpy(arg, buffer);
				char* fil = strtok(arg, "/");//fil is now the GET 
				char* path = strtok(NULL, "/");
				path = path+1;
				if(path == NULL){
					path = "";
				}
				else{
					FILE *fp;
					fp = fopen(path, "r");
					if(fp == NULL){
						if (send(new_fd, "HTTP/1.1 404 File not found\r\n\r\n", strlen("HTTP/1.1 404 File not found\r\n\r\n"), 0) == -1){
							perror("send");
						}
					}
					else{
						if (send(new_fd, "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n", strlen("HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n"), 0) == -1){
							perror("send");
						}
						
						//Send file contents here.
					}
				}
				
				//printf("%s", fil);
			
			
			}
			
			bzero(buffer, 256);
		}
		close(new_fd);
        //close(new_fd);  // parent doesn't need this
    }
	
	return 0;
	
}

