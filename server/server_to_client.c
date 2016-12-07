#include "server_to_client.h"

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
			//TODO send back item info
			temp = (char*)malloc(sizeof(char)*1024);
			strcpy(temp,search_item_contain_keyword(param2,con));
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
			int x = search_item(param2,con);
			if(x == -1){
				// wrong item name
				Send_Message(server_sock,"555");
			} else{
				// item name is true
				x = check_item_in_favorite_list(param1,param2,con);
				if(x == -1){
					// 
					insert_favorite(param1,param2,con);
					Send_Message(server_sock,"551");
				} else{
					// favorite list already has item
					Send_Message(server_sock,"550");
					break;
				}

			}
			break;
		}
		case 502:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");

			int x = search_item(param2,con);
			if(x == -1){
				// wrong item name
				Send_Message(server_sock,"555");
			} else{
				// item name is true
				x = check_item_in_favorite_list(param1,param2,con);
				if(x == -1){
					// 
					Send_Message(server_sock,"552");
				} else{
					// favorite list already has item
					delete_favorite(param1,param2,con);
					Send_Message(server_sock,"553");
					break;
				}

			}
			break;
		}
		case 503:{
			param1 = strtok(NULL,"//");
			//TODO get favorite list from username and send back
			
			temp = (char*)malloc(sizeof(char)*1024);
			strcpy(temp,show_all_favorite(param1,con));
			Send_Message(server_sock,"554");
			break;
		}
		case 601:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			param3 = strtok(NULL,"//");
			int x = search_item(param2,con);
			if (x == -1){
				Send_Message(server_sock,"555");
			} else{
				x = check_item_in_cart_list(param1,param2,con);
				if (x == -1){
					insert_cart(param1,param2,atoi(param3),con);
					Send_Message(server_sock,"650");

				} else{
					x = check_item_number_in_cart_list(param1,param2,con);
					x += atoi(param3);
					update_item_number_in_cart_list(param1,param2,x,con);
					Send_Message(server_sock,"650");
				}
			}
			break;
		}
		case 602:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			param3 = strtok(NULL,"//");
			int x = search_item(param2,con);
			if (x == -1){
				Send_Message(server_sock,"555");
			} else{
				x = check_item_in_cart_list(param1,param2,con);
				if (x == -1){
					Send_Message(server_sock,"652");
				} else{
					x = check_item_number_in_cart_list(param1,param2,con);
					if (x < atoi(param3)){
						Send_Message(server_sock,"652");
					} else{
						if(x == atoi(param3)){
							delete_item_from_cart(param1,param2,con);
							Send_Message(server_sock,"651");

						}else{
							x -= atoi(param3);
							update_item_number_in_cart_list(param1,param2,x,con);
							Send_Message(server_sock,"651");
						}
					}
					
				}
			}
			break;
		}
		case 603:{
			param1 = strtok(NULL,"//");
			temp = (char*)malloc(sizeof(char)*1024);
			strcpy(temp,show_list_cart(param1,con));
			Send_Message(server_sock,"653");
			break;
		}
		case 604:{
			param1 = strtok(NULL,"//");
			sprintf(temp, "%d", get_total_cost(param1,con));
			Send_Message(server_sock,"654");			
			break;
		}
		case 701:{
			param1 = strtok(NULL,"//");
			temp = (char*)malloc(sizeof(char)*1024);
			strcpy(temp,get_account_info(param1,con));
			Send_Message(server_sock,"750");
			break;
		}
		case 702:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			update_account_info(param1,"full_name",param2,con);
			Send_Message(server_sock,"751");
			break;
		}
		case 703:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			update_account_info(param1,"email",param2,con);
			Send_Message(server_sock,"751");
			break;
		}
		case 704:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			update_account_info(param1,"address",param2,con);
			Send_Message(server_sock,"751");
			break;
		}
		case 705:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			update_account_info(param1,"sdt",param2,con);
			Send_Message(server_sock,"751");
			break;
		}
		case 706:{
			param1 = strtok(NULL,"//");
			param2 = strtok(NULL,"//");
			int x = check_password_from_user_name(param1,param2,con);
			if(x == 1){
				// duplicate passswd
				Send_Message(server_sock,"752");
			} else{
				update_account_password(param1,param2,con);
				Send_Message(server_sock,"751");
			}
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
		case 554:{
			strcat(request,temp);
			break;
		}
		case 555:{
			strcat(request,"msg_wrong_item_name");
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
		case 653:{
			strcat(request,temp);
			break;
		}
		case 654:{
			strcat(request,temp);
			break;
		}
		case 750:{
			strcat(request,temp);
			break;
		}
		case 751:{
			strcat(request,"msg_success");
			break;
		}
		case 752:{
			strcat(request,"msg_duplicate_with_old_info");
			break;
		}
	}
	printf("Send: %s\n",request );
	bytes_sent = send(server_sock,request,strlen(request),0);
	if(bytes_sent < 0){

	}
}

void Send_UserName_Respond(int server_sock,char* request_code,char* user_name,MYSQL* con){
	int bytes_sent,bytes_received;
	char buff[1024];
	
	int i = atoi(request_code);

	//find username
	int result = check_exits_user_name(user_name,con);

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



