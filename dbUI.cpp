#include "wechat.h"

int dbUI()
{	
	char db_r[] = "���ݲ鿴";
	char db_n[] = "Navicat For MYSQL";
	char db_o[] = "����";
	loadimage(NULL,_T("IMAGE"),_T("back_1"));
	error();
	prompt();
	MOUSEMSG m;
	settextcolor(WHITE);					//����������ɫ
	setbkcolor(DARKGRAY);					//�������屳�����ɫ
	solidrectangle(50,  60, 160, 100);
	solidrectangle(50, 120, 230, 160);
	outtextxy(55, 65,  db_r);
	outtextxy(55, 125, db_n);
	//�˳���Ϣ	
	outInfo(db_o);
	int w = textwidth(db_o);		// ��ȡ�ַ���ռ�õ����ؿ�
	int h = textheight(db_o);		// ��ȡ�ַ���ռ�õ����ظ�
	FlushMouseMsgBuffer();			//��������Ϣ������
	while(1)
	{
		m = GetMouseMsg();					//�ж��Ƿ������
		//���ݲ鿴
		if(m.x >= 50 && m.x <= 160 && m.y >= 60 && m.y <= 100)
		{
			setlinecolor(GREEN);				// ѡ�п��������ɫ
			rectangle(45, 55, 165, 105);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				if( readDb() == 0)
					break;
				break;
			}
		}
		//��navicat for mysql
		else if(m.x >= 50 && m.x <= 240 && m.y >= 120 && m.y <= 160)
		{
			setlinecolor(GREEN);	
			rectangle( 45, 115, 245, 165);
			if( m.uMsg == WM_LBUTTONDOWN )
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				system(EXE_PATH);	
				break;
			}
		}
		//�˳����ݹ���,�ص����˵�
		else if(m.x >= 50 && m.x <= 55+w && m.y >= 300 && m.y <= 300+h)
		{
			setlinecolor(GREEN);		
			rectangle(45, 295, 60+w, 305+h);
			if(m.uMsg==WM_LBUTTONDOWN )
				break;
		}
		else
		{
			setlinecolor(DARKGRAY);
			rectangle(45,  55, 165, 105);	// ������
			rectangle(45, 115, 245, 165);
			rectangle(45, 295, 60+w, 305+h);
		}
	}  //end while
	return 1;
}
