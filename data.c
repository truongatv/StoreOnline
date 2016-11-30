
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
   if(mysql_query(con,"CREATE TABLE account_info(user_name varchar(20) NOT NULL,full_name varchar(30) NOT NULL,address varchar(30) NOT NULL,email varchar(30),sdt varchar(12) NOT NULL,foreign key(user_name) references account(user_name))")){
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
void create_account(char* user_name,char* password,int status,MYSQL* con){
   char statement[100];
   snprintf(statement,100,"INSERT INTO account VALUES ('%s','%s','%d')",user_name,password,status);
   // printf("%s\n",statement );
   mysql_query(con,statement);
}
void insert_info(char* user_name,char* full_name,char* address,char* email,char* sdt,MYSQL* con ){
  char statement[200];
  snprintf(statement,200,"INSERT INTO account_info VALUES('%s','%s','%s','%s','%s')",user_name,full_name,address,email,sdt);
  mysql_query(con,statement);
}
void delete_account(char* user_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"DELETE FROM account_info WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
}
int check_exits_user_name(char* user_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT * FROM account WHERE user_name = '%s'",user_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  if(result ==NULL){
    return -1;
  }
  else return 1;
}
int check_password_from_user_name(char* user_name,char* password,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT * FROM account WHERE user_name = '%s' AND pass = '%s'",user_name,password);
  mysql_query(con,statement);
  MYSQL_RES* result = mysql_store_result(con);
  if(result == NULL)
    return -1;
  else return 1;
}
int check_status_account(char* user_name,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"SELECT status FROM account WHERE user_name='%s'",user_name);
  mysql_query(con,statement);
  MYSQL_RES *result = mysql_store_result(con);
  MYSQL_ROW row;
  row = mysql_fetch_row(result);
  printf("%s\n",row );
  return 1;
}
void insert_item(char* item_name,int price,MYSQL* con){
  char statement[100];
  snprintf(statement,100,"INSERT INTO item VALUES('%s','%d')",item_name,price);
  mysql_query(con,statement);
}
void insert_cart(char* user_name,char* item_name,int total,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"INSERT INTO account_cart VALUES('%s','%s','%d')",user_name,item_name,total);
  // printf("%s\n",statement );
  mysql_query(con,statement);
}
void insert_favorite(char* user_name,char* item_name,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"INSERT INTO account_favorite VALUES('%s','%s')",user_name,item_name);
  mysql_query(con,statement);
}
void updata_info_account(char* user_name,char* password,char* full_name,char* address,char* email,char* sdt,MYSQL* con){
  char statement[200];
  snprintf(statement,200,"UPDATE account_info SET full_name = '%s',address = '%s',email = '%s',sdt = '%s' WHERE user_name = '%s'",full_name,address,email,sdt,user_name);
  mysql_query(con,statement);
  snprintf(statement,200,"UPDATA account SET pass = '%s' WHERE user_name = '%s'",password,user_name);
  mysql_query(con,statement);
}
void main(){
   MYSQL *con = mysql_init(NULL);
  // char pass[]="truong";
   int pass = 2;
   if (con == NULL) 
   {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
   } 
   create_database(); 
   if (mysql_real_connect(con, "localhost", "root", "root", "data", 0, NULL, 0) == NULL) 
   {
      finish_with_error(con);
   }
   create_table(con);
   create_account("linh","linh123",0,con);
   create_account("minh","minh123",0,con);
   create_account("phuc","phuc123",0,con);
   create_account("truong","truong123",1,con);
   create_account("nam","nam123",1,con);
   insert_info("minh","nguyen tri minh","ha noi","ntm@gmail.com","0123456",con);
   insert_info("minh","nguyen tien truong","ha noi","ntt@gmail.com","123455",con);
   // printf("done\n");
   delete_account("minh",con);
   insert_item("sach1",100,con);
   insert_item("sach2",200,con);
   insert_item("sach3",300,con);
   insert_cart("truong","sach1",3,con);
   insert_cart("minh","sach1",4,con);
   insert_cart("minh","sach2",4,con);
   insert_favorite("minh","sach1",con);
   insert_favorite("minh","sach2",con);
   insert_favorite("truong","sach1",con);
   insert_favorite("truong","sach1",con);
   // insert_cart("truong","sach1",5,con);
   // printf("%d\n",check_exits_user_name("minh",con) );
   // printf("%d\n",check_password_from_user_name("minh","minh123",con) );
   // updata_info_account("minh","minh123","nguyen van minh","ha nam","nvm@gmail.com","1234",con);
   mysql_close(con);
  exit(0);
}