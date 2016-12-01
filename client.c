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
	printf("__________MENU_________\n\t1.Login\n\t2.SignUp\n\t3.Exit\n\nInsert your choise: ");
	gets(choise);
}
void second_menu(char* choise){
	printf("__________MENU_________\n\t1.Search Item\n\t2.Favorite List\n\t3.Cart List\n\t4.Logout\n\nInsert your choise: ");
	gets(choise);
}
void third_menu(char* choise){
	printf("__________FAVORITE LIST_________\n\t1.Add item to favorite list.\n\t2.Remove item from item list.\n\t3.My favorite list.\n\t4.Back.\n\nInsert your choise: ");
	gets(choise);
}
void fourth_menu(char* choise){
	printf("__________CART LIST_________\n\t1.Add item to cart list.\n\t2.Remove item from cart list\n\t3.My cart list\n\t4.Pay.\n\t5.Back\n\nInsert your choise: ");
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
	LABEL1:do{
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
				printf("exit!!\n");
				close(client_sock);
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
		LABEL2:do{
			second_menu(choise);
			i = atoi(choise);
		} while (i <=  0 || i > 4);
		switch(i){
			case 1:{
				Send_Request(client_sock,"401",result_code);
				Show_Message(result_code,temp);
				goto LABEL2;
				break;
			}
			case 2:{
				LABEL3:do{
					third_menu(choise);
					i = atoi(choise);
				} while (i <=  0 || i > 4);
				switch(i){
					case 1:{
						Send_Request(client_sock,"501",result_code);
						Show_Message(result_code,temp);
						goto LABEL3;
						break;
					}
					case 2:{
						Send_Request(client_sock,"502",result_code);
						Show_Message(result_code,temp);
						goto LABEL3;
						break;
					}
					case 3:{
						Send_Request(client_sock,"503",result_code);
						Show_Message(result_code,temp);
						goto LABEL3;
						break;
					}
					case 4:{
						goto LABEL2;
						break;
					}
				}
				break;
			}
			case 3:{
				LABEL4:do{
					fourth_menu(choise);
					i = atoi(choise);
				} while (i <=  0 || i > 5);
				switch(i){
					case 1:{
						Send_Request(client_sock,"601",result_code);
						Show_Message(result_code,temp);
						break;
					}
					case 2:{
						Send_Request(client_sock,"602",result_code);
						Show_Message(result_code,temp);
						break;
					}
					case 3:{
						Send_Request(client_sock,"603",result_code);
						Show_Message(result_code,temp);
						break;
					}
					case 4:{
						Send_Request(client_sock,"604",result_code);
						Show_Message(result_code,temp);
						break;
					}
					case 5:{
						goto LABEL2;
						break;
					}
				}
				goto LABEL4;
				break;
			}
			case 4:{
				Send_Request(client_sock,"301",result_code);
				Show_Message(result_code,temp);
				goto LABEL1;
				break;
			}
		}
	}
	close(client_sock);
	return 0;
}