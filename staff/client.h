#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sqlite3.h>

#define ERR_MSG(msg) do{\
	fprintf(stderr, "__%d__:", __LINE__);\
	perror(msg);\
}while(0)

#define PORT 8888
#define IP 	"192.168.250.100" 

static char *errmsg = NULL;
static char **dbResult;
static int row = 0, col = 0;

static char sql[1024] = "";
static char buf[1024] = "";
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
void client_start(int sfd);
int client_user_root(int sfd);
int client_user_common(int sfd);
#endif