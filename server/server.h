#ifndef _SERVER_H_
#define _SERVER_H_

#include "data.c"
#include "server_to_client.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
<<<<<<< HEAD
#define PORT 5555
=======
#include <arpa/inet.h>

#define PORT 6550
>>>>>>> cc48df9ba4b719707c24a5079afd593472f949d6
#define BACKLOG 20

void sig_chld(int signo);
int main();

#endif