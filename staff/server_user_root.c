#include "server.h"

int server_user_root(sqlite3 *db,int sfd)
{
	int temp;
	char is;
	while(1)
	{
		res = recv(sfd, &choose, sizeof(choose), 0);
		switch(choose)
		{
		//查看
		case '1':
			sprintf(sql,"select * from member;");
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
		//修改用户信息
		case '2':
			sprintf(buf,"------Admin %s tried to modify------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

			res = recv(sfd, people_t.number, sizeof(people_t.number), 0);
			res = recv(sfd, &temp, sizeof(temp), 0);
			switch(temp)
			{
				case 1:
					res = recv(sfd, people_t.name, sizeof(people_t.name), 0);
					sprintf(buf,"------Number %s name %s changed------\n",people_t.number,people_t.name);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set name=\"%s\" where number=\"%s\";",people_t.name,people_t.number);
					break;
				case 2:
					res = recv(sfd, people_t.age, sizeof(people_t.age), 0);
					sprintf(buf,"------Number %s age %s changed------\n",people_t.number,people_t.age);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set age=\"%s\" where number=\"%s\";",people_t.age,people_t.number);
					break;
				case 3:
					res = recv(sfd, people_t.address, sizeof(people_t.address), 0);
					sprintf(buf,"------Number %s address %s changed------\n",people_t.number,people_t.address);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set address=\"%s\" where number=\"%s\";",people_t.address,people_t.number);
					break;
				case 4:
					res = recv(sfd, people_t.phone_number, sizeof(people_t.phone_number), 0);
					sprintf(buf,"------Number %s phone_number %s changed------\n",people_t.number,people_t.phone_number);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set phone_number=\"%s\" where number=\"%s\";",people_t.phone_number,people_t.number);
					break;
				case 5:
					res = recv(sfd, people_t.job, sizeof(people_t.job), 0);
					sprintf(buf,"------Number %s job %s changed------\n",people_t.number,people_t.job);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set job=\"%s\" where number=\"%s\";",people_t.job,people_t.number);
					break;
				case 6:
					res = recv(sfd, people_t.money, sizeof(people_t.money), 0);
					sprintf(buf,"------Number %s money %s changed------\n",people_t.number,people_t.money);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set money=\"%s\" where number=\"%s\";",people_t.money,people_t.number);
					break;
				case 7:
					res = recv(sfd, people_t.year, sizeof(people_t.year), 0);
					sprintf(buf,"------Number %s year %s changed------\n",people_t.number,people_t.year);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set year=\"%s\" where number=\"%s\";",people_t.year,people_t.number);
					break;
				case 8:
					res = recv(sfd, people_t.level, sizeof(people_t.level), 0);
					sprintf(buf,"------Number %s level %s changed------\n",people_t.number,people_t.level);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set level=\"%s\" where number=\"%s\";",people_t.level,people_t.number);
					break;
				case 9:
					res = recv(sfd, people_t.password, sizeof(people_t.password), 0);
					sprintf(buf,"------Number %s password %s changed------\n",people_t.number,people_t.password);
					printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
					if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

					sprintf(sql,"update member set password=\"%s\" where number=\"%s\";",people_t.password,people_t.number);
					break;
				case 10:
					continue;
				default:
					bzero(buf, sizeof(buf));strcpy(buf,"输入错误，请重新输入\n");send(sfd, buf, sizeof(buf), 0);
			}
			while(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			bzero(buf, sizeof(buf));strcpy(buf,"数据库修改成功!修改结束.\n");send(sfd, buf, sizeof(buf), 0);
			break;
		//添加用户
        case '3':
			sprintf(buf,"------Admin %s add users------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

			//接收员工结构体信息
			res = recv(sfd, &people_t, sizeof(people_t), 0);

			sprintf(sql,"insert into member values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");",\
			people_t.number,people_t.user,people_t.name,people_t.password,people_t.age,\
			people_t.phone_number,people_t.address,people_t.job,people_t.year,people_t.level,people_t.money);
			while(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

			res = recv(sfd, &is, sizeof(is), 0);
			if(is == 'Y' | is == 'y') {
				continue;
			}
			else {
				break;
			}
		//删除用户
        case '4':
			res = recv(sfd, people_t.number, sizeof(people_t.number), 0);
			res = recv(sfd, people_t.name, sizeof(people_t.name), 0);
			sprintf(sql,"delete from member where number=\"%s\" and name= \"%s\";",people_t.number,people_t.name);
			ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);

			sprintf(buf,"------The administrator delete user %s------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			res = recv(sfd, &is, sizeof(is), 0);
			if(is == 'Y' | is == 'y') {
				continue;
			}
			break;
		//查看历史记录
        case '5':
			sprintf(sql,"insert into history values (select datetime(now),\"%s\");",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

			strcpy(sql,"select * from history;");
			ret = sqlite3_get_table(db, sql, &dbResult, &row, &col, &errmsg);
			bzero(buf, sizeof(buf));
			for(int i=1;i<=row;i++) {
				for(int j=0;j<col;j++) {
					strcat(buf,dbResult[2*i + j]);
					strcat(buf,"  ");
				}
				strcat(buf,"\n");
			}
			send(sfd, buf, sizeof(buf), 0);
			sqlite3_free_table(dbResult);
			break;
		//退出
		case '6':
			sprintf(buf,"------Admin user %s is disconnected------\n",people_t.name);
			printf("%s",buf);sprintf(sql,"insert into history values (datetime('now','localtime'),'%s');",buf);
			if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);
			return 0;
		default:
			bzero(buf, sizeof(buf));strcpy(buf,"输入错误，请重新输入\n");send(sfd, buf, sizeof(buf), 0);
		}
	}
}