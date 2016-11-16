#include "server_to_client.h"
#include "account.c"
#include "account.h"

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

void Get_UserName(int server_sock){
	int bytes_sent,bytes_received;
	char buff[1024];

	bytes_sent = send(server_sock,"888",1024,0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(server_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}

	char* userName = (char*)malloc(sizeof(char)*50);

	strcpy(userName,&buff[0]);

	int status = Get_Status(userName);

	switch(status){
		case 0:{
			//not match username
			bytes_sent = send(server_sock,"103", 4,0);
			if(bytes_sent < 0){
				//error
			}
			break;
		}
		case 1:{
			// online
			bytes_sent = send(server_sock,"104",4,0);
			if(bytes_sent < 0){
				//error
			}
			break;
		}
		case 2:{
			//offline
			bytes_sent = send(server_sock,"105",4,0);
			if(bytes_sent < 0){
				//error
			}
			break;
		}
	}
}

void Get_Passwd(int server_sock, char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];

	bytes_sent = send(server_sock,"888",4,0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(server_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}
	buff[bytes_received] = '\0';

	char* PassM = (char*)malloc(sizeof(char)*100);
	char* userName = (char*)malloc(sizeof(char)*50);
	char* passwd = (char*)malloc(sizeof(char) *50);

	strcpy(PassM,&buff[0]);
	userName = strtok(PassM,"//");
	passwd = strtok(NULL,"//");

	int status = Get_Status(userName);
	if(status == 0){
		// signup
		Add_new_account(userName,passwd);
		bytes_sent = send(server_sock,"888", 4,0);
		if(bytes_sent < 0){
			//error
		}
		strcpy(result_code,"888");
		return;
	}

	status = Search(userName,passwd);

	switch(status){
		case 0:{
			//not match passwd
			bytes_sent = send(server_sock,"107",4,0);
			if(bytes_sent < 0){
				//error
			}
			strcpy(result_code,"107");
			break;
		}
		case 1:{
			// match passwd

			bytes_sent = send(server_sock,"108",4,0);
			if(bytes_sent < 0){
				//error
			}
			strcpy(result_code,"108");
			break;
		}
	}
}

void Get_Item(int server_sock){
	int bytes_sent,bytes_received;
	char buff[1024];

	char* PassM = (char*)malloc(sizeof(char) * 1024);
	char* userName = (char*) malloc(sizeof(char)*50);
	char* passwd = (char*)malloc(sizeof(char) * 50);
	char* itemName = (char*)malloc(sizeof(char)* 200);


	bytes_sent = send(server_sock,"888",4,0);
	if(bytes_sent < 0){
		//error
	}

	bytes_received = recv(server_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
	}
	buff[bytes_received] = '\0';

	strcpy(PassM,&buff[0]);
	userName = strtok(PassM,"//");
	passwd = strtok(NULL,"//");
	itemName = strtok(NULL,"//");

	//get account
	struct account acc;
	acc = Get_Account(userName,passwd);

	
}


