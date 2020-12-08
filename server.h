// Header file inclusions
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

// Defining constants
#define PROTOCOLS "TEXT TCP 1.0" // constant msg
#define MAXADDRANGE 100000 // Can change this to (maxsize of int / 2)
#define BUFLEN 512 // buffer size
#define OK "OK"
#define ERROR "ERROR"
#define IPLEN 16

// Function declarations
int get_ip_port(char *arg, char ip[], int *port);
void send_commands(int connectionFd);

