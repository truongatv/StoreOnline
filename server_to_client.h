#ifndef _SERVER_TO_CLIENT_H_
#define _SERVER_TO_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include "account.h"
#include "account.c"

void Get_UserName(int* server_sock);
void Get_Passwd(int* server_sock, char* result_code);

#endif