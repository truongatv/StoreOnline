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
struct item
 {
 	/* data */
 	char* item_name; // ten
 	char* price; //gia
 	char* total; //so luong 
 }; 
 struct item_list
 {
 	/* data */
 	struct item item;  
 	struct item_list* next;
 };

struct account{
	char* user_name;
	char* passwd;
	char* state;
	struct other_info *other_info;
	struct item_list *cart; //gio hang
	struct item_list *favorite_list; //mat hang yeu thich
};
struct account_list{
	struct account account;
	struct account_list *next;
}
#endif 