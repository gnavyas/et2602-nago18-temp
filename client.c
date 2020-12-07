#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in serverAddr, client;
	int cliFd, connectionFd, length;
	
	cliFd = socket(AF_INET, SOCK_STREAM, 0);
	if(cliFd == -1) {
		fprintf(stderr, "%% Socket couldn't be created. Exiting\n");
	}
	
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	serverAddr.sin_port = htons(33333); // change port later to be cmd 

	if(connect(cliFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
		fprintf(stderr, "%% Couldn't connect to server. Exiting\n"); 
		exit(0); 
	}
	// communicate	
	close(cliFd);
	return 0;
}
