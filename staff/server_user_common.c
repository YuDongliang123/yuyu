#include "server.h"

int server_user_common(sqlite3 *db,int sfd)
{
	char temp = 0;
	while(1)
	{
		res = recv(sfd, &choose, sizeof(choose), 0);
		switch(choose)
		{
		//查看用户信息
		case '1':
			sprintf(sql,"select * from member where name=\"%s\";",people_t.name);
			ret = sqlite3_get_table(db, sql, &dbResult, &row, &col, &errmsg);
			bzero(buf, sizeof(buf));
			for(int i=1;i<=row;i++) {
				for(int j=0;j<col;j++) {
					strcat(buf,dbResult[11*i + j]);
					strcat(buf,"  ");
				}
				strcat(buf,"\n");
			}
			send(sfd, buf, sizeof(buf), 0);
			sqlite3_free_table(dbResult);
			break;
		//修改部分信息
		case '2':
			sprintf(buf,"------The common user %s tried to modify------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

			res = recv(sfd, &temp, sizeof(temp), 0);
			switch(temp)
			{
				case '1':
					res = recv(sfd, people_t.address, sizeof(people_t.address), 0);
					sprintf(buf,"------The common user %s address %s changed------\n",people_t.name,people_t.address);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set address=\"%s\" where name=\"%s\";",people_t.address,people_t.name);
					break;
				case '2':
					res = recv(sfd, people_t.phone_number, sizeof(people_t.phone_number), 0);
					sprintf(buf,"------The common user %s phone_number %s changed------\n",people_t.name,people_t.phone_number);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set phone_number=\"%s\" where name=\"%s\";",people_t.phone_number,people_t.name);
					break;
				case '3':
					res = recv(sfd, people_t.password, sizeof(people_t.password), 0);
					sprintf(buf,"------The common user %s password %s changed------\n",people_t.name,people_t.password);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set password=\"%s\" where name=\"%s\";",people_t.password,people_t.name);
					break;
				case '4':
					return 0;
				default:
					bzero(buf, sizeof(buf));strcpy(buf,"输入错误，请重新输入\n");send(sfd, buf, sizeof(buf), 0);
			}
			while(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			bzero(buf, sizeof(buf));strcpy(buf,"数据库修改成功!修改结束.\n");send(sfd, buf, sizeof(buf), 0);
			break;
		//退出
        case '3':
			sprintf(buf,"------Common user %s is disconnected------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			return 0;
		default:
			bzero(buf, sizeof(buf));strcpy(buf,"输入错误，请重新输入\n");send(sfd, buf, sizeof(buf), 0);
		}
	}
}