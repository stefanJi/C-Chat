#include "wechat.h"

int input(char * name,char *talk)
{
	char sqlcmd[600];
	if(is_file == 0){
	sprintf(sqlcmd, "INSERT INTO tbl_wechat(time,name,info) VALUES('%s','%s','%s')",sysTime(),name,talk);
	if( mysql_query(SQL.conn,sqlcmd) )
		{//���ִ��ʧ��
			RECT air={800,25,1000,430};
			drawtext(mysql_error(SQL.conn), &air,DT_WORDBREAK);
			promptInfo("�����������");
			mysql_close(SQL.conn);
			getch();
			return 0;
		}
	return 1;
	}  //�����ж�is_file
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
		errorInfo("�ļ���ʧ��!\n�����������");
		return 0;
	}
	fprintf(file,"%s:%s\t%s\n",name,sysTime(),talk);
	fclose(file);
	return 1;
}

//ȡϵͳʱ��
char* sysTime()
{
	static char sysTime[20];   //����Ϊȫ�ֱ���
	time_t rawtime;
	struct tm * timeinfo;	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(sysTime,24,"%H:%M:%S",timeinfo); //��ʽ��ʱ��
	return sysTime;
}
