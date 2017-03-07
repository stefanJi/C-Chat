#include "wechat.h"

int dbUI()
{	
	char db_r[] = "数据查看";
	char db_n[] = "Navicat For MYSQL";
	char db_o[] = "返回";
	loadimage(NULL,_T("IMAGE"),_T("back_1"));
	error();
	prompt();
	MOUSEMSG m;
	settextcolor(WHITE);					//设置字体颜色
	setbkcolor(DARKGRAY);					//设置字体背景填充色
	solidrectangle(50,  60, 160, 100);
	solidrectangle(50, 120, 230, 160);
	outtextxy(55, 65,  db_r);
	outtextxy(55, 125, db_n);
	//退出信息	
	outInfo(db_o);
	int w = textwidth(db_o);		// 获取字符串占用的像素宽
	int h = textheight(db_o);		// 获取字符串占用的像素高
	FlushMouseMsgBuffer();			//清空鼠标消息缓冲区
	while(1)
	{
		m = GetMouseMsg();					//判断是否按下鼠标
		//数据查看
		if(m.x >= 50 && m.x <= 160 && m.y >= 60 && m.y <= 100)
		{
			setlinecolor(GREEN);				// 选中框框线条颜色
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
		//打开navicat for mysql
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
		//退出数据管理,回到主菜单
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
			rectangle(45,  55, 165, 105);	// 画矩形
			rectangle(45, 115, 245, 165);
			rectangle(45, 295, 60+w, 305+h);
		}
	}  //end while
	return 1;
}
