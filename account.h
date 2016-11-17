#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	CreateNodeAccount(temp);
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
void CopyAccount(struct account currentAccount,struct account newAccount){
	strcpy(newAccount.user_name,currentAccount.user_name);
	newAccount.state = currentAccount.state;
	strcpy(newAccount.passwd,currentAccount.passwd);
	strcpy(newAccount.other_info.full_name,currentAccount.other_info.full_name);
	strcpy(newAccount.other_info.email,currentAccount.other_info.email);
	strcpy(newAccount.other_info.address,currentAccount.other_info.address);
	strcpy(newAccount.other_info.phone_number,currentAccount.other_info.phone_number);
	CopyItem(currentAccount.favorite_list,newAccount.favorite_list);
	CopyItem(currentAccount.cart,newAccount.cart);
}
void CreateNodeAccount(struct account_list* account_list){
	(account_list->account).user_name = (char*)malloc(sizeof(char)*20);
	(account_list->account).passwd = (char*)malloc(sizeof(char)*20);
	(account_list->account).other_info.email = (char*)malloc(sizeof(char)*30);
	(account_list->account).other_info.full_name = (char*)malloc(sizeof(char)*40);
	(account_list->account).other_info.address = (char*)malloc(sizeof(char)*50);
	(account_list->account).other_info.phone_number = (char*)malloc(sizeof(char)*50);
}



// add item for linklist
#endif 