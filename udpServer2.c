#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define MAXLINE 1024

void func(int sockfd, struct sockaddr_in *cliaddr)
{
	char buffer[MAX];
	int n;
	
	for (;;) {
		bzero(buffer, MAX);
		int len, msglen;
 
		 len = sizeof(cliaddr);
		 
		 msglen= recvfrom(sockfd, (char *) buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*) &cliaddr, &len);
		
		buffer[msglen] = '\0';
		
		printf("From client: %s\t To client : ", buffer);
		bzero(buffer, MAX);
		n = 0;
		
		while ((buffer[n++] = getchar()) != '\n')
			;

		
		sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

		
		if (strncmp("exit", buffer, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}


int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	
	

	
	func(connfd, &cli);

	
	close(sockfd);
}

