#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <sys/socket.h>
int WorkThread( void * ); // Prototype

#define MAXBUF		1024

unsigned int CreateAThread( void *, int *); // Prototype
// ///////////////////////////////////////////////////////////////////////
// This is the main() code - it is the original thread
// ///////////////////////////////////////////////////////////////////////
main(int argc, char* argv[]){
	unsigned int CurrentPriority, MyPid;
	unsigned int NewThreadID;
	
	int listener;
	
	
	MyPid = pthread_self(); 
	CurrentPriority = getpriority( PRIO_PROCESS, 0 );
	// Create a new thread that will start executing at location
	//WorkThread NewThreadID = CreateAThread( (void *)(* WorkThread), &data);
	
	// Other main code
	struct addrinfo  hints, *servinfo, *p; //info for the server to know about itself
	struct sockaddr_storage their_addr; //connector's socket info
	socklen_t sin_size;
	struct sockaddr_in self;
	// Get the port number via the command line
	listener = argv[1];//grab port number
	
	memset(&hints, 0, sizeof hints);
	
	/*---Initialize address/port structure---*/
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(listener);//user assigned port number
	self.sin_addr.s_addr = INADDR_ANY;		
	
	// Establish the socket that will be used for listening
	fd = socket(AF_INET, SOCK_STREAM, 0); 
	
	// Do a bind of that socket
	bind( fd, (struct sockaddr*)&self, sizeof(self));
	
	
	// Set up to listen
	listen( fd, 5);//make larger later
	fdListen = fd;
	while( TRUE ){
        sin_size = sizeof their_addr;

		// Do the accept
		fdconn = accept( fdListen, (struct sockaddr *)&their_addr, &sin_size);
		
		out = CreateAThread( (void *)(*WorkThread), &fdConn);
	}
	
} // End of main
// This is the new thread that's created

int WorkThread( void *data ){
	int fdConn;
	fdConn = (int)data;
	//make input buffer
	char buffer[256];//buffer size of 256 chars
	int size;
	//recieve client's message
	do{
		//clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
		size = recv(fdConn, buffer, MAXBUF, 0);
	}while(size > 0);//keep reading until nothing is left
	
	

}


