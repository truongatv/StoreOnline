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


void Send_Request(int client_sock,char* request_code,char* result_code);
void Show_Message(char* respond);
void Send_UserName(int client_sock,char*request_code,char* userName,char* result_code);
void Send_State(int client_sock,char* request_code,char* username,char* result_code);
void Send_Passwd(int client_sock,char* request_code,char*userName,char* passwd,char* result_code);
void Send_Item(int client_sock,char* request_code, char* userName,char*itemName,int number,char* result_code);

#endif