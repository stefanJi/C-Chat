#include "wechat.h"

int is_file;
int initInfo(UserInfo &A,SCO &S)
{
	error();
	prompt();
	is_file=0;
	//数据库连接参数
	SQL.host     = "localhost";
	SQL.username = "root";
	SQL.password = "jiyang110";
	SQL.dbname   = "wechat";
	SQL.port     = 3306;
	
	strcpy(A.clientName," ");
	strcpy(A.serverName," ");
	strcpy(A.talk_1," ");
	strcpy(A.talk_2," ");
	flag_1 = flag_2 =0;

	if(dbLink()==0)//连接数据库
	{
		errorInfo("数据库连接失败\n将转为文件读写模式\n按任意键继续");
		is_file = 1;
		getch();
		return 1;
	}
	if(initDb()==0 )//数据库信息初始化
			return 0;   //初始化失败
	return 1;
}

