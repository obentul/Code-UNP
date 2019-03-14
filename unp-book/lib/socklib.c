#include "socklib.h"

/* 描述：初始化服务端
 * 返回值：监听套接字描述符
 * 入参：服务器参数
 *
 * */

int init_server(struct Server_info *s)
{
	int sockfd;
	struct sockaddr_in saddr;
	int ret;

	logger("init server\n");

	//入参检查
	//para_check(s);

	memset(&saddr,0x00,sizeof(struct sockaddr_in));

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(s->addr);
	saddr.sin_port = htons(s->port);

	sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd == -1)
	{
		perror("socket() error");
		return -1;
	}
	
	ret = bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(ret == -1)
	{
		perror("bind() error");	
		return -1;
	}

	listen(sockfd,s->backlog);
	
	return sockfd;
}

int init_client(struct Client_info *c)
{
	int sockfd;
	struct sockaddr_in caddr;
	int ret;

	logger("init client\n");
	
	//入参检查
	//para_check(c);
	
	memset(&caddr,0x00,sizeof(struct sockaddr_in));	

	caddr.sin_family = AF_INET;
	caddr.sin_addr.s_addr = inet_addr(c->addr);
	caddr.sin_port = htons(c->port);

	sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockfd == -1)
	{
		perror("socket() error");
		return -1;
	}

	return sockfd;
}

void logger(char *s)
{
	printf("[%d][%s]%s",__LINE__,__FILE__,s);
}

void recycle_child(void)
{
	waitpid(-1,NULL,NULL);
	return;
}

void lssockopt(int sockfd)
{
	





}





