/***************************************************************************

   Project1_Starter_Client.c

   This program does not compile but has the skeleton of what you need
       for a client web browser.
   It provides the skeleton for what you need to do to build a web
   client (browser).
   Functionality:
     Accept two arguments from the command line:
     1)  The port number that should be used to send to your server.  
         Obviously this should be the same port that you used when
         starting your server.
     2)  The name of the file you want to get from the server.

     Does the sequence required to send to the server:
       socket(),  connect(), send().
     Receives from the server:
       recv()  - note that the server may send it's data in multiple
                 packets so you should do recv() as long as data is available.
     Prints out whatever is received.

   You can use port 80 to get to an apache web server, or some
   other port number to test your own server.

   Compile with:
   gcc -o Browser -g Project1_Starter_Client.c

****************************************************************************/

#include       <stdlib.h>
#include       <sys/socket.h>
#include       <netinet/in.h>
#include       <stdio.h>
#include       <string.h>

#define         BUFFER_SIZE     2000

main ( int argc, char *argv[] )
    {
    int                family = AF_INET;       /* The default for most cases */
    int                type   = SOCK_STREAM;   /* Says it's a TCP connection */
    in_port_t          port;
    struct sockaddr_in sa;
    int                lsa = sizeof(sa);
    int                fdListen, fdConn, fd;
    char               ip_input_buffer[BUFFER_SIZE];
    char               ip_output_buffer[BUFFER_SIZE];
	
	struct sockaddr address;

    if ( argc < 4 ) {
        printf( "The program expects two arguments\n" );
        printf( "Browser <URL || IP address> <port number> <target file>\n" );
        exit(0);
    }

    if ((fd = socket ( AF_INET, SOCK_STREAM, 0 )) < 0)   {
	    // Good programming practice will have you generate an error message 
	    // here if the socket call fails.
		perror("Client: socket");
    }

    // set up the sockaddr_in structure.  This uses, among other things the 
    // port you've just entered.
    sa.sin_family       = AF_INET;
    sa.sin_port         = htons(argv[2]);               /* client & server see same port*/
    sa.sin_addr.s_addr  =  INADDR_ANY;                  /* the kernel assigns the IP addr*/

    if (connect( fd, /**/, lsa ) != 0 )  {
	    // Good programming practice will have you generate an error message 
	    // here if the connect()  call fails.
		perror("Client: connect");
    }
        
		
		
    // First clean out the output buffer (bzero is my recommendation), and then
    //   copy the get message into it.
	bzero(ip_output_buffer, BUFFER_SIZE);
	
	//create get message
	sprintf(ip_output_buffer, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", argv[2], argv[3]);

    if ( send( fd, ip_output_buffer, BUFFER_SIZE ) <= 0 )  {
	    // Good programming practice will have you generate an error message 
	    // here if the send()  call fails.
    }

    bzero( ip_input_buffer, sizeof(ip_input_buffer) );

    while(1)
    {
        if ( recv( fd, ip_input_buffer, sizeof(ip_input_buffer) - 2, 0 ) <= 0 )
	    // Good programming practice will have you generate an error message 
	    // here if the recv()  call fails.
        }
        printf( "%s", ip_input_buffer );
    }
}                                       /* End of main          */

