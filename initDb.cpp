#include "wechat.h"

int initDb()
{
	error();
	char sqlcmd[600];   //mysql�������
	strcpy(sqlcmd, "ALTER TABLE `tbl_wechat` AUTO_INCREMENT =1");
	mysql_query(SQL.conn,sqlcmd);		//mysql����������
	
	sprintf(sqlcmd,"INSERT INTO tbl_wechat(time,name,info) VALUES('%s','%s','%s')",sysTime()," "," ");
	if( mysql_query(SQL.conn,sqlcmd))
	{//���ִ��ʧ��
		RECT air={800,25,1000,430};
		drawtext(mysql_error(SQL.conn), &air,DT_WORDBREAK);
		promptInfo("�����������");
		mysql_close(SQL.conn);
		getch();
		return 0;
	}
	return 1;
}


