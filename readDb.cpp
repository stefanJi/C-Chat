#include "wechat.h"

int readDb()
{
	error();
	prompt();
	MYSQL_RES *res;
	MYSQL_ROW row;
	char sqlcmd[600];   //mysql�������
	loadimage(NULL,_T("IMAGE"),_T("back_1"));
	RECT air={800,0,1000,450};
	if(is_file== 0){
	strcpy(sqlcmd,"SELECT * FROM `tbl_wechat` ");
	//���ϰ�ֵ������
	if( mysql_query(SQL.conn,sqlcmd) )
	{//�����ȡʧ��
		RECT air={800,25,1000,430};
		drawtext(mysql_error(SQL.conn), &air,DT_WORDBREAK);
		promptInfo("�����������");
		getch();
		mysql_close(SQL.conn);
		return 0;
	}else
	{//�����ȡ�ɹ�
		res=mysql_store_result(SQL.conn);   //ȡ�������res��
		int y=40;
		settextstyle(20, 0, _T("��Բ"));	//������ʽ��С
		settextcolor(WHITE);				//������ɫ
		setbkmode(TRANSPARENT);				//�������ֻ�ͼƬ�ı���͸��
		outtextxy(100,y,"ʱ��"); 
		outtextxy(190,y,"�ǳ�"); 
		outtextxy(260,y,"��Ϣ");  
		setlinecolor(WHITE);
		line(98,39,1000,39);		// ��ˮƽ��
		line(98,62,1000,62);	
		line(100,430,1000,430);		
		line(98,40,98,430);			// ����ֱ��
		line(185,40,185,430);		
		line(250,40,250,430);				
		line(1000,40,1000,430);		
		y=65;
		while( (row=mysql_fetch_row(res) )!= NULL )
			{
				settextcolor(WHITE);			//������ɫ
				setbkmode(TRANSPARENT);			//�������ֻ�ͼƬ�ı���͸��
				outtextxy(100,y,row[1]);	//ʱ��
				outtextxy(190,y,row[2]);	//�ǳ�
				outtextxy(260,y,row[3]);	//��Ϣ
				y+=20;
				if(y >= 420)
				{
					promptInfo("��Ϣ��¼��������Ļ����ҳ���ᱻ���,�� d/D�� �鿴��һҳ");
					char a=getch();
					switch( a )
					{
					case 'd':case 'D':
						{
							 
						clearrectangle(100, 62, 1000, 430);		//���֮ǰ����Ϣ
						loadimage(NULL,_T("IMAGE"),_T("back_1"));
						setlinecolor(WHITE);
						outtextxy(100,40,"ʱ��"); 
						outtextxy(190,40,"�ǳ�"); 
						outtextxy(260,40,"��Ϣ");  
						line(98,39,1000,39);		// ��ˮƽ��
						line(98,62,1000,62);	
						line(100,430,1000,430);		
						line(98,40,98,430);			// ����ֱ��
						line(185,40,185,430);		
						line(250,40,250,430);				
						line(1000,40,1000,430);	
						y=65;
						break; }
					default: 
						promptInfo("�������������°�����d/D ��"),Sleep(1000); 
					} //�˳�switch
				}  // �˳�if
		}  //�˳�while
		mysql_free_result(res);//�ͷŽ����
		promptInfo("��Ϣ��չʾ�꣬�����������");
		getch();
	}
	}//����is_file�ж�
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
	promptInfo("��Ϣ��չʾ�꣬�����������");
	getch();
	return 1;
}