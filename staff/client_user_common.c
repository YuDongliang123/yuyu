#include "client.h"

int client_user_common(int sfd)
{
	char temp = 0;
	while(1)
	{
		printf("\n");

		printf("******************************\n");
		printf("**        1.查询            **\n");
		printf("**        2.修改            **\n");
		printf("**        3.退出            **\n");
		printf("******************************\n");
		
		printf("请输入(数字)>>>");
		scanf("%s",&choose);
		send(sfd, &choose, sizeof(choose), 0);
		switch(choose)
		{
		case '1':
			printf("工号    用户类型    姓名    密码    年龄    电话    地址    职位    入职年月    等级    工资\n");
			printf("-------------------------------------------------------------------------------------------\n");
			bzero(buf, sizeof(buf));
			res = recv(sfd, buf, sizeof(buf), 0);
			printf("%s",buf);
			break;
		case '2':
			printf("****************请输入要修改的选项***************\n");
			printf("**   1.家庭住址   2.电话   3.密码   4.退出     **\n");
			printf("*************************************************\n");
			printf("请输入您的选择（数字）>>");scanf("%s",&temp);send(sfd, &temp, sizeof(temp), 0);
			switch(temp)
			{
				case '1':
					printf("请输入家庭住址: ");scanf("%s",people_t.address);
					send(sfd, people_t.address, sizeof(people_t.address), 0);
					break;
				case '2':
					printf("请输入电话: ");scanf("%s",people_t.phone_number);
					send(sfd, people_t.phone_number, sizeof(people_t.phone_number), 0);
					break;
				case '3':
					printf("请输入密码(其他信息亲请联系管理员): ");scanf("%s",people_t.password);
					send(sfd, people_t.password, sizeof(people_t.password), 0);
					break;
				case '4':
					return 0;
				default:
					bzero(buf, sizeof(buf));
					res = recv(sfd, buf, sizeof(buf), 0);
					printf("%s",buf);
			}
			bzero(buf, sizeof(buf));res = recv(sfd, buf, sizeof(buf), 0);printf("%s",buf);
			break;
        case '3':
			return 0;
		default:
			bzero(buf, sizeof(buf));res = recv(sfd, buf, sizeof(buf), 0);printf("%s",buf);
		}
	}

}