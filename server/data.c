
#include  <mysql/mysql.h>
#include <stdio.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}
void create_database(){
   MYSQL *con = mysql_init(NULL);
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  
  if (mysql_real_connect(con, "localhost", "root", "root", NULL, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }
   if (mysql_query(con, "CREATE DATABASE IF NOT EXISTS data")) 
  {
      printf("database is EXISTS\n");
      return;
  }  
}
int create_table(MYSQL* con){
  // char statement[100];
  // snprintf(statement,100,"SELECT * FROM account ",user_name);
  mysql_query(con,"SELECT * FROM account");
  MYSQL_RES *result = mysql_store_result(con);
  if(result != NULL){
    return 1;
  }
   if (mysql_query(con, "CREATE TABLE account(user_name varchar(20) NOT NULL,pass varchar(10) NOT NULL,status INT NOT NULL,PRIMARY KEY(user_name));")) {      
      printf("1\n");
      finish_with_error(con);
   }
   if(mysql_query(con,"CREATE TABLE account_info(user_name varchar(20) NOT NULL,full_name varchar(30) NOT NULL,address varchar(30) NOT NULL,email varchar(30),phone_number varchar(12) NOT NULL,foreign key(user_name) references account(user_name))")){
    printf("2\n");
    finish_with_error(con);
   }
   if(mysql_query(con,"CREATE TABLE item(item_name varchar(30) NOT NULL,price INT NOT NULL,PRIMARY KEY(item_name))")){
    printf("3\n");
    finish_with_error(con);
   }
   if(mysql_query(con,"CREATE TABLE account_cart(user_name varchar(20) NOT NULL,item_name varchar(30) NOT NULL,total INT NOT NULL,PRIMARY KEY(item_name,user_name),foreign key(user_name) references account(user_name),foreign key(item_name) references item(item_name))")){
    printf("4\n");
    finish_with_error(con);
   }
   if(mysql_query(con,"CREATE TABLE account_favorite(user_name varchar(20) NOT NULL,item_name varchar(30) NOT NULL,PRIMARY KEY(item_name,user_name),foreign key(user_name) references account(user_name),foreign key(item_name) references item(item_name))")){
    printf("5\n");
    finish_with_error(con);
   }
}
void create_account(char* user_name,char* password,MYSQL* con){
   char statement[100];
   snprintf(statement,100,"INSERT INTO account VALUES ('%s','%s',0)",user_name,password);
   // printf("%s\n",statement );
   mysql_query(con,statement);
}
void insert_info(char* user_name,char* full_name,char* address,char* email,char* phone_number,MYSQL* con ){
  char statement[200];
  snprintf(statement,200,"INSERT INTO account_info VALUES('%s','%s','%s','%s','%s')",user_name,full_name,address,email,phone_number);
  mysql_query(con,statement);
}
void delete_account(char* user_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"DELETE FROM account_info WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
}
void update_status(char* user_name,int status,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"UPDATE account SET status=%d WHERE user_name = '%s'",status,user_name);
  mysql_query(con,statement);
}
int check_exits_user_name(char* user_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT * FROM account WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  int row = mysql_num_rows(result);
  if(row == 0){
    return -1;
  }
  else return 1;
}
// 1:true
//-1: false
int check_password_from_user_name(char* user_name,char* password,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT * FROM account WHERE user_name = '%s' AND pass = '%s'",user_name,password);
  mysql_query(con,statement);
  MYSQL_RES* result = mysql_store_result(con);
  int row = mysql_num_rows(result);
  if(row == 0)
    return -1;
  else return 1;
}
// return 1 : status of account is online
// -1 : status of account is offline
int check_status_account(char* user_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT status FROM account WHERE user_name='%s'",user_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  row = mysql_fetch_row(result);
  // printf("%s\n",row[0] );
  if(atoi(row[0]) == 1){
    return 1;
  }
  else return -1;
}
int check_item_in_favorite_list(char*user_name,char* item_name,MYSQL*con){
  char statement[200];
  snprintf(statement,200,"SELECT * FROM account_favorite WHERE user_name = '%s' and item_name = '%s';",user_name,item_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  int row = mysql_num_rows(result);
  if(row == 0){
    return -1;
  }
  return 1;
}
int search_item(char* item_name,MYSQL *con){
  char statement[200];
  snprintf(statement,200,"SELECT * FROM item WHERE item_name = '%s'",item_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  int row = mysql_num_rows(result);
  if(row == 0){
    return -1;
  }
  return 1;

}
char* search_item_contain_keyword(char* item_name,MYSQL* con){
  char statement[200];
  char* temp;
  temp =(char*)malloc(sizeof(char)*100);
  snprintf(statement,200,"SELECT * FROM item WHERE item_name like '%%%s%%'",item_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  int row = mysql_num_rows(result);
  if(row == 0){
    return "";
  }
  MYSQL_ROW raw;
  strcpy(temp,"");
  raw = mysql_fetch_row(result);
  while(raw != NULL){
    strcat(temp,"\t");
    strcat(temp,raw[0]);
    strcat(temp," : ");
    strcat(temp,raw[1]);
    strcat(temp,"$\n");
    raw = mysql_fetch_row(result);
  }
  
  return temp;
}
void insert_item(char* item_name,int price,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"INSERT INTO item VALUES('%s','%d')",item_name,price);
  mysql_query(con,statement);
}
void insert_cart(char* user_name,char* item_name,int total,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"INSERT INTO account_cart VALUES('%s','%s','%d')",user_name,item_name,total);
  mysql_query(con,statement);
}
void insert_favorite(char* user_name,char* item_name,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"INSERT INTO account_favorite VALUES('%s','%s')",user_name,item_name);
  mysql_query(con,statement);
}
void delete_favorite(char* user_name,char* item_name,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"DELETE FROM account_favorite WHERE user_name = '%s' AND item_name = '%s'",user_name,item_name);
  mysql_query(con,statement);
}
char* show_all_favorite(char* user_name,MYSQL* con){
  char statement[200];
  char* temp = (char*)malloc(sizeof(char)*400);
  strcpy(temp,"");
  snprintf(statement,200,"SELECT item_name FROM account_favorite WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  if(mysql_num_rows(result) == 0){
    return " ";
  }
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))){
    strcat(temp,row[0]);
    strcat(temp,"\n");
  } 
  mysql_free_result(result);
  return temp;
}
int check_item_in_cart_list(char*user_name,char* item_name,MYSQL*con){
  char statement[200];
  snprintf(statement,200,"SELECT * FROM account_cart WHERE user_name = '%s' and item_name = '%s';",user_name,item_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  int row = mysql_num_rows(result);
  if(row == 0){
    return -1;
  }
  return 1;
}
int check_item_number_in_cart_list(char* user_name,char* item_name,MYSQL*con){
  char statement[200];
  snprintf(statement,200,"SELECT total FROM account_cart WHERE user_name = '%s' and item_name = '%s';",user_name,item_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  row = mysql_fetch_row(result);
  return atoi(row[0]);
}
void delete_item_from_cart(char* user_name,char* item_name,MYSQL* con){
    char statement[100];
    snprintf(statement,100,"DELETE FROM account_cart WHERE user_name = '%s' AND item_name = '%s'",user_name,item_name);
    mysql_query(con,statement);
}
char* show_list_cart(char* user_name,MYSQL* con){
  char statement[100];
  int i=0;
  snprintf(statement,100,"SELECT item_name,total FROM account_cart WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
  char* temp = (char*)malloc(sizeof(char)*400);
  MYSQL_RES* result = mysql_store_result(con);
  if(mysql_num_rows(result) == 0){
    return " ";
  }
  MYSQL_ROW row;
  while(row = mysql_fetch_row(result)){
    if(i == 0 ){
      strcpy(temp,row[0]);
      strcat(temp,"\t");
      strcat(temp,row[1]);
    }
    else {
      strcat(temp,"\n");
      strcat(temp,row[0]);
      strcat(temp,"\t");
      strcat(temp,row[1]);
    }
    i++;
  }
  return temp;
}
void update_item_number_in_cart_list(char* user_name,char* item_name,int number,MYSQL*con){
  char statement[200];
  snprintf(statement,200,"UPDATE account_cart SET total = %d WHERE user_name = '%s' and item_name = '%s'",number,user_name,item_name);
  mysql_query(con,statement);
}
int get_price(char* item_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT price FROM item WHERE item_name = '%s'",item_name);
  mysql_query(con,statement);
  MYSQL_RES* result = mysql_store_result(con);
  MYSQL_ROW row = mysql_fetch_row(result);
  return atoi(row[0]);
}
int get_total_cost(char* user_name,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"SELECT item_name,total FROM account_cart WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
  char* temp = (char*)malloc(sizeof(char)*400);
  MYSQL_RES* result = mysql_store_result(con);
  int i = 0;
  int total = 0;
  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  while(row = mysql_fetch_row(result)){
    total += (get_price(row[0],con))*atoi(row[1]);
  }
  return total;
}

void update_account_info(char* user_name,char* info_column,char* new_info,MYSQL* con){
  char statement[200];

  snprintf(statement,200,"SELECT * from account_info WHERE user_name = '%s';",user_name);
  mysql_query(con,statement);
  MYSQL_RES* result = mysql_store_result(con);
  if(mysql_num_rows(result) != 0){
    snprintf(statement,200,"UPDATE account_info SET %s  = '%s' WHERE user_name = '%s';",info_column,new_info,user_name);
    mysql_query(con,statement);
  } else{
    if(strcmp(info_column,"full_name") == 0){
      insert_info(user_name,new_info,"","","",con);
    } else{
      if(strcmp(info_column,"email") == 0){
        insert_info(user_name,"","",new_info,"",con );
      } else{
        if(strcmp(info_column,"address") == 0){
          insert_info(user_name,"",new_info,"","",con );
        } else{
          if(strcmp(info_column,"phone_number") == 0){
            insert_info(user_name,"","","",new_info,con);
          }
        }
      }
    }
  }
}

char* get_account_info(char* user_name,MYSQL* con){
  char statement[200];

  snprintf(statement,200,"SELECT * from account_info WHERE user_name = '%s';",user_name);
  mysql_query(con,statement);

  MYSQL_RES* _result = mysql_store_result(con);
  MYSQL_ROW row;
  row = mysql_fetch_row(_result);

  char* result = (char*)malloc(sizeof(char)*1024);
  strcpy(result,"\nFull name: ");
  strcat(result,row[1]);
  strcat(result,"\nAddress: ");
  strcat(result,row[2]);
  strcat(result,"\nEmail: ");
  strcat(result,row[3]);
  strcat(result,"\nPhone Number: ");
  strcat(result,row[4]);
  return result;
}





// void main(){
//    MYSQL *con = mysql_init(NULL);
//    if (con == NULL) 
//    {
//       fprintf(stderr, "%s\n", mysql_error(con));
//       exit(1);
//    } 
//    create_database(); 
//    if (mysql_real_connect(con, "localhost", "root", "root", "data", 0, NULL, 0) == NULL) 
//    {
//       finish_with_error(con);
//    }
//    create_table(con);
//    create_account("linh","linh123",con);
//    create_account("minh","minh123",con);
//    create_account("phuc","phuc123",con);
//    create_account("truong","truong123",con);
//    create_account("nam","nam123",con);
//    insert_info("minh","nguyen tri minh","ha noi","ntm@gmail.com","0123456",con);
//    insert_info("minh","nguyen tien truong","ha noi","ntt@gmail.com","123455",con);
//    // printf("done\n");
//    printf("check EXISTS account: %d\n",check_exits_user_name("nam",con));
//    delete_account("minh",con);
//    insert_item("sach1",100,con);
//    insert_item("sach2",200,con);
//    insert_item("sach3",300,con);
//    insert_cart("truong","sach1",3,con);
//    insert_cart("minh","sach1",4,con);
//    insert_cart("minh","sach2",4,con);
//    // delete_item_from_cart("minh","sach1",con);
//    printf("show list cart: %s\n",show_list_cart("minh",con) );
//    insert_favorite("minh","sach1",con);
//    insert_favorite("minh","sach2",con);
//    insert_favorite("truong","sach1",con);
//    insert_favorite("truong","sach1",con);
//    printf("%d\n",check_status_account("linh",con));
//    printf("%d\n",check_status_account("nam",con));
//    updata_status("nam",1,con);
//    printf("%d\n",check_status_account("nam",con) );
//    printf("%s\n",search_item("sach1",con) );
//    // delete_favorite("truong","sach1",con);
//    printf("show all favorite: %s\n",show_all_favorite("minh",con) );
//    printf("total cost: %d\n",get_total_cost("minh",con) );
//    // show_all_favorite("minh",con);
//     // insert_cart("truong","sach1",5,con);
//    // printf("%d\n",check_exits_user_name("minh",con) );
//    // printf("%d\n",check_exits_user_name("nam",con) );
//    // printf("%d\n",check_password_from_user_name("minh","minh123",con) );
//    // updata_info_account("minh","minh123","nguyen van minh","ha nam","nvm@gmail.com","1234",con);
//    printf("%s",search_item("sach",con));
//    mysql_close(con);
//   exit(0);
// }