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
#include <readline/readline.h>

void set_completion_array(char* temp);
char **item_name_completion(const char *, int, int);
char *item_name_generator(const char *, int);
void Send_Request(int client_sock,char* request_code,char* result_code);
void Show_Message(char* respond,char* result);
void Send_UserName(int client_sock,char*request_code,char* result_code);
void Send_State(int client_sock,char* request_code,char* result_code);
void Send_Passwd(int client_sock,char* request_code,char* passwd,char* result_code);
void Send_Item(int client_sock,char* request_code,char* result_code);
void Send_Info(int client_sock,char* info_type,char* request_code,char* info,char* result_code);

#endif