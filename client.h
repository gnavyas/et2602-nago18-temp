// Header file inclusions
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

// Defining constants
#define BUFLEN 512 // buffer size
#define OK "OK\n"
#define ERROR "ERROR\n"
#define IPLEN 16

// Function declarations
int get_ip_port(char *arg, char ip[], int *port);
void process_commands(int cliFd);

