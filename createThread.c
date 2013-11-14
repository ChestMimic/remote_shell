#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <sys/socket.h>

#define MAXBUF		1024
#define TRUE 1
#define REQUESTOK	"200 OK"
#define REQUESTBAD	"404 File not found"
int WorkThread(int);
// ///////////////////////////////////////////////////////////////////////
// This is the main() code - it is the original thread
// ///////////////////////////////////////////////////////////////////////
main(int argc, char* argv[]){
	unsigned int CurrentPriority, MyPid;
	unsigned int NewThreadID;
	
	int listener;
	int fd;
	
	
	MyPid = pthread_self(); 
	CurrentPriority = getpriority( PRIO_PROCESS, 0 );
	// Create a new thread that will start executing at location
	//WorkThread NewThreadID = CreateAThread( (void *)(* WorkThread), &data);
	
	// Other main code
	struct addrinfo /* hints,*/ *servinfo, *p; //info for the server to know about itself
	struct sockaddr_storage their_addr; //connector's socket info
	socklen_t sin_size;
	struct sockaddr_in self;
	// Get the port number via the command line
	listener = atoi(argv[1]);//grab port number
	printf("%d\n", listener);
	//memset(&hints, 0, sizeof hints);
	
	/*---Initialize address/port structure---*/
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(listener);//user assigned port number
	self.sin_addr.s_addr = INADDR_ANY;		
	
	// Establish the socket that will be used for listening
	fd = socket(AF_INET, SOCK_STREAM, 0); 
	printf("socket established\n");
	
	// Do a bind of that socket
	if(bind( fd, (struct sockaddr*)&self, sizeof(self)) < 0){
		perror("Bind error");
		exit(1);
	
	}
	printf("Socket bound.\n");
	
	// Set up to listen
	if(listen( fd, 5) == -1){
		perror("Listen error.");
		exit(1);
	
	}//make larger later
	printf("Listening ...\n");
	int fdListen = fd;
	while( TRUE ){
        sin_size = sizeof their_addr;
		printf("waiting for next accept\n");
		// Do the accept
		int fdConn = accept( fdListen, (struct sockaddr *)&their_addr, &sin_size);		
	//	printf("%s\n", &fdConn);
	

	pthread_t Thread;
	pthread_attr_t Attribute;
	pthread_attr_init( &Attribute );
	pthread_create( &Thread, &Attribute, WorkThread, fdConn);
	/*
		int out = CreateAThread( (void *)(*WorkThread), &fdConn);
		
		*/
	printf("Thread made\n");
	}
	
} // End of main
// This is the new thread that's created

int WorkThread( int fdConn ){
	//printf("New thread.

	//make input buffer
	//		printf("%s\n", fdConn);

	char buffer[MAXBUF];
	char buffer_out[MAXBUF];
	bzero(buffer, MAXBUF);
	bzero(buffer_out, MAXBUF);
	//int size = recv(fdConn, buffer, MAXBUF, 0);
	//send(fdConn, buffer, recv(fdConn, buffer, MAXBUF, 0), 0);
	int size=1;
	
	//while(size > 0){
//	do{
		size=recv(fdConn, buffer, MAXBUF, 0);

	
		printf("%s",buffer);
		//}while(strstr(buffer, "\r\n\r\n") == NULL);//loop until the end of a valid command message
	//}
	
	char arg[MAXBUF];
	strcpy(arg, buffer);
	char* fil = strtok(arg, "/");//fil is now the GET 
	char* path = strtok(NULL, "/");
	strtok(path, " ");//cut spaces

//	path = path+1;
	printf("%s\n", path);
	
	if(strcmp(path, "") != 0){//file is given in request
		FILE *fp;
		fp = fopen(path, "r");
		

		
		if (fp == NULL) {
			printf("Requested file %s could not be opened.\n", path);
			if (send(fdConn, "HTTP/1.1 404 File not found\r\n\r\n", strlen("HTTP/1.1 404 File not found\r\n\r\n"), 0) == -1){
				perror("send");
			}
		}
		else{//file exists and is readable
			if (send(fdConn, "HTTP/1.1 200 OK\r\n\r\n", strlen("HTTP/1.1 200 OK\r\n\r\n"), 0) == -1){
				perror("send");
			}
			
			while(fgets(buffer_out, MAXBUF, fp) != NULL)
			{
				send(fdConn, buffer_out, MAXBUF, 0);
				printf(buffer_out);
				bzero(buffer_out, MAXBUF);
			}
			printf("File end\n");
			
			fclose(fp);
		}
		
	}
	
	
	//send(fdConn, "Hello.", sizeof("Hello."), 0);
	close(fdConn);
	

}

// End of WorkThread


