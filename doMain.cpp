#include "wechat.h"

MY SQL;   //����Ϊȫ�ֱ���
jmp_buf jmpstar;
int flag_1,flag_2;
int main()
{

	UserInfo A; 
	SCO S;
	UI();		//����������
	void(*backStar)() = &UI;
	error();	//��������ʾ��
	loadimage(NULL,_T("IMAGE"),_T("back_3"));
	if(initInfo(A,S)==0 )  //��ʼ���������������ݿ�
	{
		errorInfo("��ʼ��ʧ��,��������˳���");
		getch();
		return 0;
	}
	if( choose(A,S) == 0 )//������ѡ�����	
	{
		errorInfo("����ѡ��������\n��������˳�");
		getch();
		return 0;
	}
	getch();
	return 0;
}