#include "wechat.h"

int is_file;
int initInfo(UserInfo &A,SCO &S)
{
	error();
	prompt();
	is_file=0;
	//���ݿ����Ӳ���
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

	if(dbLink()==0)//�������ݿ�
	{
		errorInfo("���ݿ�����ʧ��\n��תΪ�ļ���дģʽ\n�����������");
		is_file = 1;
		getch();
		return 1;
	}
	if(initDb()==0 )//���ݿ���Ϣ��ʼ��
			return 0;   //��ʼ��ʧ��
	return 1;
}

