/* Author: Mark Fitzgibbon
*/


#include <stdio.h>
#include <stdlib.h>
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

#define MAXBUF		1024
//Main program
int main(int argc, char *argv[]){ //Supposedly accepts command line arguments (from stack overflow)
	struct addrinfo hints, *res;
	struct sockaddr_in sin;
	int sock;
	int bytecount;
	char buffer[MAXBUF];
	char request[MAXBUF];
	char arg[MAXBUF], argB[MAXBUF];
	char *fil;
	
	memset(&hints, 0, sizeof hints);//ensure struct is empty
	hints.ai_family = AF_UNSPEC; //Either IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; //TCP stream sockets
	hints.ai_flags = AI_PASSIVE; //fill in IP for me
	
	
	//split address into host and file
	int spot;
	char* path;
	
	
	if ( argc < 4 ) {
        printf( "The program expects 4 arguments\n" );
        printf( "Browser <URL || IP address> <port number> <command>\n" );
        exit(0);
    }
	else{
		strcpy(arg, argv[1]);//grabs whole URL from arguments
		strcpy(argB, argv[1]);
	
		fil = strtok(arg, "/");//fil is now the base domain and dot com/edu/whatever
		path = argv[3];
		printf("%s", fil);
	
	
	
	}	
	struct timeval start, end;
	double time_in_mill_S = 0;
	double time_in_mill_E = 0;

	getaddrinfo(fil, argv[2], &hints, &res);
	

	
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if(sock == -1){
		printf("Socket went bad.\n");
		exit(1);//kill program
	}
	
	if(connect(sock, res->ai_addr, res->ai_addrlen) == -1){
		printf("Connect to socket failed. Quitting.\n");
		exit(1);//something went wrong. Quit
	}
	printf("Connected!\n");
	/*
	if(	(send(sock, name, strlen(name), 0)) < 0){
		printf("Error in send\n");
		exit(1);
	}*/
	
	if(	(send(sock, "hello", strlen("hello"), 0)) < 0){
		printf("Error in send\n");
		exit(1);
	}
	
	
	//Finish up
	close(sock);
	freeaddrinfo(res);
	
	return 0;
}
