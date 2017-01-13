#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   //if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
   // error("setsockopt(SO_REUSEADDR) failed");

   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5632;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   //int flags = fcntl(newsockfd, F_GETFL, 0);
   //fcntl(newsockfd, F_SETFL, flags | O_NONBLOCK);
   /* If connection is established then start communicating */
   while(1){
   	bzero(buffer,256);
   	n = read( newsockfd,buffer,255 );
   
  	if (n < 0) {
 	    perror("ERROR reading from socket");
      	    exit(1);
   	}
   
   	
   
   	/* Write a response to the client */
	//bzero(buffer,256);
	//sprintf(buffer,"Ack");
   	if((float)rand()/RAND_MAX<0.5){
		printf("Received a message -> %s\n",buffer);
		n = write(newsockfd,"Ack",3);
	}	
   }
      
   return 0;
}
