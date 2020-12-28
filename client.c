#include "client.h"

int get_ip_port(char *arg, char ip[], int *port) {
	// arg has a.b.c.d:pppp, so put a.b.c.d in ip and pppp in port
	int status = -1;
	char temp[IPLEN];
	char *t;
	
	t = strchr(arg, ':');
	if(t == NULL)
		return status; // invalid input
	
	strcpy(temp, &arg[t - arg + 1]);
	*port = atoi(temp); // get port
	arg[t - arg] = '\0';
	strcpy(ip, arg); // get ip
	
	return 0;
}

void process_commands(int cliFd) {
	// process server commands and execute them
	char buffer[BUFLEN];
	char command[5];
	char *ptr;
	double d1;
	double d2;
	double resultDouble;
	int randomChoice;
	int resultInt;
	int i1;
	int i2;
	
	recv(cliFd, buffer, BUFLEN, 0);
	ptr = strchr(buffer, '\n');
	buffer[ptr - buffer] = '\0';
	fprintf(stdout, "** Server sent following command -- %s\n", buffer);
	
	if(strstr(buffer, "fadd") != NULL) { // fadd val1 val2 command
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);
		resultDouble = d1 + d2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%8.8g\n", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "fdiv") != NULL) { // fdiv val1 val2 command
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);	
		resultDouble = d1 / d2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%8.8g\n", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "fmul") != NULL) { // fmul val1 val2 command
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);
		resultDouble = d1 * d2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%8.8g\n", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "fsub") != NULL) { // fsub val1 val2 command
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);	
		resultDouble = d1 - d2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%8.8g\n", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "add") != NULL) { // add val1 val2 command
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);
		resultInt = i1 + i2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%d\n", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "div") != NULL) { // div val1 val2 command
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);	
		resultInt = i1 / i2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%d\n", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "mul") != NULL) { // mul val1 val2 command
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);	
		resultInt = i1 * i2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%d\n", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "sub") != NULL) { // sub val1 val2 command
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);
		resultInt = i1 - i2;
		bzero(buffer, BUFLEN);
		sprintf(buffer, "%d\n", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else { // invalid operation requested
		send(cliFd, "0\n", 3, 0);
	}
	bzero(buffer, BUFLEN);
	recv(cliFd, buffer, sizeof(buffer), 0);
	fprintf(stdout, "%% Server sent %s\n", buffer);
}

int main(int argc, char *argv[]) {
	struct sockaddr_in serverAddr, client;
	int cliFd, connectionFd, length;
	char buffer[BUFLEN];
	char ip[IPLEN];
	int port;

	
	// check if valid cmd args
	if((argc != 2) || (get_ip_port(argv[1], ip, &port) == -1)) {
		fprintf(stderr, "Usage: ./server ipto_listenon:port\n\n");
		exit(0);
	}
	
	// create sockets
	cliFd = socket(AF_INET, SOCK_STREAM, 0);
	if(cliFd == -1) {
		fprintf(stderr, "%% Socket couldn't be created. Exiting\n");
	}
	
	// embed ip, port, proto details
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = inet_addr(ip); 
	serverAddr.sin_port = htons(port); // change port later to be cmd 

	// connect to the server
	if(connect(cliFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) {
		fprintf(stderr, "%% Couldn't connect to server. Exiting\n"); 
		exit(0); 
	}
	fprintf(stdout, "%% Connected to the server %s:%d\n", ip, port);
	// communicate
	recv(cliFd, buffer, BUFLEN, 0);
	fprintf(stdout, "** SERVER sent %s\n", buffer);
	send(cliFd, OK, sizeof(OK), 0);
	process_commands(cliFd);
	fprintf(stdout, "** Processing server requests done. Closing connection\n");
	close(cliFd);
	return 0;
}
