#include "client.h"

void client_start(int sfd)
{
	while (1)
	{
		printf("\n");

		printf("******************************\n");
		printf("**        1.普通用户        **\n");
		printf("**        2.root用户        **\n");
		printf("**        3.退出            **\n");
		printf("******************************\n");
		printf("请输入(数字)>>>");
		scanf("%s",&choose);
		send(sfd, &choose, sizeof(choose), 0);
		switch (choose)
		{
		case '1':
			bzero(people_t.name, sizeof(people_t.name));
			printf("请输入用户名:");scanf("%s", people_t.name);
			send(sfd, people_t.name, sizeof(people_t.name), 0);
			
			bzero(people_t.password, sizeof(people_t.password));
			printf("请输入密码:");scanf("%s", people_t.password);
			send(sfd, people_t.password, sizeof(people_t.password), 0);

			bzero(buf, sizeof(buf));
			res = recv(sfd, buf, sizeof(buf), 0);
			printf("%s",buf);
			if(strcmp(buf,"亲爱的用户，欢迎您登陆员工管理系统！\n") == 0)
			{
				client_user_common(sfd);
				}
			break;
		case '2':
			bzero(people_t.name, sizeof(people_t.name));
			printf("请输入用户名:");scanf("%s", people_t.name);
			send(sfd, people_t.name, sizeof(people_t.name), 0);
			
			bzero(people_t.password, sizeof(people_t.password));
			printf("请输入密码:");scanf("%s", people_t.password);
			send(sfd, people_t.password, sizeof(people_t.password), 0);

			bzero(buf, sizeof(buf));
			res = recv(sfd, buf, sizeof(buf), 0);
			printf("%s",buf);
			if(strcmp(buf,"亲爱的管理员，欢迎您登陆员工管理系统！\n") == 0)
			{
				client_user_root(sfd);
				}
			break;
		case '3':
			return;
		default:
			bzero(buf, sizeof(buf));
			res = recv(sfd, buf, sizeof(buf), 0);
		}
	}
}