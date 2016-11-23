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