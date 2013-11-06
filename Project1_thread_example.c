//  ///////////////////////////////////////////////////////////////////////
//  This is a simple program to test out the pthread package on Linux.
//  It can be built on a Linux machine with the command line 
//
//   gcc  -lpthread  -g -o proj2_thread_example proj2_thread_example.c
//
//  2013-11-04      Minor fixes to this code.  Now compiles cleanly
//  ///////////////////////////////////////////////////////////////////////
//
#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <asm/errno.h>

int             WorkThread( void * );            // Prototype
unsigned int    CreateAThread( void *, int *);   // Prototype

//  ///////////////////////////////////////////////////////////////////////
//  This is the main() code - it is the original thread
//  ///////////////////////////////////////////////////////////////////////
main()
{
    int                     data = 3;
    unsigned int            CurrentPriority, MyPid;
    unsigned int            NewThreadID;

    // Get properties of this main thread
    MyPid = pthread_self();   
    CurrentPriority = getpriority( PRIO_PROCESS, 0 );
    printf( "From Main:  My ID is %ld and I have priority %d\n", 
		    MyPid, CurrentPriority );

    // Create a new thread that will start executing at location   WorkThread
    NewThreadID = CreateAThread( (void *)(*WorkThread), &data);
    printf( "From Main:  The ID of the created thread is %ld\n", NewThreadID );
    printf( "From Main:  Data passed to the new thread is = %d\n\n", data );

    sleep(4);                  // Wait for the new thread to finish
    return(0);
}        // End of main

//  ///////////////////////////////////////////////////////////////////////
//  This is the code executed by the new thread 
//  ///////////////////////////////////////////////////////////////////////
int    WorkThread( void *data )
{
    unsigned int            CurrentPriority, MyPid;

    sleep(1);
    MyPid = pthread_self();   
    CurrentPriority = getpriority( PRIO_PROCESS, 0 );
    printf( "Got to the new thread.  My ID is %ld and I have priority %d\n", 
		    MyPid, CurrentPriority );
    printf( "Data passed to the new thread is %d\n", (int *)data );
    return(0);
}        // End of WorkThread

// ///////////////////////////////////////////////////////////////////////////////
//           CreateAThread
//    Set up a new thread for the caller.  We need to be passed here:
//    Arg1:  The start address of the new thread
//    Arg2:  The address of an int or structure containing data for the new thread
//
//    We return the Thread Handle to the caller.
//    We print lots of errors if something goes wrong.  But we return anyway
// ///////////////////////////////////////////////////////////////////////////////

unsigned int    CreateAThread( void *ThreadStartAddress, int *data )
{
    int                  ReturnCode;
    pthread_t            Thread;
    pthread_attr_t       Attribute;

    ReturnCode = pthread_attr_init( &Attribute );
    if ( ReturnCode != 0 )
        printf( "Error in pthread_attr_init in CreateAThread\n" );
    ReturnCode = pthread_attr_setdetachstate( &Attribute, PTHREAD_CREATE_JOINABLE );
    if ( ReturnCode != 0 )
        printf( "Error in pthread_attr_setdetachstate in CreateAThread\n" );
    ReturnCode = pthread_create( &Thread, &Attribute, ThreadStartAddress, (void *)&data );
    if ( ReturnCode == EINVAL )                        /* Will return 0 if successful */
        printf( "ERROR doing pthread_create - The Thread, attr or sched param is wrong\n");
    if ( ReturnCode == EAGAIN )                        /* Will return 0 if successful */
        printf( "ERROR doing pthread_create - Resources not available\n");
    if ( ReturnCode == EPERM )                        /* Will return 0 if successful */
        printf( "ERROR doing pthread_create - No privileges to do this sched type & prior.\n");

    ReturnCode = pthread_attr_destroy( &Attribute );
    if ( ReturnCode )                                    /* Will return 0 if successful */
        printf( "Error in pthread_mutexattr_destroy in CreateAThread\n" );
    return( (unsigned int)Thread );
}                            // End of CreateAThread 
