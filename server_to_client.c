#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>

int retry_times = 0;
char* temp;
void Excute_Request(int server_sock,char* request_code,MYSQL*con){
	int bytes_received,bytes_sent;
	char buff[1024];

	char* code = (char*)malloc(sizeof(char)*10);
	char* param1 = (char*)malloc(sizeof(char)*50);
	char* param2 = (char*)malloc(sizeof(char)*100);
	char* param3 = (char*)malloc(sizeof(char)*20);
	
	code = strtok(request_code,"//");
	int i;
	i = atoi(code);
	switch(i){
		case 101:{
			param1 = strtok(NULL,"//");
			Send_UserName_Respond(server_sock,code,param1,con);
			break;
		}
		case 102:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			Send_Passwd_Respond(server_sock,code,param1,param2,con);
			break;
		}
		case 201:{
			param1 = strtok(NULL,"//");
			Send_UserName_Respond(server_sock,code,param1,con);
			break;
		}
		case 202:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			Send_Passwd_Respond(server_sock,code,param1,param2,con);
			break;
		}
		case 301:{
			param1 = strtok(NULL,"//");
			Send_UserName_Respond(server_sock,code,param1,con);
			break;
		}
		case 401:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			//Find_Item_info(param2);
			//TODO send back item info
			temp = (char*)malloc(sizeof(char)*1024);
			strcpy(temp,search_item(param2,con));
			if(strlen(temp) == 0){
				Send_Message(server_sock,"451");
			} else{
				Send_Message(server_sock,"450");
			}
			break;
		}
		case 501:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			// int x = Find_Item_in_Favorite_list(param1,param2);
			// //TODO
			// if (x == 0){
			// 	// not found
			// 	Send_Message(server_sock,"551");
			// 	Add_Item_To_Favorite_list(param1,param2);
			// } else{
			// 	// found
			// 	Send_Message(server_sock,"550");
			// }
			break;
		}
		case 502:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			// int x = Find_Item_in_Favorite_list(param1,param2);
			// if(x == 0){
			// 	// not found
			// 	Send_Message(server_sock,"552");
			// } else{
			// 	//found
			// 	Remove_Item_From_Favorite_list(param1,param2);
			// 	Send_Message(server_sock,"553");
			// }
			break;
		}
		case 503:{
			param1 = strtok(NULL,"//");
			//TODO get favorite list from username and send back
			break;
		}
		case 601:{

			break;
		}
		case 602:{
			break;
		}
		case 603:{
			break;
		}
		case 604:{
			break;
		}
	}

}
void Send_Message(int server_sock,char* request_code){

	int i = atoi(request_code);
	int bytes_sent,bytes_received;
	char* request = (char*) malloc(sizeof(char)*1024);
	strcpy(request,request_code);
	strcat(request,"//");
	switch(i){
		case 150:{
			strcat(request,"msg_not_match_user_name");
			break;
		}
		case 151:{
			strcat(request,"msg_acc_currently_online");
			break;
		}
		case 152:{
			strcat(request,"msg_acc_currently_offline");
			break;
		}
		case 153:{
			strcat(request,"msg_not_match_passwd");
			break;
		}
		case 154:{
			strcat(request,"msg_match_username_passwd");
			break;
		}
		case 155:{
			strcat(request,"msg_retry_over_5_times");
			break;
		}
		case 250:{
			strcat(request,"msg_username_has_been_used");
			break;
		}
		case 251:{
			strcat(request,"msg_username_can_be_used");
			break;
		}
		case 252:{
			strcat(request,"msg_created_new_acc");
			break;
		}
		case 351:{
			strcat(request,"msg_logout");
			break;
		}
		case 450:{
			strcat(request,"msg_found_item");
			strcat(request,"//");
			strcat(request,temp);
			break;
		}
		case 451:{
			strcat(request,"msg_not_found_item");
			break;
		}
		case 550:{
			strcat(request,"msg_favorite_list_already_has_item");
			break;
		}
		case 551:{
			strcat(request,"msg_success_add_item_to_favorite_list");
			break;
		}
		case 552:{
			strcat(request,"msg_error_when_remove_item_from_favorite_list");
			break;
		}
		case 553:{
			strcat(request,"msg_success_remove_item_from_cart_list");
			break;
		}
		case 650:{
			strcat(request,"msg_success_add_item_to_cart");
			break;
		}
		case 651:{
			strcat(request,"msg_success_remove_item_from_cart_list");
			break;
		}
		case 652:{
			strcat(request,"msg_error_when_remove_item_from_cart_list");
			break;
		}
	}
	printf("%s\n",request );
	bytes_sent = send(server_sock,request,strlen(request),0);
	if(bytes_sent < 0){

	}
}
// void Get_Message(int server_sock){
// 	char* request = (char*)malloc(sizeof(char)*1024);
// 	bytes_received = recv(server_sock,buff,1024,0);
// 	if(bytes_received < 0){
// 		//error
// 	}
// 	buff[bytes_received] = '\0';
// 	strcpy(request,&buff[0]);
// 	char* request_code = (char*)malloc(sizeof(char)*5);
// 	request_code = strtok(request,"//");
// 	user_name = strtok(NULL,"//");

// }
void Send_UserName_Respond(int server_sock,char* request_code,char* user_name,MYSQL* con){
	int bytes_sent,bytes_received;
	char buff[1024];
	
	int i = atoi(request_code);

	//find username
	int result = check_exits_user_name(user_name,con);
	printf("%d\n",result );
	if(result == -1){
		// not found user name
		switch(i){
			case 101:{
				Send_Message(server_sock,"150");
				break;
			}	
			case 201:{
				Send_Message(server_sock,"251");
				break;
			}
		}
	} else{
		//found user name
		if(result == 1){
			//online
			switch(i){
				case 101:{
					result = check_status_account(user_name,con);
					if( result == 1){
						Send_Message(server_sock,"151");
					} else{
						Send_Message(server_sock,"152");
					}
					break;
				}
				case 201:{
					Send_Message(server_sock,"250");
					break;
				}
				case 301:{
					//Set_status(user_name,con,0);	//set acc status = 1 thanh status = 0
					update_status(user_name,0,con);
					Send_Message(server_sock,"351");
					break;
				}
				case 603:{
					break;
				}
				case 604:{
					break;
				}
			}
		} else{
			//offline
			switch(i){
				case 101:{
					Send_Message(server_sock,"152");
					break;
				}
				case 201:{
					Send_Message(server_sock,"250");
					break;
				}
			}
		}
	}
}

void Send_Passwd_Respond(int server_sock, char* request_code, char* user_name,char* passwd,MYSQL*con){
	int bytes_sent,bytes_received;
	char buff[1024];
	int i = atoi(request_code);
	int result = check_password_from_user_name(user_name,passwd,con);
	switch(i){
		case 102:{
		
			if(result == 1){
				//match passwd
				Send_Message(server_sock,"154");
				update_status(user_name,1,con);
			} else{
				// not match passwd
				retry_times ++;
				if(retry_times >= 5){
					Send_Message(server_sock,"155");
				} else{
					Send_Message(server_sock,"153");
				}
			}
			break;
		}
		case 202:{
			create_account(user_name,passwd,con);
			Send_Message(server_sock,"252");
			update_status(user_name,1,con);
			break;
		}
	}
	
	
}



