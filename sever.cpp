#include "wechat.h"

HANDLE hThread_1,hThread_2;  
DWORD dwThreadId_1,dwThreadId_2;
SOCKET  NewConnection;		//定义一个SOCKET连接
SOCKET	ListeningSocket;

int serLink(SCO &S)
{
	error();
	RECT air={0,0,1024,400};  //区域指针
	//服务器网络参数初始化
	WSAStartup(MAKEWORD(2,2), &S.wsaData); //初始化Windows Socket 2.2  
	S.ServerAddr.sin_family = AF_INET;     //填写服务器地址信息 
	S.ServerAddr.sin_port = htons(PORT);   //填写服务器端口信息  
	S.ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//绑定监听端口(当调用socket函数创建套接字后)

	memset((void *)&S.ClientAddr.sin_addr,0,sizeof(S.ClientAddr.sin_addr)); //初始化客户端ip为0
 
	if( (ListeningSocket = socket(AF_INET,SOCK_STREAM,0))==-1 //创建一个新的Socket来响应客户端的连接请求
		|| //或
		bind(ListeningSocket,(SOCKADDR *)&S.ServerAddr,sizeof(S.ServerAddr))==-1 //将本机地址和端口等信息与客户端套接字相连
		)
	{
		errorInfo("初始化scoket失败\n按任意键继续");
		getch();
		return 0;  //初始化scoket失败，就返回0
	}
	//开始监听,指定最大同时连接数为CLIENT_MAX
	if( listen(ListeningSocket,CLIENT_MAX))
	{
		errorInfo("监听错误\n按任意键继续");
		getch();
		return 0;
	}
	return 1;
}

int server(UserInfo &A,SCO &S) 
{  
	loadimage(NULL,_T("IMAGE"),_T("back_2"));
	error();
	prompt();
	int len = sizeof(S.ClientAddr);
	if(flag_1 == 0)
	{
		if(serLink(S) == 0)		//建立scoket网络服务，并建立监听INVALID_SOCKET
				return 0;		//建立失败就返回
		promptInfo("…等待连接…");
		NewConnection = accept(ListeningSocket, (SOCKADDR *) &S.ClientAddr,&len);//等待连接
		char t[40]={"新连接已建立:"};
		strcat(t,inet_ntoa(S.ClientAddr.sin_addr));
		strcat(t,"按Esc键可后台运行");
		flag_1 = 1;
		promptInfo(t);  //输出新连接的ip地址
		if(InputBox((TCHAR *)A.serverName,20,"确定-->确认昵称\n取消-->默认昵称为WaLi" , "输入昵称",NULL,50,50,false) == false )
			strcpy(A.serverName,"Wali");
		hThread_2=CreateThread(NULL,NULL,recvMessage,NULL,0,&dwThreadId_2); //建立接受消息同步线程 hThread_2
	}
		inputUI(); //画文本输入框
		int y=30; //第一条消息输出纵坐标
		if( hThread_2 != NULL)
		{  
			int j =1;
			while(j)  
			{  
				if(InputBox((TCHAR*)A.talk_1,1024,"确定-->发送消息\n取消-->返回主界面,后台运行" , "输入聊天内容",NULL, 100, 100,false) == false)
					longjmp(jmpstar,1);  //返回2，代表返回主菜单
				if(send(NewConnection,A.talk_1,sizeof(A.talk_1),0) == -1)  
				{
					errorInfo("发送出错!");
					getch();
					j=0;
					break;
				}
				else  
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
					outtextxy(210,y,A.serverName);
					outtextxy(210+textwidth(A.serverName),y,":");
					outtextxy(210+textwidth(A.serverName)+textwidth(":"),y,A.talk_1);
					y+=20;
					outtextxy(210, y ,sysTime());
					input(A.serverName,A.talk_1);  //写入数据库
				}
				if(strcmp(A.talk_1,"886")==0)   
				{
					promptInfo("你已下线，按任意键返回");
					j=0;
					getch();
					closesocket(NewConnection);		//关闭连接  
					closesocket(ListeningSocket);	//并关闭监听Socket  
					WSACleanup();					//释放Windows Socket DLL的相关资源  
					longjmp(jmpstar,1);  //返回主菜单
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
		CloseHandle(hThread_2);
		CloseHandle(hThread_1);
		closesocket(NewConnection);		//关闭连接  
		closesocket(ListeningSocket);	//并关闭监听Socket  
		WSACleanup();					//释放Windows Socket DLL的相关资源  
		return 1;
}


//服务器接受消息线程hThread_2
DWORD WINAPI recvMessage(LPVOID rev)
{  
	int recvbytes;
	int i=1;
	char clientName[20];
	char talk_2[1024];
	
	recvbytes=recv(NewConnection,clientName,20,0);  //接收客户端昵称
	settextcolor(LIGHTBLUE);
	int y = 30;
	while(i)  
	{  
		if((recvbytes=recv(NewConnection,talk_2,1024,0)) != -1)   
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
			drawtext(clientName, &a, DT_RIGHT);			//右对齐输出冒号
			RECT b={210,y,800-textwidth(clientName),y+20};
			drawtext(":", &b,DT_RIGHT);	//右对齐输出昵称
			RECT c={210,y,800-textwidth(":")-textwidth(clientName),y+20};
			drawtext(talk_2, &c,DT_RIGHT);			//右对齐输出消息
			input(clientName,talk_2);				//写入数据库
			y+=20;
			RECT d={210,y,800,y+20};
			drawtext(sysTime(), &d, DT_RIGHT);		//右对齐输出时间
			if(strcmp(talk_2,"886")==0)    
			{
				promptInfo("对方已下线");
				getch();
				break;
			}
		}   
		y+=20;
	}  
	return 0;  
}   