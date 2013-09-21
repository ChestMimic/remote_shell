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

#define BUFFERSIZE 500;
//Main program
int main(int argc, char *argv[]){ //Supposedly accepts command line arguments (from stack overflow)
	struct addrinfo hints, *res;
	struct sockaddr_in sin;
	int sock;
	int bytecount;
	char buffer[256];
	char request[1024];
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
	if(argc == 3){
		strcpy(arg, argv[1]);//grabs whole URL from arguments
		strcpy(argB, argv[1]);
	
		fil = strtok(arg, "/");//fil is now the base domain and dot com/edu/whatever
		path = strtok(NULL, "");
		if(path == NULL){
			path = "";
		}
		printf("%s", fil);
	}
	else if(argc == 4){
		strcpy(arg, argv[2]);//grabs whole URL from arguments
		strcpy(argB, argv[2]);
	
		fil = strtok(arg, "/");//fil is now the base domain and dot com/edu/whatever
		path = strtok(NULL, "");
		if(path == NULL){
			path = "";
		}
		printf("%s", fil);
	}
	else{
		printf("Incorrect input.\nUse ./httpCli (-p) domain port.\n");
		exit(1);
	}
	//printf("%s", argB[strlen(fil)]);
	
	struct timeval start, end;
	double time_in_mill_S = 0;
	double time_in_mill_E = 0;
	if(argc == 3){
		getaddrinfo(fil, argv[2], &hints, &res);
		sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, fil);
		printf("Sending request:\n");
		printf("%s\n", request);
	}
	else if(argc == 4){
		getaddrinfo(fil, argv[3], &hints, &res);
		sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, fil);
		printf("Sending request:\n");
		printf("%s\n", request);
		if((strcmp("-p", argv[2])) == 0){
			gettimeofday(&start, NULL);
			time_in_mill_S = (start.tv_sec) * 1000 + (start.tv_usec) / 1000 ;
		}
	}
	else{
		//incorrect input
		exit(1);
	}	
	
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
	
	int iRes = 1;
	while(iRes > 0){//currently an infinite loop on success?
		if((iRes = recv(sock, buffer, sizeof(buffer) - 1, 0)) == -1){
			printf("Error\n");
		}else{
			//printf("%d\n", iRes);
			buffer[iRes+ 1] = '\0';
			printf("%s", buffer);
			bzero(buffer, 256);
		}
	}
	
	
	if(argc == 4){
		if((strcmp("-p", argv[2])) == 0){
			gettimeofday(&end, NULL);
			time_in_mill_E = (end.tv_sec) * 1000 + (end.tv_usec) / 1000 ;
		}
		
		 printf("%d\n", (time_in_mill_E - time_in_mill_S));
	}
	
	//Finish up
	close(sock);
	freeaddrinfo(res);
	
	return 0;
}
