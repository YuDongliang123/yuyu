#include "server.h"
#include "server.h"

int rcv_cli_msg(int newfd, struct sockaddr_in);

typedef void (*sighandler_t)(int);
void handler(int sig)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
	return;
}

int main(int argc, const char *argv[])
{
	//注册17)SIGCHLD信号 回收僵尸进程
	sighandler_t s = signal(SIGCHLD, handler);
	if(SIG_ERR == s)
	{
		ERR_MSG("signal");
		return -1;
	}
	
	//创建流式套接字
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd < 0)
	{
		ERR_MSG("socket");
		return -1;
	}

	//允许端口快速重用
	int reuse = 1;
	if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
		ERR_MSG("setsockopt");
		return -1;
	}

	//填充地址信息结构体
	struct sockaddr_in sin;
	sin.sin_family 		= AF_INET;
	sin.sin_port 		= htons(PORT); 		//网络字节序的端口号
	sin.sin_addr.s_addr = inet_addr(IP); 	//本机IP

	//将IP和端口绑定到套接字上
	if(bind(sfd, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		ERR_MSG("bind");
		return -1;
	}

	//将套接字设置为被动监听状态;
	if(listen(sfd, 10) < 0)
	{
		ERR_MSG("listen");
		return -1;
	}

	//创建一个读集合
	fd_set readfds, tempfds;

	FD_ZERO(&readfds); 		//清空集合
	FD_ZERO(&tempfds); 		//清空集合
	
	FD_SET(0, &readfds); 	//将0号文件描述符添加到集合中
	FD_SET(sfd, &readfds); 	//将sfd添加到文件描述符集合中

	int maxfd = sfd; 		//集合中最大的文件描述符

	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);

	int newfd = 0;
	pid_t pid = -1;

	while(1)
	{
		newfd = accept(sfd, (struct sockaddr*)&cin, &addrlen);
		if(newfd < 0)
		{
			ERR_MSG("accept");
			return -1;
		}
		
		//创建一个子进程，专门用于与客户端交互
		pid = fork();
		if(pid > 0)
		{
			//父进程运行
			close(newfd);
		}
		else if(0 == pid)
		{
			//子进程运行---与客户端交互
			close(sfd);
			printf("------The client is successfully connected------\n");
			rcv_cli_msg(newfd, cin);
			exit(0);
		}
		else
		{
			ERR_MSG("fork");
			return -1;
		}
	}

	close(sfd);
	return 0;
}

int rcv_cli_msg(int newfd, struct sockaddr_in cin)
{
	//数据库初始化
	sqlite3 *db =sqilte_init();
	while(1)
	{
		server_start(db,newfd);
	}

	close(newfd);
	return 0;
}