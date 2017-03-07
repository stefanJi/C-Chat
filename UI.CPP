#include "wechat.h"
// 界面初始化
void UI()
{
	initgraph(1024, 450);				//窗口初始化大小
	setbkcolor(DARKGRAY);				//设置背景颜色
	cleardevice();
	setlinecolor(BLACK);				//设置绘图颜色
	settextcolor(WHITE);				//设置文字颜色
	setfillcolor(DARKGRAY);				//设置填充颜色
	settextstyle(20, 0, _T("幼圆"));	//字体样式大小

}
//功能选择界面
int choose(UserInfo &A,SCO &S)
{
	if( setjmp(jmpstar) != 0 )
		choose(A,S);
	cleardevice();
	loadimage(NULL,_T("IMAGE"),_T("back_3"));
	error();
	prompt();
	setfillcolor(DARKGRAY);				// 设置填充颜色
	settextcolor(BLACK);				// 设置文字颜色
	setfillstyle(BS_SOLID);		//设置填充模式为固实填充
	char *s_ser,*s_cli;
	if(flag_1 == 0)
		s_ser	= "建立服务器";
	else
		s_ser	= "继续聊天";
	if(flag_2 == 0)
		s_cli	= "建立客户端";
	else
		s_cli	= "继续聊天";
	char s_dbm[]    = "-数据管理-";
	char s_out[]	= "退出程序";
	char s_info[]	= "*****使用鼠标点击功能即可*****";
	MOUSEMSG m;
	//初始化
	draw3_rectangle(s_ser,s_cli,s_dbm);
	//通知信息
	setfillcolor(DARKGRAY);
	solidrectangle(0, 400, 1024, 450);
	outtextxy(365, 410, s_info);
	//退出信息
	outInfo(s_out);
	int w = textwidth(s_out);		//获取字符串占用的像素宽
	int h = textheight(s_out);		//获取字符串占用的像素高
	while(1)
	{
		m = GetMouseMsg();				//判断是否按下鼠标
		//建立服务器
		if(m.x >= 50 && m.x <= 160 && m.y >= 60 && m.y <= 100)
		{
			setlinecolor(WHITE);				//选中框框线条颜色
			rectangle(45, 55, 165, 105);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clear3_rectangl();
				setbkcolor(WHITE);
				cleardevice();
				if( server(A,S) ==0)
				{	
					errorInfo("服务器建立失败,按任意键返回");
					getch();
					longjmp(jmpstar,1);
				}
				if(server(A,S) ==1)
					longjmp(jmpstar,1);
			}
		}
		//建立客户端
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
					errorInfo("客户端建立失败,按任意键返回");
					getch();
					longjmp(jmpstar,1);
				}
			}
		}
		//数据管理
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
		//退出程序
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

//画3个功能矩形
void draw3_rectangle(char *a,char *b,char *c)
{
	//功能矩形
	solidrectangle(50,  60, 160, 100);
	solidrectangle(50, 120, 160, 160);
	solidrectangle(50, 180, 160, 220);
	settextcolor(WHITE);					//设置字体颜色
	setbkcolor(DARKGRAY);					//设置字体背景填充色
	//功能信息
	outtextxy(55, 65,  a);
	outtextxy(55, 125, b);
	outtextxy(55, 185, c);
}
//画2个功能矩形
void draw2_rectangle(char *a,char *b)
{
	//功能矩形
	solidrectangle(50,  60, 160, 100);
	solidrectangle(50, 120, 160, 160);
	settextcolor(WHITE);					//设置字体颜色
	setbkcolor(DARKGRAY);					//设置字体背景填充色
	//功能信息
	outtextxy(55, 65,  a);
	outtextxy(55, 125, b);
}
void draw1_rectangle(char *a)
{
	solidrectangle(50,  60, 160, 100);
	settextcolor(WHITE);					//设置字体颜色
	setbkcolor(DARKGRAY);					//设置字体背景填充色
	//功能信息
	outtextxy(55, 65,  a);
}
//画退出信息
void outInfo(char *a)
{
	//退出信息	
	settextcolor(WHITE);
	setbkcolor(DARKGRAY);
	outtextxy(50, 300, a);
}

//清除3个矩形
void clear3_rectangl()
{
	clearrectangle(50,  60, 160, 100);
	clearrectangle(50, 120, 240, 160);
	clearrectangle(50, 180, 160, 220);
}

//画3个选择框
void rect3_angle(int w,int h)
{
	setlinecolor(RED);
	rectangle(45,  55, 165, 105);	// 画矩形
	rectangle(45, 115, 165, 165);
	rectangle(45, 175, 165, 225);
	rectangle(45, 295, 60+w, 305+h); //返回
}
//画文本输入框
void inputUI()
{
	setlinecolor(BLUE);
	rectangle(200, 30, 800, 430);
}
//画错误提示区
void error()
{
	settextcolor(YELLOW);
	rectangle(810,20,1000,430);
	setbkcolor(DARKGRAY);	
	outtextxy(810,0,"*错误提示*");
}
//画信息提示区
void prompt()
{
	settextcolor(YELLOW);
	line(220,20,800,20);		//画水平线
	setbkcolor(DARKGRAY);	
	outtextxy(150,0,"*提示-->");
}

//打印错误信息
void errorInfo(char *a)
{
	clearrectangle(810,25,1000,430);	//清空之前的错误
	settextcolor(YELLOW);
	setfillcolor(DARKGRAY);		
	RECT air={810,25,1000,430};
	drawtext(a, &air,DT_WORDBREAK);	
}
//打印提示信息
void promptInfo(char *a)
{
	clearrectangle(220,0,800,20);	//清空之前的提示
	settextcolor(YELLOW);
	setfillcolor(DARKGRAY);	
	RECT air={220,0,800,20};
	drawtext(a, &air,DT_WORDBREAK);	
}
