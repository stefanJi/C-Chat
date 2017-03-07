#include "wechat.h"

int readDb()
{
	error();
	prompt();
	MYSQL_RES *res;
	MYSQL_ROW row;
	char sqlcmd[600];   //mysql命令语句
	loadimage(NULL,_T("IMAGE"),_T("back_1"));
	RECT air={800,0,1000,450};
	if(is_file== 0){
	strcpy(sqlcmd,"SELECT * FROM `tbl_wechat` ");
	//马上把值读出来
	if( mysql_query(SQL.conn,sqlcmd) )
	{//如果读取失败
		RECT air={800,25,1000,430};
		drawtext(mysql_error(SQL.conn), &air,DT_WORDBREAK);
		promptInfo("按任意键返回");
		getch();
		mysql_close(SQL.conn);
		return 0;
	}else
	{//如果读取成功
		res=mysql_store_result(SQL.conn);   //取结果集到res中
		int y=40;
		settextstyle(20, 0, _T("幼圆"));	//字体样式大小
		settextcolor(WHITE);				//字体颜色
		setbkmode(TRANSPARENT);				//设置文字或图片的背景透明
		outtextxy(100,y,"时间"); 
		outtextxy(190,y,"昵称"); 
		outtextxy(260,y,"消息");  
		setlinecolor(WHITE);
		line(98,39,1000,39);		// 画水平线
		line(98,62,1000,62);	
		line(100,430,1000,430);		
		line(98,40,98,430);			// 画竖直线
		line(185,40,185,430);		
		line(250,40,250,430);				
		line(1000,40,1000,430);		
		y=65;
		while( (row=mysql_fetch_row(res) )!= NULL )
			{
				settextcolor(WHITE);			//字体颜色
				setbkmode(TRANSPARENT);			//设置文字或图片的背景透明
				outtextxy(100,y,row[1]);	//时间
				outtextxy(190,y,row[2]);	//昵称
				outtextxy(260,y,row[3]);	//消息
				y+=20;
				if(y >= 420)
				{
					promptInfo("消息记录超过了屏幕，本页将会被清空,按 d/D键 查看下一页");
					char a=getch();
					switch( a )
					{
					case 'd':case 'D':
						{
							 
						clearrectangle(100, 62, 1000, 430);		//清空之前的消息
						loadimage(NULL,_T("IMAGE"),_T("back_1"));
						setlinecolor(WHITE);
						outtextxy(100,40,"时间"); 
						outtextxy(190,40,"昵称"); 
						outtextxy(260,40,"消息");  
						line(98,39,1000,39);		// 画水平线
						line(98,62,1000,62);	
						line(100,430,1000,430);		
						line(98,40,98,430);			// 画竖直线
						line(185,40,185,430);		
						line(250,40,250,430);				
						line(1000,40,1000,430);	
						y=65;
						break; }
					default: 
						promptInfo("按键错误，请重新按键：d/D 键"),Sleep(1000); 
					} //退出switch
				}  // 退出if
		}  //退出while
		mysql_free_result(res);//释放结果集
		promptInfo("信息已展示完，按任意键返回");
		getch();
	}
	}//结束is_file判断
	if(is_file == 1)
		if( re_file() == 0)
			return 0;
	return 1;
}


int re_file()
{
	error();
	prompt();
	system(FILE_PATH);
	promptInfo("信息已展示完，按任意键返回");
	getch();
	return 1;
}