#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "client_to_server.c"

<<<<<<< HEAD
#define PORT 5555
=======
#define PORT 6550
>>>>>>> cc48df9ba4b719707c24a5079afd593472f949d6
#define clear() printf("\033[H\033[J")

void first_menu(char* choise);
void second_menu(char* choise);
void third_menu(char* choise);
void fourth_menu(char* choise);
void fifth_menu(char* choise);
void sixth_menu(char* choise);
int main();

#endif