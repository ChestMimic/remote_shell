/* Author: Mark Fitzgibbon
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
//I haven't used C or C++ in a while, so code may be sloppy
/*
	NOTE TO SELF:
	& is the ADDRESS OPERATOR, and means that when attached to a variable, it returns the ADDRESS IN MEMORY OF SAID VARIABLE
	* is the DEREFERENCING OPERATOR, and when given to a variable, it returns the VALUE STORED AT THE ADDRESS LISTED IN THE VARIABLE
*/

//code is partially based on tutorial found at http://www.beej.us

#define         BUFFER_SIZE     2000
//Main program
int main(int argc, char *argv[]){ //Supposedly accepts command line arguments (from stack overflow)
	struct addrinfo hints, *res;
	struct sockaddr_in sin;
	int sock;
	int bytecount;
	char buffer[BUFFER_SIZE];
	char request[BUFFER_SIZE];
	char arg[500], argB[500];
	char *fil;
	
	memset(&hints, 0, sizeof hints);//ensure struct is empty
	hints.ai_family = AF_UNSPEC; //Either IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; //TCP stream sockets
	hints.ai_flags = AI_PASSIVE; //fill in IP for me
	//printf(argv[1]);
	//make sure proper number of arguments
	
	//split address into host and file
	int spot;
	char* path;
	
	
	if ( argc < 4 ) {
        printf( "The program expects two arguments\n" );
        printf( "Browser <URL || IP address> <port number> <target file>\n" );
        exit(0);
    }
	else{
		strcpy(arg, argv[1]);//grabs whole URL from arguments
		strcpy(argB, argv[1]);
	
		fil = strtok(arg, "/");//fil is now the base domain and dot com/edu/whatever
		path = argv[3];
		printf("%s", fil);
	
	
	
	}
	
	
	
	//printf("%s", argB[strlen(fil)]);
	
	struct timeval start, end;
	double time_in_mill_S = 0;
	double time_in_mill_E = 0;

	getaddrinfo(fil, argv[2], &hints, &res);
	sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s:%s\r\n\r\n", path, fil, argv[2]);
	printf("Sending request:\n");
	printf("%s\n", request);

	
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("Socket");
	if(sock == -1){
		//fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		printf("Socket went bad.\n");
		exit(1);//kill program
	}
	
	if(connect(sock, res->ai_addr, res->ai_addrlen) == -1){
	
		exit(1);//something went wrong. Quit
	}
	printf("Connected!\n");
	
	int iSend;
	//send GET http://www.w3.org/pub/WWW/TheProject.html HTTP/1.1
	if(	(iSend =  send(sock, request, strlen(request), 0)) < 0){
		printf("Error in send\n");
		exit(1);
	}
	else{
		printf("Sent %d of %d\n",iSend, strlen(request));
	}
	

	
	int flag = 0;
	while(1)
   {
        if ( recv( sock, buffer, BUFFER_SIZE, 0 ) < 0 ){
	    // Good programming practice will have you generate an error message 
	    // here if the recv()  call fails.
			perror("Client: recieve");
			break;
        }
		
        printf( "%s", buffer );
		bzero(buffer, BUFFER_SIZE);
   }
	
	

	
	//Finish up
	close(sock);
	freeaddrinfo(res);
	
	return 0;
}
