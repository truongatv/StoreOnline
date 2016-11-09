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
 	char* bio;	//mo ta
 	char* price; //gia
 	char* total; //so luong hien co
 }; 
 struct item_list
 {
 	/* data */
 	struct item item;  
 	struct item_list* next;
 };

struct account{
	char* username;
	char* passwd;
	struct other_info *other_info;
	struct item_list *cart; //gio hang
	struct item_list *favorite_list; //mat hang yeu thich
};