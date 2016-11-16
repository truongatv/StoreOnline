#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>

#define PORT 6550
#define BACKLOG 20

struct account
{
	/* data */
	char* userid;
	char* passwd;
	char* status;
	struct account* next;
};
struct account *first,*last;
void error_sending();
void error_recving();
int Get_Data();
void Insert_ToFirst(char* userid,char* passwd,char* status);
void Insert_ToLast(char* userid,char* passwd,char* status);
char* Search(char* userid_received);
char* Get_Status(char* userid_received);
void recv_passM(int client,int type);
void recv_signup_request(int client);
void Set_Status(char* userid_received,char* status);
void recv_login_request(int client);
void recv_logout_request(int client);

#endif