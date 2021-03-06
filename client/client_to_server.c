#include "client_to_server.h"

char* user_name_sent;
char* tmp;
char* array[] ={
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL
};

void Send_Request(int client_sock,char* request_code,char* result_code){

	int int_request_code;
	int_request_code = atoi(request_code);

	char* username = (char*)malloc(sizeof(char)*50);
	char* passwd = (char*)malloc(sizeof(char)*50);

	switch(int_request_code){
		case 101:{
			// send user name to login
			Send_UserName(client_sock,request_code,result_code);
			break;
		}
		case 102:{
			// send passwd to login
			Send_Passwd(client_sock,request_code,passwd,result_code);
			break;
		}
		case 201:{
			// send user name to signup
			Send_UserName(client_sock,request_code,result_code);
			break;
		}
		case 202:{
			// send passwd to create new account
			Send_Passwd(client_sock,request_code,passwd,result_code);
			break;
		}
		case 301:{
			// send username to logout
			Send_State(client_sock,request_code,result_code);
			break;
		}
		case 401:{
			//send user name + item to search item
			Send_Item(client_sock,request_code,result_code);
			break;
		}
		case 501:{
			// send user name + item to add to favorite list
			Send_Item(client_sock,request_code,result_code);
			break;
		}
		case 502:{
			// send user name + item to remove from favorite list
			Send_Item(client_sock,request_code,result_code);
			break;
		}
		case 503:{
			// send user name to get all item from favorite list
			Send_State(client_sock,request_code,result_code);
			break;
		}
		case 601:{
			// send user name + item + number to add to cart list
			Send_Item(client_sock,request_code,result_code);
			break;
		}
		case 602:{
			// send user name + item + number to remove from cart list
			Send_Item(client_sock,request_code,result_code);
			break;
		}
		case 603:{
			// send user name to get all item from cart list
			Send_State(client_sock,request_code,result_code);
			break;
		}
		case 604:{
			// send user name to get total cost
			Send_State(client_sock,request_code,result_code);
			break;
		}
		case 701:{
			Send_State(client_sock,request_code,result_code);
			break;
		}
		case 702:{
			Send_Info(client_sock,"full name",request_code,passwd,result_code);
			break;
		}
		case 703:{
			Send_Info(client_sock,"email",request_code,passwd,result_code);
			break;
		}
		case 704:{
			Send_Info(client_sock,"address",request_code,passwd,result_code);
			break;
		}
		case 705:{
			Send_Info(client_sock,"phone number",request_code,passwd,result_code);
			break;
		}
		case 706:{
			Send_Info(client_sock,"new password",request_code,passwd,result_code);
			break;
		}
	}
}
void Show_Message(char* respond,char* result){
	char* result_code = (char*)malloc(sizeof(char)*10);
	char* msg = (char*)malloc(sizeof(char)*100);
	char* params = (char*)malloc(sizeof(char)*800);

	result_code = strtok(respond,"//");

	int i = atoi(result_code);
	switch(i){
		case 150:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"0");
			break;
		}
		case 151:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"0");
			break;
		}
		case 152:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"1");
			break;
		}
		case 153:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg );
			strcpy(result,"3");
			break;
		}
		case 154:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"2");
			break;
		}
		case 155:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg );
			strcpy(result,"4");
			break;
		}
		case 250:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"0");
			break;
		}
		case 251:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"1");
			break;
		}
		case 252:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"2");
			break;
		}
		case 351:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			strcpy(result,"4");
			break;
		}
		case 451:{

		}
		case 550:{

		}
		case 551:{

		}
		case 552:{

		}
		case 553:{

		}
		case 555:{

		}
		case 650:{

		}
		case 651:{

		}
		case 556:{
			
		}
		case 655:{

		}
		case 652:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			break;
		}
		case 450:{
			msg = strtok(NULL,"//");
			printf("%s\n",msg);
			params = strtok(NULL,"//");
			printf("%s\n", params);
			tmp = (char*)malloc(sizeof(char)*1024);
			strcpy(tmp,params);
			set_completion_array(tmp);
			int i;
			// for(i=0;i<30;i++){
			// 	if(array[i] != NULL){
			// 		printf("\'%s\'\n", array[i]);
			// 	}
			// }
			break;
		}
		case 653:{
			params = strtok(NULL,"//");
			printf("%s\n", params);
			break;
		}
		case 654:{
			msg = strtok(NULL,"//");
			//params = strtok(NULL,"//");
			printf("%s\n", msg);
			//printf("%s\n", params);
			break;
		}
		case 554:{
			params = strtok(NULL,"//");
			printf("%s\n", params);
			break;
		}
		case 750:{
			params = strtok(NULL,"//");
			printf("%s\n",params );
			break;
		}
		case 751:{
			params = strtok(NULL,"//");
			printf("%s\n", params);
			break;
		}
		case 752:{
			params = strtok(NULL,"//");
			printf("%s\n", params);
			break;
		}
	}
}
// request_code == 101 || 201 || 301 || 603 || 604
void Send_UserName(int client_sock,char*request_code,char* result_code){
	char buff[1024];
	do{
		printf("\nInsert userid:");
		memset(buff,'\0',(strlen(buff)+1));
		gets(buff);
	}while((int)strlen(buff) <=5 || (int)strlen(buff)>20);

	user_name_sent = (char*)malloc(sizeof(char)*50);
	strcpy(user_name_sent,&buff[0]);
	Send_State(client_sock,request_code,result_code);

}

void Send_State(int client_sock,char* request_code,char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];
	char *request = (char*)malloc(sizeof(char)*1024);

	strcpy(request,request_code);
	strcat(request,"//");
	strcat(request,user_name_sent);

	//send request_code//username
	bytes_sent = send(client_sock,request,strlen(request),0);
	if(bytes_sent < 0){
		//error
		printf("Error!!Can't send data to server!\n");
		close(client_sock);
		return;
	}
	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
		printf("Error!!Can't recv data from server!\n");
		close(client_sock);
		return;
	}
	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);
}
//request_code == 102 || 202
void Send_Passwd(int client_sock,char* request_code,char* passwd,char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];

	do{
		printf("\nInsert passwd:");
		memset(buff,'\0',(strlen(buff)+1));
		gets(buff);

	}while((int)strlen(buff) <=5  || strlen(buff)>10 || strstr(buff," ")!=NULL);



	strcpy(passwd,&buff[0]);

	char* PassM = (char*)malloc(sizeof(char)*1024);
	
	strcpy(PassM,request_code);
	strcat(PassM,"//");
	strcat(PassM,user_name_sent);
	strcat(PassM,"//");
	strcat(PassM,passwd);

	//send request_code//username//passwd
	
	bytes_sent = send(client_sock,PassM,strlen(PassM),0);
	if(bytes_sent < 0){
		//error
		printf("Error!!Can't send data to server!\n");
		close(client_sock);
		return;
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
		printf("Error!!Can't recv data from server!\n");
		close(client_sock);
		return;
	}
	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);
}

void Send_Info(int client_sock,char* info_type,char* request_code,char* info,char* result_code){
	int bytes_sent,bytes_received;
	char buff[1024];

	loop: do{
		printf("\nInsert %s:",info_type);
		memset(buff,'\0',(strlen(buff)+1));
		gets(buff);

		if(!strcmp("email",info_type)){
			if(strstr(buff," ")!=NULL || strstr(buff,"@")==NULL||strlen(buff)<=5){
				goto loop;
			}
		}
		if(!strcmp("phone number",info_type)){
			if(strspn(buff,"0123456789") != strlen(buff))
				goto loop;
		}
		if(!strcmp("new password",info_type)){
			if((int)strlen(buff) <=5  || strlen(buff)>10 || strstr(buff," ")!=NULL)
				goto loop;
		}
	}while((int)strlen(buff) == 0);


	strcpy(info,&buff[0]);

	char* PassM = (char*)malloc(sizeof(char)*1024);
	
	strcpy(PassM,request_code);
	strcat(PassM,"//");
	strcat(PassM,user_name_sent);
	strcat(PassM,"//");
	strcat(PassM,info);

	//send request_code//username//info
	
	bytes_sent = send(client_sock,PassM,strlen(PassM),0);
	if(bytes_sent < 0){
		//error
		printf("Error!!Can't send data to server!\n");
		close(client_sock);
		return;
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
		printf("Error!!Can't recv data from server!\n");
		close(client_sock);
		return;
	}
	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);
}

// request_code == 401 || 501 || 601 || 602
void Send_Item(int client_sock,char* request_code,char* result_code){
	char* itemName = (char*)malloc(sizeof(char)*1024);
	int bytes_sent,bytes_received;
	char buff[1024];
	int i;
	do{
		printf("\nInsert item:");
		//memset(buff,'\0',(strlen(buff)+1));
		// gets(buff);
		itemName = readline("> ");
	}while((int)strlen(itemName) == 0);

	//strcpy(itemName,&buff[0]);

	char* request = (char*) malloc(sizeof(char)*1024);

	strcpy(request,request_code);
	strcat(request,"//");
	strcat(request,user_name_sent);
	strcat(request,"//");
	strcat(request,itemName);

	if((strcmp(request_code,"601") == 0) || (strcmp(request_code,"602") == 0)){
		
		do{
			printf("\nInsert number:");
			scanf("%d",&i);
			while(getchar()!='\n');
		}while(i<=0);
		char str[10];

  		sprintf(str, "%d", i);

		strcat(request,"//");
		strcat(request,&str[0]);

	}

	bytes_sent = send(client_sock,request,strlen(request),0);
	if(bytes_sent < 0){
		//error
		printf("Error!!Can't recv data from server!\n");
		close(client_sock);
		return;
	}

	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received < 0){
		//error
		printf("Error!!Can't recv data from server!\n");
		close(client_sock);
		return;
	}

	buff[bytes_received] = '\0';
	strcpy(result_code,&buff[0]);	
}

void set_completion_array(char* temp){
	char* str = (char*)malloc(sizeof(char)*1024);
	memmove(&temp[0], &temp[1], strlen(temp));
	int i;
	for ( i  = 0; i< 30; i++){
		array[i] = NULL;
	}
	i=1;
	
	array[0] = strtok(temp,":");
	array[0][strlen(array[0]) -1] = '\0';
	while(strtok(NULL,"\t") != NULL){
		array[i] = strtok(NULL,":");
		if(array[i] !=NULL){
			array[i][strlen(array[i]) -1] = '\0';
		}
		//array[i][strlen(array[i]) -1] = '\0';
		i++;
	}
}
char **item_name_completion(const char *text, int start, int end){
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, item_name_generator);
}

char *item_name_generator(const char *text, int state){
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = array[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}