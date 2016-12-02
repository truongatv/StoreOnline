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

void Excute_Request(int server_sock,char* request_code,MYSQL*con);
void Send_Message(int server_sock,char* request_code);
void Send_UserName_Respond(int server_sock,char* request_code,char* user_name,MYSQL* con);
void Send_Passwd_Respond(int server_sock, char* request_code, char* user_name,char* passwd,MYSQL*con);

#endif