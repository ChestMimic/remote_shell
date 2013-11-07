#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <sys/socket.h>
int WorkThread( void * ); // Prototype

#define MAXBUF		1024
#define TRUE 1

unsigned int CreateAThread( void *, int *); // Prototype
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
	listener = argv[1];//grab port number
	
	//memset(&hints, 0, sizeof hints);
	
	/*---Initialize address/port structure---*/
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(9876);//user assigned port number
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
	//int size = recv(fdConn, buffer, MAXBUF, 0);
	//send(fdConn, buffer, recv(fdConn, buffer, MAXBUF, 0), 0);
	int size=recv(fdConn, buffer, MAXBUF, 0);
	printf("%d\n", size);
	printf("%s\n",buffer);
	close(fdConn);
	

}

// End of WorkThread


