#ifndef SOCK_LIB
#define SOCK_LIB

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>

struct Server_info{
	char *addr;
	int port;
	int backlog;
};

struct Client_info{
	char *addr;
	int port;
	
};

int init_client(struct Client_info *c);
int init_server(struct Server_info *s);
void logger(char *s);
void recycle_child(void);


#endif
