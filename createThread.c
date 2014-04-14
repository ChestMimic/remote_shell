#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAXBUF		1024
#define TRUE 1
int WorkThread(int fdConn, pid_t pid);
// ///////////////////////////////////////////////////////////////////////
// This is the main() code - it is the original thread
// ///////////////////////////////////////////////////////////////////////
main(int argc, char* argv[]){
	unsigned int CurrentPriority;
	unsigned int NewThreadID;
	
	int listener;
	int fd;
	pid_t pid;
	
	CurrentPriority = getpriority( PRIO_PROCESS, 0 );
	// Create a new thread that will start executing at location
	//WorkThread NewThreadID = CreateAThread( (void *)(* WorkThread), &data);
	
	// Other main code
	struct addrinfo *servinfo, *p; //info for the server to know about itself
	struct sockaddr_storage their_addr; //connector's socket info
	socklen_t sin_size;
	struct sockaddr_in self;
	
	
	// Get the port number via the command line
	listener = atoi(argv[1]);//grab port number
	printf("%d\n", listener);
	
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
	time_t timer;
	char mostrecenttimestamp[25];
	struct tm* tm_info;
	
	while( TRUE ){
        sin_size = sizeof their_addr;
		printf("waiting for next accept\n");
		// Do the accept
		int fdConn = accept( fdListen, (struct sockaddr *)&their_addr, &sin_size);	
		time(&timer);
		tm_info = localtime(&timer);
		strftime(mostrecenttimestamp, 25, "%Y:%m:%d%H:%M:%S", tm_info);
		puts(mostrecenttimestamp);	
		printf("Accept made at: %s", mostrecenttimestamp);
		
	

		pid = fork();
		if(pid > 0){
			WorkThread(fdConn, pid);
			kill(pid, SIGTERM);//marks child process as dead/zombie to be killed at program exit
			
		}
		
		
	
	}
	
} // End of main


// This is the new thread that's created
//Legacy name, kept for convinience but not actually a thread. Refactor
int WorkThread( int fdConn, pid_t pid ){
	char buffer[MAXBUF];
	char buffer_out[MAXBUF];
	bzero(buffer, MAXBUF);
	bzero(buffer_out, MAXBUF);
	
	
	
	
	

}

// End of WorkThread


