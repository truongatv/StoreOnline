#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include "server.h"

/*
100-login;
101-signup;
102-logout;
999-exit;
888-ready;
103-notmatch userid
104-acc is offline
105-acc is online
106-account already exist
107-send passwd
108-not match pass
109-match pass authenticated
110-send passM to create new acc
111-retry over 5 times
*/



int main(){
	if(Get_Data() == -1){
 		printf("Error!Cannot get data!\n");
 		exit(-1);
 	}
	int listenfd,conn_sock; /* file descriptors */
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	

	if ((listenfd=socket(PF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listenfd,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}     

	if(listen(listenfd,BACKLOG) == -1){  /* calls listen() */
		printf("listen() error\n");
		exit(-1);
	}
	int bytes_sent, bytes_received;
	char recv_data[1024];
	int sin_size;
	fd_set readfds;
	fd_set sockfds;
	fd_set writefds;

	int clients[FD_SETSIZE];
	int i;
	int maxfd = listenfd;

	for( i =0; i <FD_SETSIZE;i++){
		clients[i] = -1;
	}
	FD_ZERO(&readfds);
	FD_ZERO(&sockfds);

	FD_SET(listenfd,&sockfds);

	int nEvents;
	sin_size = sizeof(struct sockaddr_in);
	while(1){
		readfds = sockfds;
		nEvents = select(maxfd+1, &readfds,NULL,NULL,NULL);
		if(nEvents < 0){
			printf("Error events < 0\n");
			exit(0);
		}
		if(FD_ISSET(listenfd,&readfds) != 0){
			conn_sock = accept(listenfd,(struct sockaddr*)&client,&sin_size);
			for(i =0;i <FD_SETSIZE; i++){
				if(clients[i] == -1)
					break;
			}
			if( i == FD_SETSIZE){
				printf("Max connection reached!\n");
				continue;
			} else{
				clients[i] = conn_sock;
				if(conn_sock > maxfd){
					maxfd = conn_sock;
				}
				FD_SET(conn_sock,&sockfds);
			}
			nEvents--;
		}
		
		for(i = 0;i<FD_SETSIZE; i++){
		
			if(FD_ISSET(clients[i],&readfds) !=0){
				bytes_received = recv(clients[i], recv_data,1024,0);
				if(bytes_received == -1){
					error_recving();
					close(clients[i]);
					FD_CLR(clients[i],&sockfds);
					clients[i] = -1;
				}

				recv_data[bytes_received] = '\0';
				if(strcmp(recv_data,"999") == 0){
					printf("Close clients %d.\n",clients[i]);
					close(clients[i]);
					FD_CLR(clients[i],&sockfds);
				} else{
					if(strcmp(recv_data,"100") == 0 ){
						//login 

						recv_login_request(clients[i]);
						
					} else{
						if(strcmp(recv_data,"101") == 0){

							recv_signup_request(clients[i]);

						} else{
							if(strcmp(recv_data,"107") == 0){

								recv_passM(clients[i],1);

							} else{
								if(strcmp(recv_data,"110") == 0){

									recv_passM(clients[i],2);

								} else{
									if(strcmp(recv_data,"111") == 0){

										printf("Close clients %d.\n",clients[i]);
										close(clients[i]);
										FD_CLR(clients[i],&sockfds);

									} else{
										if(strcmp("102",recv_data) == 0){
											recv_logout_request(clients[i]);
										} 
									}
								}
							}
						}

					}
				}
				
				// close(clients[i]);
				// FD_CLR(clients[i],&sockfds);
				// clients[i] = -1;
			}
		}

	}
	close(listenfd);
	return 1;
}

void Insert_ToLast(char* userid,char* passwd,char *status){
	struct account *newNode;
	newNode = (struct account*)malloc(sizeof(struct account));
	newNode->userid = (char*)malloc(sizeof(char));
	newNode->passwd = (char*)malloc(sizeof(char));
	newNode->status = (char*)malloc(sizeof(char));

	strcpy(newNode->userid,userid);
	strcpy(newNode->passwd,passwd);
	strcpy(newNode->status,status);
	last->next = newNode;
	last = newNode;
}

void Insert_ToFirst(char* userid,char* passwd,char*status){
	first = (struct account*)malloc(sizeof(struct account*));
	last = (struct account*) malloc(sizeof(struct account*));
	first->userid = (char*)malloc(sizeof(char));
	first->passwd = (char*)malloc(sizeof(char));
	first->status = (char*)malloc(sizeof(char));

	strcpy(first->userid,userid);
	strcpy(first->passwd,passwd);
	strcpy(first->status,status);

	first->next = NULL;
	
	last = first;
}

char* Search(char* userid_received){
	struct account* tempNode;
	tempNode = (struct account*) malloc(sizeof(struct account));
	tempNode = first;
	do{
		if(strcmp(tempNode->userid,userid_received) == 0){
			return tempNode->passwd;
		}
		tempNode = tempNode->next;
	} while(tempNode != NULL);
	return " ";
}
void Set_Status(char* userid_received,char* status){
	struct account* tempNode;
	tempNode = (struct account*)malloc(sizeof(struct account));
	tempNode = first;
	do{
		if(strcmp(tempNode->userid,userid_received) == 0){
			strcpy(tempNode->status,status);
			return;
		}
		tempNode = tempNode ->next;
	} while(tempNode!=NULL);
}
char* Get_Status(char* userid_received){
	struct account* tempNode;
	tempNode = (struct account*)malloc(sizeof(struct account));
	tempNode = first;
	do{
		if(strcmp(tempNode->userid,userid_received) == 0){
			return tempNode->status;
		}
		tempNode = tempNode->next;
	} while(tempNode!=NULL);
	return "-1";
}
int Get_Data(){
	FILE *f;
	f = fopen("./Data/account_info.txt","r");
	if(f == NULL){
		printf("Cannot open file.\n");
		return -1;
	}
	char* buff;
	char* userid;
	char* passwd;
	char* status;

	userid = (char*) malloc(sizeof(char)*50);
	passwd = (char*)malloc(sizeof(char)*50);
	status = (char*)malloc(sizeof(char)*2);
	buff = (char*) malloc(sizeof(char)*1024);
	fgets(buff,1024,f);
	fgets(buff,1024,f);

	if(buff[strlen(buff)-1] == '\n'){
		buff[strlen(buff)-1] = '\0';
	}
	userid = strtok(buff," ");
	passwd = strtok(NULL," ");
	strcpy(status,"0");
	Insert_ToFirst(userid,passwd,status);

	while(!feof(f)){
		fgets(buff,1024,f);
		if(buff[strlen(buff)-1] == '\n'){
			buff[strlen(buff)-1] = '\0';
		}
		userid = strtok(buff," ");
		passwd = strtok(NULL, " ");
		strcpy(status,"0");
		Insert_ToLast(userid,passwd,status);	
	}
	return 1;
}
void error_sending(){
	printf("\nError! Cannot send data to client\n");
}
void error_recving(){
	printf("\nError! Cannot recv data from client\n");
}
void recv_passM(int client,int type){
	int bytes_sent,bytes_received;
	char recv_data[1024];
	bytes_sent = send(client,"888",4,0);
	if(bytes_sent == -1){

	}
	bytes_received = recv(client,recv_data,1024,0);
	if(bytes_received == -1){

	}
	recv_data[bytes_received] = '\0';
	char* passM = (char*)malloc(sizeof(char)*100);
	char* userid_received = (char*) malloc(sizeof(char)*50);
	char* passwd_received = (char*) malloc(sizeof(char)*50);
	strcpy(passM,recv_data);
	userid_received = strtok(passM,"-");
	passwd_received = strtok(NULL,"-");
	switch(type){
		case 1:{
			if(strcmp(Search(userid_received),passwd_received) == 0){
				//match passwd
				Set_Status(userid_received,"1");
				printf("acount %s connected.\n",userid_received);
				
				bytes_sent = send(client,"109",4,0);
				if(bytes_sent == -1){

				}

			} else{
				//not match passwd
				bytes_sent=send(client,"108",4,0);
				if(bytes_sent == -1){
					
				}
			}
			break;
		}
		case 2:{
			Insert_ToLast(userid_received,passwd_received,"0");
			FILE *f;
			char* buff = (char*)malloc(sizeof(char)*1024);
			f = fopen("./Data/account_info.txt","a");
			if(f == NULL){
				printf("Cannot open file.\n");
				return;
			}
			// while(!feof(f)){
			// 	fgets(buff,1024,f);
			// }
			fprintf(f, "\n%s", userid_received);
			fprintf(f, " %s",passwd_received );
			fclose(f);
			bytes_sent = send(client,"888",4,0);
			if(bytes_sent == -1){

			}
			break;
		}
	}
	
}
void recv_logout_request(int client){
	int bytes_sent,bytes_received;
	char recv_data[1024];

	bytes_sent = send(client,"888",4,0);
	if(bytes_sent == -1){

	}
	bytes_received = recv(client,recv_data,1024,0);
	if(bytes_received == -1){

	}
	recv_data[bytes_received] = '\0';
	char* userid_received = (char*)malloc(sizeof(char)*50);
	strcpy(userid_received,recv_data);

	Set_Status(userid_received,"0");

}
void recv_login_request(int client){
	int bytes_sent,bytes_received;
	char recv_data[1024];
	bytes_sent = send(client,"888",4,0);
	if(bytes_sent == -1){
		// error_sending();
		// close(*client);
		// FD_CLR(client,&sockfds);
		// clients[i] = -1;
	}
	bytes_received = recv(client,recv_data,1024,0);
	if(bytes_received == -1){
		// error_recving();
		// close(clients[i]);
		// FD_CLR(clients[i],&sockfds);
		// clients[i] =-1;
	}
	recv_data[bytes_received] = '\0';
	char* userid_received = (char*)malloc(sizeof(char)*50);
	strcpy(userid_received,&recv_data[0]);
	char* status = (char*)malloc(sizeof(char)*2);
	strcpy(status,Get_Status(userid_received));
	if(strcmp(status,"-1") == 0){
		// not match userid
		bytes_sent = send(client,"103",4,0);
		if(bytes_sent == -1){

		}
	} else{
		//match
		if(strcmp(status,"0") == 0){
			// offline
			bytes_sent = send(client,"104",4,0);
			if(bytes_sent == -1){

			}

		} else{
			//online
			bytes_sent = send(client,"105",4,0);
			if(bytes_sent == -1){

			}
			
		}
	}
}

void recv_signup_request(int client){
	//signup
	int bytes_received,bytes_sent;
	char recv_data[1024];
	bytes_sent = send(client,"888",4,0);
	// if(bytes_sent == -1){
	// 	error_sending();
	// 	close(client);
	// 	FD_CLR(clients[i],&sockfds);
	// 	clients[i] = -1;
	//}
	bytes_received = recv(client,recv_data,1024,0);
	if(bytes_received == -1){
		// error_recving();
		// close(clients[i]);
		// FD_CLR(clients[i],&sockfds);
		// clients[i] =-1;
	}
	recv_data[bytes_received] = '\0';
	recv_data[bytes_received] = '\0';
	char* userid_received = (char*)malloc(sizeof(char)*50);
	strcpy(userid_received,&recv_data[0]);
	char* status = (char*)malloc(sizeof(char)*2);
	strcpy(status,Get_Status(userid_received));
	if(strcmp(status,"-1") == 0){
		// not match userid
		bytes_sent = send(client,"103",4,0);
		if(bytes_sent == -1){

		}
	} else{
		// account already exist
		bytes_sent = send(client,"106",4,0);
		if(bytes_sent == -1){

		}
	}
}