#include "wechat.h"
// �����ʼ��
void UI()
{
	initgraph(1024, 450);				//���ڳ�ʼ����С
	setbkcolor(DARKGRAY);				//���ñ�����ɫ
	cleardevice();
	setlinecolor(BLACK);				//���û�ͼ��ɫ
	settextcolor(WHITE);				//����������ɫ
	setfillcolor(DARKGRAY);				//���������ɫ
	settextstyle(20, 0, _T("��Բ"));	//������ʽ��С

}
//����ѡ�����
int choose(UserInfo &A,SCO &S)
{
	if( setjmp(jmpstar) != 0 )
		choose(A,S);
	cleardevice();
	loadimage(NULL,_T("IMAGE"),_T("back_3"));
	error();
	prompt();
	setfillcolor(DARKGRAY);				// ���������ɫ
	settextcolor(BLACK);				// ����������ɫ
	setfillstyle(BS_SOLID);		//�������ģʽΪ��ʵ���
	char *s_ser,*s_cli;
	if(flag_1 == 0)
		s_ser	= "����������";
	else
		s_ser	= "��������";
	if(flag_2 == 0)
		s_cli	= "�����ͻ���";
	else
		s_cli	= "��������";
	char s_dbm[]    = "-���ݹ���-";
	char s_out[]	= "�˳�����";
	char s_info[]	= "*****ʹ����������ܼ���*****";
	MOUSEMSG m;
	//��ʼ��
	draw3_rectangle(s_ser,s_cli,s_dbm);
	//֪ͨ��Ϣ
	setfillcolor(DARKGRAY);
	solidrectangle(0, 400, 1024, 450);
	outtextxy(365, 410, s_info);
	//�˳���Ϣ
	outInfo(s_out);
	int w = textwidth(s_out);		//��ȡ�ַ���ռ�õ����ؿ�
	int h = textheight(s_out);		//��ȡ�ַ���ռ�õ����ظ�
	while(1)
	{
		m = GetMouseMsg();				//�ж��Ƿ������
		//����������
		if(m.x >= 50 && m.x <= 160 && m.y >= 60 && m.y <= 100)
		{
			setlinecolor(WHITE);				//ѡ�п��������ɫ
			rectangle(45, 55, 165, 105);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				if( server(A,S) ==0)
				{	
					errorInfo("����������ʧ��,�����������");
					getch();
					longjmp(jmpstar,1);
				}
				if(server(A,S) ==1)
					longjmp(jmpstar,1);
			}
		}
		//�����ͻ���
		else if(m.x >= 50 && m.x <= 160 && m.y >= 120 && m.y <= 160)
		{
			setlinecolor(WHITE);	
			rectangle( 45, 115, 165, 165);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				if( client(A,S) ==0)
				{	
					errorInfo("�ͻ��˽���ʧ��,�����������");
					getch();
					longjmp(jmpstar,1);
				}
			}
		}
		//���ݹ���
		else if(m.x >= 50 && m.x <= 160 && m.y >= 180 && m.y <= 220)
		{
			setlinecolor(WHITE);			
			rectangle( 45, 175, 165, 225);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				dbUI();
				longjmp(jmpstar,1);
			}
		}
		//�˳�����
		else if(m.x >= 50 && m.x <= 55+w && m.y >= 300 && m.y <= 300+h)
		{
			setlinecolor(WHITE);		
			rectangle(45, 295, 60+w, 305+h);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				closegraph();
				mysql_close(SQL.conn);
				break;
			}
		}
		else
			rect3_angle(w,h);
	}//end while
	return 1;
}

//��3�����ܾ���
void draw3_rectangle(char *a,char *b,char *c)
{
	//���ܾ���
	solidrectangle(50,  60, 160, 100);
	solidrectangle(50, 120, 160, 160);
	solidrectangle(50, 180, 160, 220);
	settextcolor(WHITE);					//����������ɫ
	setbkcolor(DARKGRAY);					//�������屳�����ɫ
	//������Ϣ
	outtextxy(55, 65,  a);
	outtextxy(55, 125, b);
	outtextxy(55, 185, c);
}
//��2�����ܾ���
void draw2_rectangle(char *a,char *b)
{
	//���ܾ���
	solidrectangle(50,  60, 160, 100);
	solidrectangle(50, 120, 160, 160);
	settextcolor(WHITE);					//����������ɫ
	setbkcolor(DARKGRAY);					//�������屳�����ɫ
	//������Ϣ
	outtextxy(55, 65,  a);
	outtextxy(55, 125, b);
}
void draw1_rectangle(char *a)
{
	solidrectangle(50,  60, 160, 100);
	settextcolor(WHITE);					//����������ɫ
	setbkcolor(DARKGRAY);					//�������屳�����ɫ
	//������Ϣ
	outtextxy(55, 65,  a);
}
//���˳���Ϣ
void outInfo(char *a)
{
	//�˳���Ϣ	
	settextcolor(WHITE);
	setbkcolor(DARKGRAY);
	outtextxy(50, 300, a);
}

//���3������
void clear3_rectangl()
{
	clearrectangle(50,  60, 160, 100);
	clearrectangle(50, 120, 240, 160);
	clearrectangle(50, 180, 160, 220);
}

//��3��ѡ���
void rect3_angle(int w,int h)
{
	setlinecolor(RED);
	rectangle(45,  55, 165, 105);	// ������
	rectangle(45, 115, 165, 165);
	rectangle(45, 175, 165, 225);
	rectangle(45, 295, 60+w, 305+h); //����
}
//���ı������
void inputUI()
{
	setlinecolor(BLUE);
	rectangle(200, 30, 800, 430);
}
//��������ʾ��
void error()
{
	settextcolor(YELLOW);
	rectangle(810,20,1000,430);
	setbkcolor(DARKGRAY);	
	outtextxy(810,0,"*������ʾ*");
}
//����Ϣ��ʾ��
void prompt()
{
	settextcolor(YELLOW);
	line(220,20,800,20);		//��ˮƽ��
	setbkcolor(DARKGRAY);	
	outtextxy(150,0,"*��ʾ-->");
}

//��ӡ������Ϣ
void errorInfo(char *a)
{
	clearrectangle(810,25,1000,430);	//���֮ǰ�Ĵ���
	settextcolor(YELLOW);
	setfillcolor(DARKGRAY);		
	RECT air={810,25,1000,430};
	drawtext(a, &air,DT_WORDBREAK);	
}
//��ӡ��ʾ��Ϣ
void promptInfo(char *a)
{
	clearrectangle(220,0,800,20);	//���֮ǰ����ʾ
	settextcolor(YELLOW);
	setfillcolor(DARKGRAY);	
	RECT air={220,0,800,20};
	drawtext(a, &air,DT_WORDBREAK);	
}