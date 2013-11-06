#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>
int WorkThread( void * ); // Prototype


unsigned int CreateAThread( void *, int *); // Prototype
// ///////////////////////////////////////////////////////////////////////
// This is the main() code - it is the original thread
// ///////////////////////////////////////////////////////////////////////
main(){
	unsigned int CurrentPriority, MyPid;
	unsigned int NewThreadID;
	// Create a new thread that will start executing at location
	WorkThread NewThreadID = CreateAThread( (void *)(* WorkThread), &data);
	// Other main code
	
	
	// Get the port number via the command line
	
	// Establish the socket that will be used for listening
	fd = socket( ????? )
	// Do a bind of that socket
	bind( fd, ???? )
	// Set up to listen
	listen( fd, ??? )
	fdListen = fd;
	while( TRUE ){
		// Do the accept
		fdconn = accept( fdListen, ???? );
		
		out = CreateAThread( (void *)(*WorkThread), &fdConn);
	}
	
} // End of main
// This is the new thread that's created

int WorkThread( void *data ){
	int fdConn;
	fdConn = (int)data;

}
// End of WorkThread