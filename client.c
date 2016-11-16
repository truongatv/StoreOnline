#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "client_to_server.c"
#include "client_to_server.h"

int main(){
	int client_sock;
	char buff[1024];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received, sin_size;

	client_sock=socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(6550);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	sin_size = sizeof(struct sockaddr);	

	if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
		printf("\nError!Can not connect to sever!Client exit imediately! ");
		return 0;
	}
	char* reply = (char*) malloc(sizeof(char) *1024);
	while(1){
		
	}
	printf("Bye!\n");
	close(client_sock);
	return 0;
}
/*
888 - ready
100 - send username
101 - send passm
103 - not mach username
104 - acc is current online
105 - acc is current offline
107 - not match passwd
108 - match passwd
*/

void Login(int* client_sock,char* userName,char*passwd,char* result_code){
	Send_UserName(client_sock,userName,result_code);
	if(strcmp(result_code,"103") == 0){
		//error not match username
		printf("Not match UserName!\n");
		return;
	}
	else{
		if(strcmp(result_code,"104") == 0){
			// error acc is online
			printf("Account currently online!\n");
		} else{
			int retry_times = 0;
			do{
				retry_times++;
				Send_Passwd(client_sock,userName,passwd,result_code);
				if(strcmp(result_code,"108") == 0){
					break;
				}
			} while(retry_times <= 5);
			if(strcmp(result_code,"108") == 0){
				printf("Login\n");
				return;
			} else{
				printf("Error \n");
				return;
			}
		}
	}
}

void Signup(int* client_sock,char* userName, char* passwd,char* result_code){
	Send_UserName(client_sock,userName,result_code);
	if(strcmp(result_code,"103") != 0){
		printf("Already has acc\n");
		return;
	} else{
		Send_Passwd(client_sock,userName,passwd,result_code);
		return;
	}
}

void Search_Item(int* client_sock, char* userName,char* passwd,char* result_code){
	
}