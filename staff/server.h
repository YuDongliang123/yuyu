#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sqlite3.h>
#include <sys/select.h>

#define ERR_MSG(msg) do{\
	fprintf(stderr, "__%d__:", __LINE__);\
	perror(msg);\
}while(0)

#define PORT 8888 				//1024~49151
#define IP 	"192.168.250.100" 		//本机IP，ifconfig查找

static char *errmsg = NULL;
static char **dbResult;
static int row = 0, col = 0;

static char buf[1024] = "";
static char sql[1024] = "";
static int ret;
static int res;
static char choose;

struct people{
	char number[6];
	char user[10];
	char name[10];
	char password[6];
	char age[5];
	char phone_number[15];
	char address[30];
	char job[30];
	char year[15];
	char level[5];
	char money[10];
};
struct people people_t;

sqlite3* sqilte_init();
void server_start(sqlite3 *db,int sfd);
int server_user_root(sqlite3 *db,int sfd);
int server_user_common(sqlite3 *db,int sfd);
int rcv_cli_msg(int newfd, struct sockaddr_in);

#endif