#include "wechat.h"

int dbLink()
{
	error();
	if( 
		(SQL.conn=mysql_init((MYSQL *)0))
		&&
		(mysql_options(SQL.conn,MYSQL_SET_CHARSET_NAME,"gbk")==0)
		&&
		mysql_real_connect(SQL.conn,SQL.host,SQL.username,SQL.password,SQL.dbname,SQL.port,NULL,0)
	  )//���ӳɹ�
	  return 1;
	else //****����ʧ��******
		{
			RECT air={810,25,1000,430};
			drawtext(mysql_error(SQL.conn), &air,DT_WORDBREAK);
			promptInfo("�����������");
			mysql_close(SQL.conn);
			getch();
			return 0; //����ʧ�ܷ���0
		}
}