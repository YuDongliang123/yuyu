#include "server.h"

sqlite3 *sqilte_init()
{
	sqlite3 *db = NULL;
	if (sqlite3_open("./staff", &db) != SQLITE_OK)
	{
		fprintf(stderr, "__%d__ code:%d sqlite3_open:%s\n", __LINE__,
				sqlite3_errcode(db), sqlite3_errmsg(db));
		return NULL;
	}
	char *errmsg = NULL;
	//创建表格
	//工号  用户类型	姓名	密码	年龄	电话	地址	职位	入职年月	等级	工资
	char sql[1024] = "create table if not exists member (number char,user char,name char,password char,\
	age char,phone_number char,address char,job char,year char,level char,money char)";
	while (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK);

	char sql_history[1024] = "create table if not exists history (time char,history char)";
	while (sqlite3_exec(db, sql_history, NULL, NULL, &errmsg) != SQLITE_OK);

	return db;
}
