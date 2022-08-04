#include "server.h"

void server_start(sqlite3 *db,int sfd)
{
	while (1)
	{
		res = recv(sfd, &choose, sizeof(choose), 0);
		switch (choose)
		{
		//普通用户
		case '1':
			//接受客户端发送的用户名、密码
			bzero(people_t.name, sizeof(people_t.name));
			res = recv(sfd, people_t.name, sizeof(people_t.name), 0);

			bzero(people_t.password, sizeof(people_t.password));
			res = recv(sfd, people_t.password, sizeof(people_t.password), 0);

			sprintf(sql, "select * from member where (name = \"%s\" and password = \"%s\");",people_t.name,people_t.password);
			ret = sqlite3_get_table(db, sql, &dbResult, &row, &col, &errmsg);
			if(row==0 && col==0)
			{
				strcpy(buf,"------Common user login error------\n");
				printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
				if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
				bzero(buf, sizeof(buf));strcpy(buf,"用户名或密码错误!!!\n");send(sfd, buf, sizeof(buf), 0);
				continue;
			}
			sqlite3_free_table(dbResult);
			sprintf(sql, "select * from member where (name = \"%s\" and password = \"%s\" and user = \"common\");",people_t.name,people_t.password);
			ret = sqlite3_get_table(db, sql, &dbResult, &row, &col, &errmsg);
			if(row==0 && col==0)
			{
				bzero(buf, sizeof(buf));strcpy(buf,"非普通用户!!!\n");send(sfd, buf, sizeof(buf), 0);
				continue;
			}
			sqlite3_free_table(dbResult);
			bzero(buf, sizeof(buf));strcpy(buf,"亲爱的用户，欢迎您登陆员工管理系统！\n");send(sfd, buf, sizeof(buf), 0);
			sprintf(buf,"------Common user %s login succeeded------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			server_user_common(db,sfd);
			break;
		//管理员
		case '2':
			//接受客户端发送的用户名、密码
			bzero(people_t.name, sizeof(people_t.name));
			res = recv(sfd, people_t.name, sizeof(people_t.name), 0);

			bzero(people_t.password, sizeof(people_t.password));
			res = recv(sfd, people_t.password, sizeof(people_t.password), 0);

			sprintf(sql, "select * from member where (name = \"%s\" and password = \"%s\");",people_t.name,people_t.password);
			ret = sqlite3_get_table(db, sql, &dbResult, &row, &col, &errmsg);
			if(row==0 && col==0)
			{
				strcpy(buf,"------Admin user login error------\n");
				printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
				if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
				bzero(buf, sizeof(buf));strcpy(buf,"用户名或密码错误!!!\n");send(sfd, buf, sizeof(buf), 0);
				continue;
			}
			sqlite3_free_table(dbResult);
			sprintf(sql, "select * from member where (name = \"%s\" and password = \"%s\" and user = \"root\");",people_t.name,people_t.password);
			ret = sqlite3_get_table(db, sql, &dbResult, &row, &col, &errmsg);
			if(row==0 && col==0)
			{
				bzero(buf, sizeof(buf));strcpy(buf,"非管理员用户!!!\n");send(sfd, buf, sizeof(buf), 0);
				continue;
			}
			sqlite3_free_table(dbResult);
			bzero(buf, sizeof(buf));strcpy(buf,"亲爱的管理员，欢迎您登陆员工管理系统！\n");send(sfd, buf, sizeof(buf), 0);
			sprintf(buf,"------Admin user %s login succeeded------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			server_user_root(db,sfd);
			break;
		case '3':
			if (sqlite3_close(db) != SQLITE_OK);
			return;
		default:
			bzero(buf, sizeof(buf));strcpy(buf,"输入错误，请重新输入\n");send(sfd, buf, sizeof(buf), 0);
		}
	}
}