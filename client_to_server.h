#ifndef _CLIENT_TO_SERVER_H_
#define _CLIENT_TO_SERVER_H_

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

void Send_UserName(int* client_sock,char* userName,char* result_code);
void Send_Passwd(int* client_sock,char*userName,char* passwd,char* result_code);

#endif