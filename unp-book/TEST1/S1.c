#include "socklib.h"
#include <signal.h>

int main(int argc , char ** argv)
{
	int lfd,cfd;
	int pid;
	struct sockaddr_in caddr;
	int caddr_len;
	struct Server_info s;

	if(argc!=4)
	{
		logger("error usage,number of argv should be 4: ./x ip port backlog .");
		return -1;
	}

	signal(SIGCHLD,recycle_child);	

	memset(&caddr,0x00,sizeof(struct sockaddr_in));
	memset(&s,0x00,sizeof(struct Server_info));
	
	s.addr=argv[1];
	s.port=atoi(argv[2]);
	s.backlog=atoi(argv[3]);

	lfd = init_server(&s);
	
	cfd = accept(lfd,(struct sockaddr *)&caddr,&caddr_len);
	
	if(cfd == -1)
	{
		perror("accept error");
		return -1;
	}
	
	pid = fork();
	if(pid == 0)
	{
		int tmp,nbytes;
		char r_buff[4096];
		memset(r_buff,0x00,4096);
		logger("child process,continue process\n");
		sleep(2);

		again1:
		if(nbytes = read(cfd,r_buff,4096)>0)
		{
			printf("read %d bytes -> %s\n",nbytes,r_buff);
			goto again1;
		}
		if(nbytes == -1)
		{
			perror("read error\n");
			return -1;
		}
		logger("child process finish, return 0\n");
		return 0;
	}

	if(pid>0)
	{
		logger("parent process\n");
		close(cfd);
		close(lfd);
		waitpid(pid,NULL,NULL);
		printf("recycle child success %d\n",pid);
		while(1) sleep(1);	
	}

}










