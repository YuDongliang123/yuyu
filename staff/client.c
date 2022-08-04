#include "client.h"

int main(int argc, const char *argv[])
{
	//创建流式套接字
	int sfd = socket(AF_INET, SOCK_STREAM, 0);

	//填充服务器的IP和端口，因为客户端必须明确服务器的IP和端口才能连接
	struct sockaddr_in sin;
	sin.sin_family 		= AF_INET;
	sin.sin_port 		= htons(PORT); 		//服务器的端口号
	sin.sin_addr.s_addr = inet_addr(IP); 	//服务器绑定的IP
	
	//连接服务器
	if(connect(sfd, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		ERR_MSG("connect");
		return -1;
	}
	//数据库初始化
	sqlite3 *db = sqilte_init();
	//进入初始界面
	client_start(sfd);
	
	//关闭套接字
	close(sfd);
	return 0;
}