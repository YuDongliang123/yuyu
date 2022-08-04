#include "client.h"

int client_user_root(int sfd)
{
	int temp;
	char is;
	while(1)
	{
		printf("\n");
		printf("******************************\n");
		printf("**        1.查询            **\n");
		printf("**        2.修改            **\n");
        printf("**        3.添加用户        **\n");
        printf("**        4.删除用户        **\n");
        printf("**        5.查询历史记录    **\n");
		printf("**        6.退出            **\n");
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
			printf("请输入要修改的用户工号:");scanf("%s",people_t.number);send(sfd, people_t.number, sizeof(people_t.number), 0);
			printf("****************请输入要修改的选项***************\n");
			printf("**     1.姓名       2.年龄       3.家庭住址    **\n");
		    printf("**     4.电话       5.职位       6.工资        **\n");
			printf("**     7.入职年月   8.评级       9.密码        **\n");
			printf("**     10.退出                                 **\n");
			printf("*************************************************\n");
			printf("请输入您的选择（数字）>>");scanf("%d",&temp);send(sfd, &temp, sizeof(temp), 0);
			switch(temp)
			{
				case 1:
					printf("请输入姓名: ");scanf("%s",people_t.name);
					send(sfd, people_t.name, sizeof(people_t.name), 0);
					break;
				case 2:
					printf("请输入年龄: ");scanf("%s",people_t.age);
					send(sfd, people_t.age, sizeof(people_t.age), 0);
					break;
				case 3:
					printf("请输入家庭住址: ");scanf("%s",people_t.address);
					send(sfd, people_t.address, sizeof(people_t.address), 0);
					break;
				case 4:
					printf("请输入电话: ");scanf("%s",people_t.phone_number);
					send(sfd, people_t.phone_number, sizeof(people_t.phone_number), 0);
					break;
				case 5:
					printf("请输入职位: ");scanf("%s",people_t.job);
					send(sfd, people_t.job, sizeof(people_t.job), 0);
					break;
				case 6:
					printf("请输入工资: ");scanf("%s",people_t.money);
					send(sfd, people_t.money, sizeof(people_t.money), 0);
					break;
				case 7:
					printf("请输入入职年月: ");scanf("%s",people_t.year);
					send(sfd, people_t.year, sizeof(people_t.year), 0);
					break;
				case 8:
					printf("请输入评级: ");scanf("%s",people_t.level);
					send(sfd, people_t.level, sizeof(people_t.level), 0);
					break;
				case 9:
					printf("请输入密码: ");scanf("%s",people_t.password);
					send(sfd, people_t.password, sizeof(people_t.password), 0);
					break;
				case 10:
					continue;
				default:
					bzero(buf, sizeof(buf));res = recv(sfd, buf, sizeof(buf), 0);printf("%s",buf);
			}
			bzero(buf, sizeof(buf));res = recv(sfd, buf, sizeof(buf), 0);printf("%s",buf);
			break;
        case '3':
			bzero(buf, sizeof(buf));
			printf("请输入工号: ");
			scanf("%s",buf);getchar();
			printf("您输入的工号是：%s\n",buf);
			printf("工号信息一旦录入无法更改，请确认您所输入的是否正确! (Y/N) ");
			scanf("%c",&is);
			if(is == 'N' | is == 'n') {
				break;
			}
			strcpy(people_t.number,buf);

			printf("请输入姓名: ");scanf("%s",people_t.name);getchar();
			printf("请输入密码: ");scanf("%s",people_t.password);getchar();
			printf("请输入年龄: ");scanf("%s",people_t.age);getchar();
			printf("请输入电话: ");scanf("%s",people_t.phone_number);getchar();
			printf("请输入地址: ");scanf("%s",people_t.address);getchar();
			printf("请输入职位: ");scanf("%s",people_t.job);getchar();
			printf("请输入入职年月: ");scanf("%s",people_t.year);getchar();
			printf("请输入评级(1~5,5最高,新员工为1): ");scanf("%s",people_t.level);getchar();
			printf("请输入工资: ");scanf("%s",people_t.money);getchar();
			printf("是否为管理员 (Y/N) ");scanf("%c",&is);
			if(is == 'Y' | is == 'y') {
				strcpy(people_t.user,"root");
			}
			else {
				strcpy(people_t.user,"common");
			}
			//发送员工结构体信息
			send(sfd, &people_t, sizeof(people_t), 0);

			printf("员工添加成功！\n");
			printf("是否继续添加员工 (Y/N) ");scanf("%c",&is);getchar();send(sfd, &is, sizeof(is), 0);
			if(is == 'Y' | is == 'y') {
				continue;
			}
			else {
				break;
			}
        case '4':
			printf("请输入要删除的用户工号:");scanf("%s",people_t.number);getchar();send(sfd, people_t.number, sizeof(people_t.number), 0);
			printf("请输入要删除的用户名:");scanf("%s",people_t.name);getchar();send(sfd, people_t.name, sizeof(people_t.name), 0);
			printf("数据库修改成功! 删除工号为: %s 的用户\n",people_t.number);
			printf("是否继续删除员工 (Y/N) ");scanf("%c",&is);getchar();send(sfd, &is, sizeof(is), 0);
			if(is == 'Y' | is == 'y') {
				continue;
			}
			break;
        case '5':
			bzero(buf, sizeof(buf));
			res = recv(sfd, buf, sizeof(buf), 0);
			printf("%s",buf);
			break;
		case '6':
			return 0;
		default:
			bzero(buf, sizeof(buf));res = recv(sfd, buf, sizeof(buf), 0);printf("%s",buf);
		}
	}
}