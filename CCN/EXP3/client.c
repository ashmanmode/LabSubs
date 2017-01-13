#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char buffer[256];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
	
   portno = atoi(argv[2]);
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
   int ii = 0;
   int flags = fcntl(sockfd, F_GETFL, 0);
   fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
   //struct timeval tv;

	//tv.tv_sec = 30;  /* 30 Secs Timeout */
//	tv.tv_usec = 0;  // Not init'ing this can cause strange errors

//	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

   int rep_count = 0;
   while(1){	
   	
	sleep(1);
	bzero(buffer,256);
   	sprintf(buffer,"%d",ii);

   	/* Send message to the server */
   	n = write(sockfd, buffer, strlen(buffer));
	printf("\nSending %s",buffer);
   
   	if (n < 0) {
    	  perror("\nERROR writing to socket");
   	   exit(1);
   	}
   
   	/* Now read server response */
   	bzero(buffer,256);
        
	
   	//n = read(sockfd, buffer, 255);
	//printf("\nAck received of size : %d!",n);
   	struct pollfd fd;
	int ret;

	fd.fd = sockfd; // your socket handler 
	fd.events = POLLIN;
	ret = poll(&fd, 1, 3000); // 1 second for timeout
	switch (ret) {
    		case -1:
        		printf("\nError in reading");
        		break;
    		case 0:
        		printf("\n**TIMEOUT** No Ack received");
			//rep_count++;
			//if(rep_count==2)
			//{	printf("\nExhausted retrials..Moving to next message!");
			//	rep_count=0;
			//	ii=(ii+1)%10;
			//}
			//else
			//	printf("\nRetrying trial no:%d",rep_count); 
        		break;
    		default:
        		recv(sockfd,buffer,sizeof(buffer), 0); // get your data
			printf("\nAck received :)");
			ii=(ii+1)%1000;
			rep_count=0;
        		break;
	}
   }
   return 0;
}
