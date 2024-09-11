
#include <stdio.h>      /* Contains common I/O functions */
#include <sys/types.h>  /* Contains definitions of data types used in system calls */
#include <sys/socket.h> /* Includes definitions of structures needed for sockets */
#include <netinet/in.h> /* Contains constants and structures needed for internet domain addresses. */
#include <unistd.h>     /* Contains standard unix functions */
#include <stdlib.h>     /* For atoi() and exit() */
#include <string.h> 	/* For memset() */
#include <arpa/inet.h>  /* For inet_pton() */
#include <time.h>       /* For retrieving the time */

int main(int argc, char** argv)
{
	/* The port number */	
	int port = -1;
	
	/* The file descriptor representing the connection to the client */
	int connfd = -1;
	
	/* The size of the time buffer */
	#define TIME_BUFF_SIZE 100
	
	/* The buffer to store the time */
	char timeBuff[TIME_BUFF_SIZE];
	
	/* The number of bytes read */
	int numRead = -1;
		
	/* The structures representing the server address */
	sockaddr_in serverAddr;
	
	/* Stores the size of the client's address */
	socklen_t servLen = sizeof(serverAddr);	
	
	/* Make sure the user has provided the port number to
	 * listen on
	 */
	if(argc < 3)
	{
		/* Report an error */
		fprintf(stderr, "USAGE: %s <HOST IP> <PORT #>", argv[0]);
		exit(-1);	
	}
	
	/* Get the port number */
	port = atoi(argv[2]);
		
	
	/* Make sure that the port is within a valid range */
	if(port < 0 || port > 65535)	
	{
		fprintf(stderr, "Invalid port number\n");
		exit(-1);
	} 
	
	/* Connect to the server */
	if((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	
		
	/* Set the structure to all zeros */
	memset(&serverAddr, 0, sizeof(serverAddr));
		
	/* Set the server family */
	serverAddr.sin_family = AF_INET;
	
	/* Convert the port number to network representation */	
	serverAddr.sin_port = htons(port);
	
	
	/**
	 * Convert the IP from the presentation format (i.e. string)
	 * to the format in the serverAddr structure.
	 */
	if(!inet_pton(AF_INET, argv[1], &serverAddr.sin_addr))
	{
		perror("inet_pton");
		exit(-1);
	}
	
	
	/* Lets connect to the client. This call will return a socket used 
	 * used for communications between the server and the client.
	 */
	if(connect(connfd, (sockaddr*)&serverAddr, sizeof(sockaddr))<0)
	{
		perror("connect");
		exit(-1);
	}	
	
		
	/* Receive whatever the server sends */
	if((numRead = read(connfd, timeBuff, TIME_BUFF_SIZE-1)) < 0)
	{
		perror("read");	
		exit(-1);
	}
	
	/* NULL terminate the received string */
	timeBuff[numRead] = '\0';
		
	fprintf(stderr, "The time received from the server: %s\n", timeBuff);
	fprintf(stderr, "Bytes read: %d\n", numRead);
	
	
	/* The thank you message */
	char thankBuff[] = "Thank You!";
	
	/* Thank the server */
	if(write(connfd, thankBuff, sizeof(thankBuff)) < 0)
	{
		perror("write");
		exit(-1);
	}
		
	/* Close the connection socket */	
	close(connfd);
		
	return 0;
}





