#include "wechat.h"

int input(char * name,char *talk)
{
	char sqlcmd[600];
	if(is_file == 0){
	sprintf(sqlcmd, "INSERT INTO tbl_wechat(time,name,info) VALUES('%s','%s','%s')",sysTime(),name,talk);
	if( mysql_query(SQL.conn,sqlcmd) )
		{//如果执行失败
			RECT air={800,25,1000,430};
			drawtext(mysql_error(SQL.conn), &air,DT_WORDBREAK);
			promptInfo("按任意键返回");
			mysql_close(SQL.conn);
			getch();
			return 0;
		}
	return 1;
	}  //结束判断is_file
	if(is_file == 1)
		if( in_file(name,talk) == 0)
			return 0;
	return 1;
}

int in_file(char *name,char *talk)
{
	error();
	FILE *file;
	if( (file=fopen(FILE_PATH,"a+") ) == NULL)
	{
		errorInfo("文件打开失败!\n按任意键继续");
		return 0;
	}
	fprintf(file,"%s:%s\t%s\n",name,sysTime(),talk);
	fclose(file);
	return 1;
}

//取系统时间
char* sysTime()
{
	static char sysTime[20];   //定义为全局变量
	time_t rawtime;
	struct tm * timeinfo;	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sysTime,24,"%H:%M:%S",timeinfo); //格式化时间
	return sysTime;
}
