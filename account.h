#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
struct other_info{
	char* email;	//mail
	char* full_name; // ten
	char* address; //dia chi
	char* phone_number; // sdt
};
struct other_info *other_info = NULL;
struct item
 {
 	/* data */
 	char* item_name; // ten
 	int price; //gia
 	int total; //so luong 
 }; 

 struct item *item = NULL;

 struct item_list
 {
 	/* data */
 	struct item item;  
 	struct item_list* next;
 };

struct item_list *item_list = NULL;

struct account{
	char* user_name;
	char* passwd;
	int state;
	struct other_info *other_info;
	struct item_list *cart; //gio hang
	struct item_list *favorite_list; //mat hang yeu thich
};
struct account *account = NULL;
struct account_list{
	struct account account;
	struct account_list *next;
}


#endif 

/* client
msg_type // prameters

Login
	101//username
	102//state//passwd
Signup
	201//username
	202//state//passwd
LogOut
	301//state
Search Item
	401//state//ItemName 
Favorite list
	501//state//ItemName 			-- 		add new item to favorite list
	502//state//ItemName 			--		remove from favorite list
	503//state 						-- 		show all favorite list
Cart list
	601//state//ItemName//number 	-- 		add new item to cart list with number of item
	602//state//ItemName//number 	-- 		remove number of item from cart list 
	603//state						-- 		get total cost
	604//state 						--		show cart list

	server
Login
	150//msg_not_match_user_name
	151//msg_acc_currently_online
	152//msg_acc_currently_offline
	153//msg_not_match_passwd
	154//msg_match_username_passwd
Signup
	250//msg_username_has_been_used
	251//msg_username_can_be_used
	252//msg_created_new_acc
LogOut
	351//msg_logout
Search Item
	450//msg_found_item//item_info
	451//msg_not_found_item
Favorite list
	550//msg_favorite_list_already_has_item
	551//msg_success_add_item_to_favorite_list
	552//msg_error_when_remove_item_from_favorite_list
	553//msg_success_remove_item_from_favorite_list
	554//favorite_list
Cart list
	650//msg_success_add_item_to_cart
	651//msg_success_remove_item_from_cart_list
	652//msg_error_when_remove_item_from_cart_list
	653//cart_list//total_cost
	654//cart_list
*/
struct account_list *account_list =NULL;
// link list for item
void InsertFirstItem(struct item item,struct item_list* item_list){
	struct item_list *temp = (struct item_list*)malloc(sizeof(struct item_list));
	// (temp->item).item_name = (char*)malloc(sizeof(char)*100);
	CopyItem(item,temp->item);
	temp->next = item_list;
	item_list = temp;
}
struct item_list* DeleteItem(char* name,struct item_list* item_list){
	struct item_list* current = item_list;
	struct item_list* previous = NULL;
	//if list is empty
	if(item_list == NULL ){
		return NULL;
	}
	while(strcmp((current->item.item_name),name)!=0){
		if(current->next ==NULL){
			return NULL;
		}else{
			previous = current;
			current = current->next;
		}
	}
	if(current==item_list){
		item_list = item_list->next;
	}else{
		previous->next = current->next;
	}
	return current;
}
int UpdateItem(struct item currentItem,struct item newItem,struct item_list* item_list){
	struct item_list* temp = item_list;
	while(CompareItem(currentItem,temp->item)==1 && temp !=NULL){
		temp=temp->next;
	}
	if(temp==NULL){
		return -1;
	}
	if(temp!=NULL){
		CopyItem(newItem.item_name,(temp->item).item_name);
		(temp->item).price = newItem.price;
		(temp->item).total = newItem.total;
		return 1;
	}
}
struct item SearchItem(char* item_name,struct item_list* item_list){
	struct item_list* temp = item_list;
	while(strcmp(item_name,(temp->item.item_name))!=0 && temp!=NULL){
		temp = temp->next;
	}
	if(temp == NULL)
		return NULL;
	if(temp!=NULL){
		return temp->item;
	}
}
int CompareItem(struct item item_1,struct item item_2){
	if(strcmp(item_1.item_name,item_2.item_name)==0){
		if(item_1.price == item_2.price){
			if(item_1.total == item_2.total){
				return 1;
			}else return -1;
		}else return -1;
	}else return -1;
}
void CopyItem(struct item currentItem,struct item newItem){
	newItem.item_name = (char*)malloc(sizeof(char)*100);
	strcpy(newItem.item_name,currentItem.item_name);
	newItem.price = currentItem.price;
	newItem.total = currentItem.total;
}
//linklist for account

void InsertFirstAccount(struct account account,struct account_list* account_list){
	struct account_list *temp = (struct account_list*)malloc(sizeof(struct account_list));
	CreateNodeAccount(temp->account);
	CopyAccount(account,temp->account);
	temp->next = account_list;
	account_list = temp;
}
struct account_list* DeleteAccount(char* name,struct account_list* account_list){
	struct account_list* current = account_list;
	struct account_list* previous = NULL;
	//if list is empty
	if(account_list == NULL ){
		return NULL;
	}
	while(strcmp((current->account.user_name),name)!=0){
		if(current->next ==NULL){
			return NULL;
		}else{
			previous = current;
			current = current->next;
		}
	}
	if(current==account_list){
		account_list = account_list->next;
	}else{
		previous->next = current->next;
	}
	return current;
}
// tim kiem mot account trong list account dua vao user name
struct account* SearchAccount(char* user_name,struct account_list* account_list){
	struct account_list* temp = account_list;
	while(strcmp(temp->account.user_name,user_name)!=0 && temp!=NUL){
		temp = temp->next;
	}
	if(temp ==NULL)return NULL;
	else return &(temp->account);
}
int UpdateAccount(struct account currentAccount,struct account newAccount,struct account_list* account_list){
	struct account_list* temp = account_list;
	while(CompareAccount(currentAccount,temp->account)==1 && temp !=NULL){
		temp=temp->next;
	}
	if(temp==NULL){
		return -1;
	}
	if(temp!=NULL){
		(temp->account).state = newAccount.state;
		strcpy((temp->account).user_name,newAccount.user_name);
		strcpy((temp->account).passwd,newAccount.passwd);
		temp->account.other_info = newAccount.other_info;
		temp->account.cart = newAccount.cart;
		temp->account.favorite_list=newAccount.favorite_list;
		return 1;
	}
}
int CompareAccount(struct account account_1,struct account account_2){
	if(strcmp(account_1.user_name,account_2.user_name)==0){
		return 1;
	}else return -1;
}
//copy 2 accout
void CopyAccount(struct account currentAccount,struct account newAccount){
	strcpy(newAccount.user_name,currentAccount.user_name);
	newAccount.state = currentAccount.state;
	strcpy(newAccount.passwd,currentAccount.passwd);
	strcpy(newAccount.other_info->full_name,currentAccount.other_info->full_name);
	strcpy(newAccount.other_info->email,currentAccount.other_info->email);
	strcpy(newAccount.other_info->address,currentAccount.other_info->address);
	strcpy(newAccount.other_info->phone_number,currentAccount.other_info->phone_number);
	CopyItem(currentAccount.favorite_list,newAccount.favorite_list);
	CopyItem(currentAccount.cart,newAccount.cart);
}
// malloc cho cac bien char* cua struct account
void CreateNodeAccount(struct account account){
	account.favorite_list = (struct item_list*)malloc(sizeof(struct item_list));
	account.cart = (struct item_list*)malloc(sizeof(struct item_list));
	account.favorite->item.item_name = (char*)malloc(sizeof(char)*50);
	account.cart->item.item_name = (char*)malloc(sizeof(char)*50);
	account.user_name = (char*)malloc(sizeof(char)*20);
	account.passwd = (char*)malloc(sizeof(char)*20);
	account.other_info->email = (char*)malloc(sizeof(char)*30);
	account.other_info->full_name = (char*)malloc(sizeof(char)*40);
	account.other_info->address = (char*)malloc(sizeof(char)*50);
	account.other_info->phone_number = (char*)malloc(sizeof(char)*50);
}



// add item for linklist
struct item_list* AddItem(struct item_list* item_list){
	// struct item_list* temp = item_list;
	struct item item ;
	char* price = (char*)malloc(sizeof(char)*20);
	FILE* fr;
	fr = fopen("./Data/item.txt","r")
	while(!foef(fr)){
		fscanf(fr,"%[^\t]s",&(item.item_name));
		fscanf(fr,"%[^\n]s",price);
		item.price = atoi(price);
		InsertFirstItem(item,item_list);
		// temp = temp->next;
	}
	return item_list;
}

// add info for account
struct account_list* AddInfoAccount(struct account_list* account_list){
	struct account account;
	struct account_list* temp = (struct account_list*)malloc(sizeof(struct account_list));
	CreateNodeAccount(account);
	char* total = (char*)malloc(sizeof(char)*20);
	FILE *acc = fopen("account_info.txt","r");
	if(acc == NULL){
		printf("cant open file account_info.txt\n");
		return NULL;
	}
	while(!feof(acc)){
		fscanf(acc,"%[\n]s",temp->account.user_name);
		CopyAccount(ReadInfoAccount(user_name),temp->account);
		InsertFirstAccount(temp->account,account_list);
	}
	fclose(acc);
	return account_list;
}



struct account ReadInfoAccount(char* user_name){
	struct account account;
	CreateNodeAccount(account);
	struct item_list* item_list = (struct item_list*)malloc(sizeof(struct item_list));
	item_list->item.item_name = (char*)malloc(sizeof(char)*50);

	struct other_info other_info;
	other_info.email = (char*)malloc(sizeof(char)*30);
	other_info.full_name = (char*)malloc(sizeof(char)*40);
	other_info.address = (char*)malloc(sizeof(char)*50);
	other_info.phone_number = (char*)malloc(sizeof(char)*50);


	FILE *fr;
	char* total = (char*)malloc(sizeof(char)*10);
	
	//add user_name
	strcpy(account.user_name,user_name);
	//add pass
	fr = fopen(GetFilename(user_name,4),"r");
	if(fr==NULL){
		printf("cant open file pass.txt\n");
	}
	fscanf(fr,"%s",account.passwd);
	fclose(fr);
	//add favorite
	fr = fopen(GetFilename(user_name,2),"r");
	if(fr ==NULL){
		printf("cant open file favorite.txt\n");
	}
	while(!feof(fr)){
		fscanf(fr,"%[\t]",item_list->item.name);
		InsertFirstItem(item_list->item,account.favorite_list);
	}
	fclose(fr);
	//add cart
	fr= fopen(GetFilename(user_name,1),"r");
	if(fr ==NULL){
		printf("cant open file cart.txt\n");
	}
	while(!feof(fr)){
		fscanf(fr,"%[\t]s",item_list->item.item_name);
		fscanf(fr,"%[\n]s",total);
		item_list->item.total = atoi(total);
		InsertFirstItem(item_list.item,account.cart);
	}
	fclose(fr);
	//add info
	fr = fopen(GetFilename(user_name,3),"r");
	if(fr==NULL){
		printf("cant open file info.txt\n");
	}
		//read other info
	fscanf(fr,"%[\n]s",other_info.full_name);
	fscanf(fr,"%[^\n]s",other_info.address);
	fscanf(fr,"%[^\n]s",other_info.email);
	fscanf(fr,"%[^\n]s",other_info.phone_number);
	account.other_info = &(other_info);
	return account;
}
char* GetFilename(char* user_name,int type){
	char *path = (char*)malloc(sizeof(char)*50);
	strcpy(path,"./Data/");
	strcat(path,user_name);
	switch(type){
		case 1: { // cart
			strcat(path,"/cart.txt");
			break;
		}
		case 2:{ // favorite
			strcat(path,"/favorite.txt");
			break;
		}
		case 3:{ // info
			strcat(path,"/info.txt");
			break;
		}
		case 5:{ //status
			strcat(path,"/status.txt");
			break;
		}
		case 4:{//pass
			strcat(path,"/pass.txt");
			break;
		}
	}
}



//write file
// ham tra ve 1 neu than cong, tra ve -1 neu that bai
int WriteInfoAccount(char* user_name,struct account_list* account_list){
	struct account* account = NULL;
	FILE* fr;
	account = SearchAccount(user_name,account_list);
	if(account == NULL){
		printf("account not exist!\n");
		return -1;
	}
	if(account!=NULL){
		// write cart
		fr=fopen(GetFilename(user_name,1),"w");
		if(fr ==NULL){
			printf("cant open file cart.txt for write !\n");
			return -1;
		}
		while(account.cart->next!=NULL){
			fprintf(fr, "%s\t",account.cart->item.item_name );
			fprintf(fr, "%d\n",account.cart->item.total );
		}
		fclose(fr);
		//write favorite
		fr = fopen(GetFilename(user_name,2),"w");
		if(fr == Null){
			printf("cant open file favorite.txt for write!\n");
			return -1;
		}
		while(account.favorite->next!=NULL){
			fprintf(fr, "%s\t",account.favorite->item.item_name );
		}
		fclose(fr);
		//write info
		fr = fopen(GetFilename(user_name,3),"w");
		if(fr == NULL){
			printf("cant open file info.txt for write!\n");
			return -1;
		}
		fprintf(fr, "%s\n",account.other_info->full_name );
		fprintf(fr, "%s\n",account.other_info->address );
		fprintf(fr, "%s\n",account.other_info->email );
		fprintf(fr, "%s\n",account.other_info->phone_number );
		fclose(fr);
		//write pass
		fr = fopen(GetFilename(user_name,4),"w");
		if(fr==NULL){
			printf("cant open file pass.txt for write!\n");
			return -1;
		}
		fprintf(fr, "%s\n",account.passwd );
		fclose(fr);
	}
}
// write list account
//return 1: done
// return -1: fail
int WriteListAccount(char* user_name,char* passwd){
	FILE* fr;
	fr = fopen("account_info.txt","a");
	if(fr ==NULL){
		printf("cant open file account_info.txt for write!\n");
		return -1;
	}
	fprintf(fr, "\n%s",user_name );
	struct stat stat = {0};
}
#endif 

