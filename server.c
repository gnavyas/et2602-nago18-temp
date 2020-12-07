#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

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
	
	if ((listen(servFd, 5)) != 0) { 
		fprintf(stderr, "%% Listen call failed. Exiting\n"); 
		exit(0); 
	}
	
	length = sizeof(client);
	connectionFd = accept(servFd, (struct sockaddr *)&client, &length);
	// communicate
	close(servFd);
	return 0;
}
