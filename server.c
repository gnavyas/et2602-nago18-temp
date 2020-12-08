#include "server.h"

int get_ip_port(char *arg, char ip[], int *port) {
	int status = -1;
	char temp[IPLEN];
	char *t;
	
	t = strchr(arg, ':');
	if(t == NULL)
		return status;
	
	strcpy(temp, &arg[t - arg + 1]);
	*port = atoi(temp);
	arg[t - arg] = '\0';
	strcpy(ip, arg);
	
	return 0;
}

void send_commands(int connectionFd) {
	// get random commands and send it to client to execute
	char buffer[BUFLEN];
	char calcInt[4][10] = {"add", "div", "mul", "sub"};
	char calcDouble[4][10] = {"fadd", "fdiv", "fmul", "fsub"};
	char tempBuf[50];
	double d1;
	double d2;
	double resultDouble;
	double p = 0.00001; // precision checking
	int randomChoice;
	int resultInt;
	int i1;
	int i2;
	
	srand(time(0));
	randomChoice = rand() % 2; // generates 0 or 1
	if(randomChoice) {
		// let's send int nums
		i1 = rand() % MAXADDRANGE;
		i2 = rand() % MAXADDRANGE;
		sprintf(tempBuf, "%d %d", i1, i2);
		randomChoice = rand() % 4;
		sprintf(buffer, "%s %s\n", calcInt[randomChoice], tempBuf);
		fprintf(stdout, "%% Sending command to execute -- %s", buffer);
		send(connectionFd, buffer, BUFLEN, 0);
		recv(connectionFd, buffer, BUFLEN, 0);
		fprintf(stdout, "%% Client returned the value %s\n", buffer);
		sscanf(buffer, "%d", &resultInt);
		switch(randomChoice) {
			case 0: (resultInt == i1 + i2) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
			case 1: (resultInt == i1 / i2) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
			case 2: (resultInt == i1 * i2) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
			case 3: (resultInt == i1 - i2) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
		}
	}
	else {
		// let's send double nums
		d1 = (float) rand() / RAND_MAX;
		d2 = (float) rand() / RAND_MAX;
		sprintf(tempBuf, "%8.8g %8.8g", d1, d2);
		sscanf(tempBuf, "%lf %lf", &d1, &d2);
		randomChoice = rand() % 4;
		sprintf(buffer, "%s %s\n", calcDouble[randomChoice], tempBuf);
		fprintf(stdout, "%% Sending command to execute -- %s", buffer);
		send(connectionFd, buffer, BUFLEN, 0);
		recv(connectionFd, buffer, BUFLEN, 0);
		fprintf(stdout, "%% Client returned the value %s\n", buffer);
		sscanf(buffer, "%d", &resultInt);
		switch(randomChoice) {
			case 0: ((resultDouble - p < d1 + d2) && (resultDouble + p > d1 + d2)) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
			case 1: ((resultDouble - p < d1 / d2) && (resultDouble + p > d1 + d2)) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
			case 2: ((resultDouble - p < d1 * d2) && (resultDouble + p > d1 + d2)) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
			case 3: ((resultDouble - p < d1 - d2) && (resultDouble + p > d1 + d2)) ? send(connectionFd, OK, sizeof(OK), 0) : send(connectionFd, ERROR, sizeof(ERROR), 0);
				break;
		}
	}

}

int main(int argc, char *argv[]) {
	struct sockaddr_in serverAddr, client;
	int servFd, connectionFd, length;
	char buffer[BUFLEN];
	char ip[IPLEN];
	int port;

	
	if((argc != 2) || (get_ip_port(argv[1], ip, &port) == -1)) {
		fprintf(stderr, "Usage: ./server ipto_listenon:port\n\n");
		exit(0);
	}

	servFd = socket(AF_INET, SOCK_STREAM, 0);
	if(servFd == -1) {
		fprintf(stderr, "%% Socket couldn't be created. Exiting\n");
	}
	
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serverAddr.sin_port = htons(port); 

	if(bind(servFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
		fprintf(stderr, "%% Couldn't bind a name to socket. Exiting\n"); 
		exit(0); 
	}
	
	fprintf(stdout, "%% Server started successfully on %s:%d\n", ip, port);
	if ((listen(servFd, 1)) != 0) { 
		fprintf(stderr, "%% Listen call failed. Exiting\n"); 
		exit(0); 
	}
	
	length = sizeof(client);
	while(1) {
		fprintf(stdout, "%% Waiting for the new client to connect\n");
		connectionFd = accept(servFd, (struct sockaddr *)&client, &length);
		fprintf(stdout, "%% New Client has connected\n");
		// communicate
		fprintf(stdout, "%% Connected to the client\n");
		send(connectionFd, PROTOCOLS, sizeof(PROTOCOLS), 0);
		recv(connectionFd, buffer, BUFLEN, 0);
		fprintf(stdout, "%% SERVER sent %s\n", buffer);

		if(strcmp(buffer, OK) == 0) {
			send_commands(connectionFd);
		}
		fprintf(stderr, "%% Closing client connection\n\n");
		// close connection here
		close(connectionFd);
	}
	close(servFd);
	return 0;
}
