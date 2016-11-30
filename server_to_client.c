#include "server_to_client.h"
#include "account.c"
#include "account.h"


void Excute_Request(int server_sock,char* request_code){
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
			Send_UserName_Respond(server_sock,code,param1);
			break;
		}
		case 102:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			Send_Passwd_Respond(server_sock,code,param1,param2);
			break;
		}
		case 201:{
			param1 = strtok(NULL,"//");
			Send_UserName_Respond(server_sock,code,param1);
			break;
		}
		case 202:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			Send_Passwd_Respond(server_sock,code,param1,param2);
			break;
		}
		case 301:{
			param1 = strtok(NULL,"//");
			Send_UserName_Respond(server_sock,code,param1);
			break;
		}
		case 401:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			Find_Item_info(param2);
			//TODO send back item info
			break;
		}
		case 501:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			int x = Find_Item_in_Favorite_list(param1,param2);
			//TODO
			if (x == 0){
				// not found
				Send_Message(server_sock,"551");
				Add_Item_To_Favorite_list(param1,param2);
			} else{
				// found
				Send_Message(server_sock,"550");
			}
			break;
		}
		case 502:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			int x = Find_Item_in_Favorite_list(param1,param2);
			if(x == 0){
				// not found
				Send_Message(server_sock,"552");
			} else{
				//found
				Remove_Item_From_Favorite_list(param1,param2);
				Send_Message(server_sock,"553");
			}
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
void Send_UserName_Respond(int server_sock,char* request_code,char* user_name){
	int bytes_sent,bytes_received;
	char buff[1024];
	
	int i = atoi(request_code);

	//find username
	
	int result = Find_UserName(username);
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
					Send_Message(server_sock,"151");
					break;
				}
				case 201:{
					Send_Message(server_sock,"250");
					break;
				}
				case 301:{
					Set_status(user_name,0);	//set acc status = 1 thanh status = 0
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

void Send_Passwd_Respond(int server_sock, char* request_code, char* user_name,char* passwd){
	int bytes_sent,bytes_received;
	char buff[1024];


	int i = atoi(request_code);
	switch(i){
		case 102:{

			if(strcmp(_passwd,passwd) == 0){
				//match passwd
				char* _passwd = (char*)malloc(sizeof(char)*50);
				_passwd = Get_Passwd(user_name);
				Send_Message(server_sock,"154");
				Set_status(user_name,1);	//set status 0 -> 1
			} else{
				// not match passwd
				Send_Message(server_sock,"153");
			}
			break;
		}
		case 202:{
			Create_new_acc(username,passwd);
			Send_Message(server_sock,"252");
			break;
		}
	}
	
	
}



