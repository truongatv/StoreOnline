#include "account.h"
struct item_list* Insert_Item_ToFirst(struct item *i){
	struct item_list* first;
	first = (struct item_list*) malloc(sizeof(item_list*));
	first.item->item_name = (char*)malloc(sizeof(char)*30);
	first.item->bio = (char*)malloc(sizeof(char)*60);
	first.item->price  = (char*)malloc(sizeof(char)* 20);
	first.item->total = (char*)malloc(sizeof(char) * 5);
	strcpy(first.item->item_name,i->item_name);
	strcpy(first.item->bio,i->bio);
	strcpy(first.item->price,i->price);
	strcpy(first.item->total,i->total);
	first->next = NULL;
	return first;
}

struct item_list* Insert_Item_ToLast(struct item_list* last,struct item i){
	struct item_list* tempNode;
	tempNode = (struct item_list*) malloc(sizeof(item_list*));
	tempNode.item->item_name = (char*)malloc(sizeof(char)*30);
	tempNode.item->bio = (char*)malloc(sizeof(char)*60);
	tempNode.item->price  = (char*)malloc(sizeof(char)* 20);
	tempNode.item->total = (char*)malloc(sizeof(char) * 5);
	strcpy(tempNode.item->item_name,i->item_name);
	strcpy(tempNode.item->bio,i->bio);
	strcpy(tempNode.item->price,i->price);
	strcpy(tempNode.item->total,i->total);
	tempNode->next = NULL;
	last->next = tempNode;
	last = tempNode;
	return last;
}

struct item Search_Item(struct item_list* first,char* item_name){
	struct item_list* tempNode = (struct item_list*)malloc(sizeof(item_list));
	tempNode = first;
	do{
		if(strcmp(tempNode->item->item_name, item_name) == 0){
			return tempNode->item;
		}
		tempNode = tempNode->next;
	}while(tempNode != NULL);
	return NULL;
}


struct account * Create_New_Account(char* user_name,char* passwd, struct other_info*other_info,struct item_list *cart,struct item_list * favorite){
	struct account *acc;
	acc = (struct account*) malloc(sizeof(struct account));
	acc->user_name = (char*) malloc(sizeof(char) * 50);
	acc->passwd = (char*) malloc(sizeof(char) * 50);
	acc->other_info = (struct other_info*)malloc(sizeof(struct other_info));
	acc->other_info->email = (char*)malloc(sizeof(char)*30);
	acc->other_info->full_name = (char*)malloc(sizeof(char)*20);
	acc->other_info->address = (char*)malloc(sizeof(char)*60);
	acc->other_info->phone_number =(char*)malloc(sizeof(char)*20)

	strcpy()
}
void Insert_Account_ToFirst(struct account_list*first,struct account_list* last,struct account *acc){

}