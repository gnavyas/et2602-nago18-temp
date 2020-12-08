#include "client.h"

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

void process_commands(int cliFd) {
	// process server commands and execute them
	char buffer[BUFLEN];
	char command[5];
	double d1;
	double d2;
	double resultDouble;
	int randomChoice;
	int resultInt;
	int i1;
	int i2;
	
	recv(cliFd, buffer, BUFLEN, 0);
	fprintf(stdout, "** Server sent following command -- %s", buffer);
	
	if(strstr(buffer, "fadd") != NULL) {
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);
		resultDouble = d1 + d2;
		sprintf(buffer, "%8.8g", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "fdiv") != NULL) {
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);	
		resultDouble = d1 / d2;
		sprintf(buffer, "%8.8g", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "fmul") != NULL) {
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);
		resultDouble = d1 * d2;
		sprintf(buffer, "%8.8g", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "fsub") != NULL) {
		sscanf(buffer, "%s %lf %lf\n", command, &d1, &d2);	
		resultDouble = d1 - d2;
		sprintf(buffer, "%8.8g", resultDouble);
		fprintf(stdout, "** Sending answer %8.8g to server\n", resultDouble);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "add") != NULL) {
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);
		resultInt = i1 + i2;
		sprintf(buffer, "%d", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "div") != NULL) {
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);	
		resultInt = i1 / i2;
		sprintf(buffer, "%d", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "mul") != NULL) {
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);	
		resultInt = i1 * i2;
		sprintf(buffer, "%d", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else if(strstr(buffer, "sub") != NULL) {
		sscanf(buffer, "%s %d %d\n", command, &i1, &i2);
		resultInt = i1 - i2;
		sprintf(buffer, "%d", resultInt);
		fprintf(stdout, "** Sending answer %d to server\n", resultInt);
		send(cliFd, buffer, BUFLEN, 0);
	}
	else { // invalid operation requested
		send(cliFd, "0", 2, 0);
	}
	recv(cliFd, buffer, sizeof(buffer), 0);
	if(strcmp(buffer, OK) == 0)
		fprintf(stdout, "%% Server sent %s\n", OK);
	else
		fprintf(stdout, "%% Server sent %s\n", ERROR);
}

int main(int argc, char *argv[]) {
	struct sockaddr_in serverAddr, client;
	int cliFd, connectionFd, length;
	char buffer[BUFLEN];
	char ip[IPLEN];
	int port;

	
	if((argc != 2) || (get_ip_port(argv[1], ip, &port) == -1)) {
		fprintf(stderr, "Usage: ./server ipto_listenon:port\n\n");
		exit(0);
	}
	
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
	fprintf(stdout, "%% Connected to the server\n");
	// communicate
	recv(cliFd, buffer, BUFLEN, 0);
	fprintf(stdout, "** SERVER sent %s\n", buffer);
	send(cliFd, OK, sizeof(OK), 0);
	process_commands(cliFd);
	fprintf(stdout, "** Processing server requests done. Closing connection\n");
	close(cliFd);
	return 0;
}
