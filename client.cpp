#include "wechat.h"

HANDLE hThread_3;
DWORD dwThreadId_3;
SOCKET s;

int client(UserInfo &A,SCO &S)  
{  
	error();
	prompt();
	loadimage(NULL,_T("IMAGE"),_T("back_2"));
	int result=0;
	char ipAddress[20];     //保存输入的ip字符串
	in_addr ipAddr;			//ip地址结构体
	if (flag_2 == 0)
	{
	WSAStartup(MAKEWORD(2,2), &S.wsaData);                                     //初始化Windows Socket 2.2        
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                           //创建一个新的Socket来连接服务器    
	S.ServerAddr.sin_family = AF_INET;  
	S.ServerAddr.sin_port = htons(PORT);  

	if(InputBox((TCHAR *)ipAddress,20,"确定-->确认ip\n取消-->默认为本机局域网" , "输入服务器ip",NULL,50,50,false) == false )
			strcpy(ipAddress,"127.0.0.1");
	ipAddr.S_un.S_addr = inet_addr(ipAddress);							//将字符串转换为网络地址格式
	S.ServerAddr.sin_addr.s_addr = ipAddr.S_un.S_addr;					//填写要进行通信的服务器ip地址  
	
	if( (result = connect(s,(SOCKADDR *) &S.ServerAddr, sizeof(S.ServerAddr)) ) == SOCKET_ERROR )//向服务器发出连接请求 
	{	
		errorInfo("无法建立连接，请检查,按任意键返回"); 
		getch();
		return 0;
	}
	//连接成功
	flag_2 = 1;
	if(InputBox((TCHAR *)A.clientName,20,"确定-->确认昵称\n取消-->默认昵称为YiWa" , "输入昵称",NULL,50,50,false) == false )
				strcpy(A.clientName,"YiWa");
	char t[40]={"服务器连接成功，"};
	strcat(t,"按Esc键可后台运行");
	promptInfo(t);  //输出连接的ip地址
	hThread_3 = CreateThread(NULL,NULL,cliRecvMess,NULL,0,&dwThreadId_3); //消息同步接收线程
	} //end if(flag==0)
	//第二次进入直接跳到这里
	inputUI();
	promptInfo("按Esc键可后台运行");
	if(hThread_3!=NULL)
	{  
		int j =1;
		int y=30; //第一条消息输出纵坐标
		while(j)  
		{  
			if(InputBox((TCHAR*)A.talk_2,1024,"确定-->发送消息\n取消-->返回主界面,可以继续接受对方消息" , "输入聊天内容",NULL, 100, 100,false) == false)
				longjmp(jmpstar,1);  //返回主界面
			if(send(s,A.talk_2,sizeof(A.talk_2),0) == -1)  
			{
				errorInfo("发送出错!");
				getch();
				j=0;
				return 0;
				break;  
				}
				else  
				{	
					if(y >= 430 )
					{
						clearrectangle(210, 31, 800, 430);	//清空之前的信息
						error();
						prompt();
						loadimage(NULL,_T("IMAGE"),_T("back_2"));
						inputUI();
						y = 30;
					}
					setbkmode(TRANSPARENT);			//设置文字或图片的背景透明
					outtextxy(210,y,A.clientName);
					outtextxy(210+textwidth(A.clientName),y,":");
					outtextxy(210+textwidth(A.clientName)+textwidth(":"),y,A.talk_2);
					y+=20;
					outtextxy(210, y ,sysTime());
					input(A.clientName,A.talk_2);   //写入数据库
				}
				if(strcmp(A.talk_2,"886")==0)   
				{
					promptInfo("你已下线,按任意键继续");
					getch();
					break;
				}
				if(kbhit())
				{
					promptInfo("按Esc键可后台运行");
					if(27 ==  getch())
						longjmp(jmpstar,1);
				}
			y+=20;
			} //end while  
		}
	closesocket(s);  
	WSACleanup();  
	return 1;
}  


//客户端接收消息线程
DWORD WINAPI cliRecvMess(LPVOID cli)  
{  
	int recvbytes; 
	int j =1;
	char serverName[20];
	char talk_1[1024];
	recvbytes=recv(s,serverName,20,0); //接受服务器昵称
	settextcolor(LIGHTBLUE);
	int y = 31;
	while(j)  
	{  
		if((recvbytes=recv(s,talk_1,1024,0)) != -1)   
		{  
			if(y >= 430 )
			{
					clearrectangle(210, 31, 800, 430);	//清空之前的信息
					error();
					prompt();
					loadimage(NULL,"image\\3.bmp");
					inputUI();
					y = 30;
			}
			setbkmode(TRANSPARENT);			//设置文字或图片的背景透明
			RECT a={210,y,800,y+20};
			drawtext(serverName, &a, DT_RIGHT);			//右对齐输出冒号
			RECT b={210,y,800-textwidth(serverName),y+20};
			drawtext(":", &b,DT_RIGHT);	//右对齐输出昵称
			RECT c={210,y,800-textwidth(":")-textwidth(serverName),y+20};
			drawtext(talk_1, &c,DT_RIGHT);			//右对齐输出消息
			input(serverName,talk_1);				//写入数据库
			y+=20;
			RECT d={210,y,800,y+20};
			drawtext(sysTime(), &d, DT_RIGHT);		//右对齐输出时间
			if(strcmp(talk_1,"886")==0)    
			{
				promptInfo("对方已下线");
				j=0;  
			}
		}   
		y+=20;
		if(y >= 430 )
			clearrectangle(210, 31, 800, 430);	//清空之前的信息
	}  
	return 0;  
}   