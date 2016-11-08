#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*
100-login;
101-signup;
102-logout;
999-exit;
888-ready;
*/
struct user
{
	char* userid;
	char* pass;
	char* mail;
};
struct MatHang
{
	char* name;
	int id;
	int gia;
};
struct cart
{
	struct user name;
	int* list_id;
};
void menu_login();
void error_send();
void error_recv();

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
		int menu_choise =0;
		do{
			menu_login(&menu_choise);
		} while(menu_choise < 1 || menu_choise >3);
		if(menu_choise == 3){
			bytes_sent = send(client_sock,"999",4,0);
			if(bytes_sent == -1){
				error_send();
			}
			close(client_sock);
			return 0;
		}
		while(getchar()!='\n');
		char* userid_sent = (char*) malloc(sizeof(char) * 50);
		do{
			printf("\nInsert userid:");
			memset(buff,'\0',(strlen(buff)+1));
			gets(buff);
		}while((int)strlen(buff) == 0);
		strcpy(userid_sent,&buff[0]);
		switch(menu_choise){
			case 1:{
				//login
				bytes_sent = send(client_sock,"100",4,0);
				if(bytes_sent == -1){
					error_send();
					close(client_sock);
					return 0;
				}
				break;
			}
			case 2:{
				//signup
				bytes_sent = send(client_sock,"101",4,0);
				if(bytes_sent == -1){
					error_send();
					close(client_sock);
					return 0;
				}
				break;
			}
		}
		bytes_received = recv(client_sock,buff,1024,0);
		if(bytes_received == -1){
			error_recv();
			close(client_sock);
			return 0;
		}
		
		// send userid
		
		bytes_sent = send(client_sock,userid_sent,strlen(userid_sent),0);
		if(bytes_sent == -1){
			error_send();
			close(client_sock);
			return 0;
		}

		bytes_received = recv(client_sock,buff,1024,0);
		if(bytes_received ==-1){

		}
		buff[bytes_received] = '\0';
		int flag =0;
		switch(menu_choise){
			case 1:{
				if(strcmp(buff,"103") == 0){
					// notmatch usedid
					printf("\nNot match userid!\n");
					flag = -1;
					
				} else{
					if(strcmp(buff,"105") == 0){
						//online
						printf("\nAccount is currently online.Pls try again later!\n");
						flag = -1;
						
					} else{
						//offline
						//send pass to login
						int retry_times =0;
						do{	
							retry_times++;
							
							printf("\nInsert passwd:");
							memset(buff,'\0',(strlen(buff)+1));
							gets(buff);
							char* passwd_sent = (char*) malloc(sizeof(char)*50);
							strcpy(passwd_sent,&buff[0]);

							char* passM = (char*) malloc(sizeof(char)*100);
							strcpy(passM,userid_sent);
							strcat(passM,"-");
							strcat(passM,passwd_sent);

							bytes_sent = send(client_sock,"107",4,0);
							if(bytes_sent == -1){

							}
							bytes_received = recv(client_sock,buff,1024,0);
							if(bytes_received == -1){

							}

							
							//send userid + pass
							bytes_sent = send(client_sock,passM,strlen(passM),0);
							if(bytes_sent == -1){
								printf("\nError!Cannot send data to sever!\n");
								close(client_sock);
								exit(-1);
							}

							bytes_received = recv(client_sock,buff,1024,0);
							if(bytes_received == -1){
								printf("\nError!Cannot receive data from sever!\n");
								close(client_sock);
								exit(-1);
							}
							buff[bytes_received] = '\0';
							if(strcmp(buff,"109") == 0){
								retry_times = 0;
								break;
							}
							printf("Wrong passwd\n");
						} while(retry_times < 5);
						if(retry_times == 5){
							printf("Error!!Retry 5 times,exit\n");
							break;
						}
						else{
							printf("login\n");
						}

					}
					
				}
				break;
			}
			case 2:{
				if(strcmp(buff,"106") ==0){
					// account already exist
					printf("\nAccount already exist!\n");
					flag = -1;
				} else{
					// send pass to create new account
					bytes_sent = send(client_sock,"110",4,0);
					if(bytes_sent == -1){

					}

					bytes_received = recv(client_sock,buff,1024,0);
					if(bytes_received == -1){

					}
					do{
						printf("\nInsert passwd:");
						memset(buff,'\0',(strlen(buff)+1));
						gets(buff);
						if(strlen(buff) <6){
							printf("Passwd length must greater than 6\n");
						}
					} while (strlen(buff) < 6);
					char* passwd_sent = (char*) malloc(sizeof(char)*50);
					strcpy(passwd_sent,&buff[0]);

					char* passM = (char*) malloc(sizeof(char)*100);
					strcpy(passM,userid_sent);
					strcat(passM,"-");
					strcat(passM,passwd_sent);
					//send userid + pass
					bytes_sent = send(client_sock,passM,strlen(passM),0);
					if(bytes_sent == -1){
						printf("\nError!Cannot send data to sever!\n");
						close(client_sock);
						exit(-1);
					}
					bytes_received = recv(client_sock,buff,1024,0);
				}
				break;
			}
		}
		if(flag == -1){
			continue;
		}
	}
	printf("Bye!\n");
	close(client_sock);
	return 0;
}

void menu_login(int* i){
	printf("\n**********Login Menu**********\n\t1.Login\n\t2.Signup\n\t3.Exit");
	printf("\n\n");
	scanf("%d",i);
}

void error_send(){
	printf("\nError!!Cannot send data to server!\n");
}
void error_recv(){
	printf("\nError!!Cannot recv data from server!\n");
}