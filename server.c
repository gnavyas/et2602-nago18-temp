#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PROTOCOLS "TEXT TCP 1.0" // constant msg

void send_commands(int connectionFd) {
	// get random commands and send it to client to execute
	// get output
}

int main(int argc, char *argv[]) {
	struct sockaddr_in serverAddr, client;
	int servFd, connectionFd, length;
	
	servFd = socket(AF_INET, SOCK_STREAM, 0);
	if(servFd == -1) {
		fprintf(stderr, "%% Socket couldn't be created. Exiting\n");
	}
	
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serverAddr.sin_port = htons(33333); // change port later to be cmd 

	if(bind(servFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
		fprintf(stderr, "%% Couldn't bind a name to socket. Exiting\n"); 
		exit(0); 
	}
	
	if ((listen(servFd, 1)) != 0) { 
		fprintf(stderr, "%% Listen call failed. Exiting\n"); 
		exit(0); 
	}
	
	length = sizeof(client);
	connectionFd = accept(servFd, (struct sockaddr *)&client, &length);
	// communicate
	fprintf(stdout, "%% Connected to the client\n");
	send(connectionFd, PROTOCOLS, sizeof(PROTOCOLS), 0);
	recv(cliFd, buffer, BUFLEN, 0);
	fprintf(stdout, "%% SERVER sent %s\n", buffer);

	if(strcmp(buffer, OK) == 0) {
		send_commands(connectionFd);
	}
	else {
		fprintf(stderr, "%% Closing client connection");
		// close connection here
	}

	close(servFd);
	return 0;
}
