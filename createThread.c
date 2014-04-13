#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <crypt.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>

#define MAXBUF		1024
#define TRUE 1
#define REQUESTOK	"200 OK"
#define REQUESTBAD	"404 File not found"
#define PASSWD	"Hello"
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
	int numPro = 0;
	
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
	

		pid = fork();
		if(pid > 0){
			WorkThread(fdConn, pid);
			kill(pid, SIGTERM);//marks child process as dead/zombie to be killed at program exit
			numPro--;
		}
		else{
			numPro++;
		}
		
	
	}
	
} // End of main
// This is the new thread that's created
//Legacy name, kept for convinience but not actually a thread. Refactor
int WorkThread( int fdConn, pid_t pid ){
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
	
	
	
	size=recv(fdConn, buffer, MAXBUF, 0);

	printf("%s\n", buffer);
	if(strcmp("mwfitzgibbon", buffer) == 0){
		
		//gen unique random number
		time_t t;
		char urn1;
		char urn2;
		srand((unsigned) time(&t));
		
		char urnS[3] = {('A' + rand()%26), ('A' + rand()%26), '\0'};
		
		
		printf("%s\n", urnS);
		if(	(send(fdConn, urnS, strlen(urnS), 0)) < 0){
			printf("Error in send\n");
			//kill self
		}
		bzero(buffer, MAXBUF);
		
		int rConfirm = 88;
		while(rConfirm != 0){
			if ( rConfirm = recv( fdConn, buffer, MAXBUF, 0 ) < 0 ){
				// Good programming practice will have you generate an error message 
				// here if the recv()  call fails.
				perror("Client: recieve");
			}	
		
        
		
		}

		printf("%s\n", buffer);
		char* check =  crypt("Hello", urnS);
		if(strcmp(check, buffer) == 0){
			printf("Passwords match\n");
			
			bzero(buffer, MAXBUF);
			
			
			rConfirm = 88;
			while(rConfirm != 0){
				if ( rConfirm = recv( fdConn, buffer, MAXBUF, 0 ) < 0 ){
					// Good programming practice will have you generate an error message 
					// here if the recv()  call fails.
					perror("Client: recieve");
				}	
			}	
			
			char line[MAXBUF];
			strcpy(line, buffer);
			
			//parsing influenced from solution found at csl.mtu.edu
			/*
			char* token;
			token = strtok(line, " ");
			int i = 0;
			char* path;
			char* args;
			printf("ping\n");
			while(token != NULL){
				if(i ==0){
					strcpy(path, token);
				}
				else{
					strcat(args, token);
					strcat(args, " ");
				}
				i++;
				token = strtok(line, " ");
			}
			*/
			
			
			dup2(fdConn, STDOUT_FILENO);
			dup2(fdConn, STDERR_FILENO);
			//execl(path, args);
			system(line);
			
		}
		else{
			printf("Incorrect password, exiting attempt\n");
			//kill self
		}
	}
	else{
		//incorrect username recieved
		if(	(send(fdConn, "ERR", strlen("ERR"), 0)) < 0){
			printf("Error in send\n");
			
		}
		//kill self
	}
	
	close(fdConn);
	

}

// End of WorkThread


