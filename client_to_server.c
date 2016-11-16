#include "client_to_server.h"
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
void Send_UserName(int client_sock,char* userName,char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];

	do{
		printf("\nInsert userid:");
		memset(buff,'\0',(strlen(buff)+1));
		gets(buff);
	}while((int)strlen(buff) == 0);

	strcpy(userName,&buff[0]);

	bytes_sent = send(client_sock,"100",4,0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}

	bytes_sent = send(client_sock,userName,strlen(userName),0);
	if(bytes_sent < 0){
		//error
	}
	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}
	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);

}

void Send_Passwd(int client_sock,char*userName,char* passwd,char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];

	printf("\nInsert passwd:");
	memset(buff,'\0',(strlen(buff)+1));
	gets(buff);
	strcpy(passwd,&buff[0]);

	char* PassM = (char*)malloc(sizeof(char)*1024);
	strcpy(PassM,userName);
	strcat(PassM,"//");
	strcat(PassM,passwd);

	bytes_sent  = send(client_sock,"101",4,0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}

	bytes_sent = send(client_sock,PassM,strlen(PassM),0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}
	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);
}

void Send_Item(int client_sock, char* userName,char* passwd,char*itemName,char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];

	char* PassM = (char*) malloc(sizeof(char)*1024);
	strcpy(PassM,userName);
	strcat(PassM,"//");
	strcat(PassM,passwd);
	strcat(PassM,"//");
	strcat(PassM,itemName);

	bytes_sent = send(client_sock,"401",4,0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}

	bytes_sent = send(client_sock,PassM,strlen(PassM),0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}
	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);
	
}