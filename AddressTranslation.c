// This code shows how to translate back and forth between
//   a hostname and an ip address.

#include        <stdio.h>
#include        <stdlib.h>
#include        <netdb.h>
#include        <arpa/inet.h>
#include        <string.h>

int main(int argc, char **argv) {
    char            *ptr, **pptr;
    char            str[INET6_ADDRSTRLEN];
    struct hostent  *hptr;
    char            IPAddress[100];

    if ( argc < 2 )  {
        printf( "Usage: %s <hostname or IP Address>\n", argv[0]);
        exit(0);
    }
    ptr = *++argv;       // Get the argument after the program name
    if ( (hptr = gethostbyname(ptr)) == NULL) {
        printf("gethostbyname error for host: %s: %s\n",
                ptr, hstrerror(h_errno));
        exit(0);
    }
    printf("official hostname: %s\n", hptr->h_name);

    // Are there other names for this site?
    for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)   {
        printf("    alias: %s\n", *pptr);
    }
    pptr = hptr->h_addr_list;   // Assumes address type is AF_INET
    for ( ; *pptr != NULL; pptr++) {
        strcpy( IPAddress,  inet_ntop(hptr->h_addrtype, 
                       *pptr, str, sizeof(str)));
        printf("\taddress: %s\n", IPAddress );

        // For each of the IP addresses, find the host address
        if ( (hptr = gethostbyaddr(*pptr, hptr->h_length,
                                   hptr->h_addrtype)) == NULL)
            printf("\t(gethostbyaddr failed)\n");
        else if (hptr->h_name != NULL)
            printf("\tname = %s\n", hptr->h_name);
        else
            printf("\t(no hostname returned by gethostbyaddr)\n");
    }             // End of for loop
    exit(0);
}                 // End of main
