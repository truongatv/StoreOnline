#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "client_to_server.c"
#define PORT 5550


void first_menu(char* choise){
	printf("__________MENU_________\n\t1.Login\n\t2.SignUp\n\t3.Exit\n\nInsert your choise:");
	gets(choise);
}
void second_menu(char* choise){
	printf("__________MENU_________\n\t1.LogOut\n");
	gets(choise);
}
int main(){

	int client_sock;
	char buff[1024];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received;
	int total_byte_sent =0;
	int i ;

	char* choise = (char*)malloc(sizeof(char)*4);
	char* result_code = (char*)malloc(sizeof(char)*10);
	char* temp = (char*)malloc(sizeof(char)*10);

	client_sock=socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
		printf("\nError!Can not connect to sever!Client exit imediately! ");
		return 0;
	}
	bytes_received = recv(client_sock,buff,1024,0); //blocking
	if (bytes_received < 0){
		printf("\nError!Can not receive data from client!");
		close(client_sock);
	}
	else{
		buff[bytes_received] = '\0';
		puts(buff);
	}
	do{
		do{
			first_menu(choise);
			i = atoi(choise);
		} while (i <=  0 || i>3);

		
		switch(i){
			case 1:{
				Send_Request(client_sock,"101",result_code);
				Show_Message(result_code,temp);
				if(strcmp(temp,"1") == 0){
					do{
						Send_Request(client_sock,"102",result_code);
						Show_Message(result_code,temp);
					}
					while(strcmp(temp,"3") == 0);
				}
				break;
			}
			case 2:{
				Send_Request(client_sock,"201",result_code);
				Show_Message(result_code,temp);
				if(strcmp(temp,"1") == 0){
					Send_Request(client_sock,"202",result_code);
					Show_Message(result_code,temp);
				}
				break;
			}
			case 3:{
				return 0;
			}
		}

	} while (strcmp(temp,"0") == 0);
	if(strcmp(temp,"4") == 0){
		printf("exit!!\n");
		close(client_sock);
		return 0;
	}
	if(strcmp(temp,"2") == 0){
		printf("Welcome back!\n");
		do{
			second_menu(choise);
			i = atoi(choise);
		} while (i <=  0 || i>3);
	}
	close(client_sock);
	return 0;
}