MYSQL_LIBS := $(shell mysql_config --libs)
server: server.c server.h data.c server_to_client.c server_to_client.h
	gcc -o server server.c $(MYSQL_LIBS) -w