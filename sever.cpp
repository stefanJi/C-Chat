#include "wechat.h"

HANDLE hThread_1,hThread_2;  
DWORD dwThreadId_1,dwThreadId_2;
SOCKET  NewConnection;		//����һ��SOCKET����
SOCKET	ListeningSocket;

int serLink(SCO &S)
{
	error();
	RECT air={0,0,1024,400};  //����ָ��
	//���������������ʼ��
	WSAStartup(MAKEWORD(2,2), &S.wsaData); //��ʼ��Windows Socket 2.2  
	S.ServerAddr.sin_family = AF_INET;     //��д��������ַ��Ϣ 
	S.ServerAddr.sin_port = htons(PORT);   //��д�������˿���Ϣ  
	S.ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//�󶨼����˿�(������socket���������׽��ֺ�)

	memset((void *)&S.ClientAddr.sin_addr,0,sizeof(S.ClientAddr.sin_addr)); //��ʼ���ͻ���ipΪ0
 
	if( (ListeningSocket = socket(AF_INET,SOCK_STREAM,0))==-1 //����һ���µ�Socket����Ӧ�ͻ��˵���������
		|| //��
		bind(ListeningSocket,(SOCKADDR *)&S.ServerAddr,sizeof(S.ServerAddr))==-1 //��������ַ�Ͷ˿ڵ���Ϣ��ͻ����׽�������
		)
	{
		errorInfo("��ʼ��scoketʧ��\n�����������");
		getch();
		return 0;  //��ʼ��scoketʧ�ܣ��ͷ���0
	}
	//��ʼ����,ָ�����ͬʱ������ΪCLIENT_MAX
	if( listen(ListeningSocket,CLIENT_MAX))
	{
		errorInfo("��������\n�����������");
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
		if(serLink(S) == 0)		//����scoket������񣬲���������INVALID_SOCKET
				return 0;		//����ʧ�ܾͷ���
		promptInfo("���ȴ����ӡ�");
		NewConnection = accept(ListeningSocket, (SOCKADDR *) &S.ClientAddr,&len);//�ȴ�����
		char t[40]={"�������ѽ���:"};
		strcat(t,inet_ntoa(S.ClientAddr.sin_addr));
		strcat(t,"��Esc���ɺ�̨����");
		flag_1 = 1;
		promptInfo(t);  //��������ӵ�ip��ַ
		if(InputBox((TCHAR *)A.serverName,20,"ȷ��-->ȷ���ǳ�\nȡ��-->Ĭ���ǳ�ΪWaLi" , "�����ǳ�",NULL,50,50,false) == false )
			strcpy(A.serverName,"Wali");
		hThread_2=CreateThread(NULL,NULL,recvMessage,NULL,0,&dwThreadId_2); //����������Ϣͬ���߳� hThread_2
	}
		inputUI(); //���ı������
		int y=30; //��һ����Ϣ���������
		if( hThread_2 != NULL)
		{  
			int j =1;
			while(j)  
			{  
				if(InputBox((TCHAR*)A.talk_1,1024,"ȷ��-->������Ϣ\nȡ��-->����������,��̨����" , "������������",NULL, 100, 100,false) == false)
					longjmp(jmpstar,1);  //����2�����������˵�
				if(send(NewConnection,A.talk_1,sizeof(A.talk_1),0) == -1)  
				{
					errorInfo("���ͳ���!");
					getch();
					j=0;
					break;
				}
				else  
				{	
					if(y >= 430 )
					{
						clearrectangle(210, 31, 800, 430);	//���֮ǰ����Ϣ
						error();
						prompt();
						loadimage(NULL,"image\\3.bmp");
						inputUI();
						y = 30;
					}
					setbkmode(TRANSPARENT);			//�������ֻ�ͼƬ�ı���͸��
					outtextxy(210,y,A.serverName);
					outtextxy(210+textwidth(A.serverName),y,":");
					outtextxy(210+textwidth(A.serverName)+textwidth(":"),y,A.talk_1);
					y+=20;
					outtextxy(210, y ,sysTime());
					input(A.serverName,A.talk_1);  //д�����ݿ�
				}
				if(strcmp(A.talk_1,"886")==0)   
				{
					promptInfo("�������ߣ������������");
					j=0;
					getch();
					closesocket(NewConnection);		//�ر�����  
					closesocket(ListeningSocket);	//���رռ���Socket  
					WSACleanup();					//�ͷ�Windows Socket DLL�������Դ  
					longjmp(jmpstar,1);  //�������˵�
				}
				if(kbhit())
				{
					promptInfo("��Esc���ɺ�̨����");
					if(27 ==  getch())
						longjmp(jmpstar,1);
				}
				y+=20;
			} //end while
		} 
		CloseHandle(hThread_2);
		CloseHandle(hThread_1);
		closesocket(NewConnection);		//�ر�����  
		closesocket(ListeningSocket);	//���رռ���Socket  
		WSACleanup();					//�ͷ�Windows Socket DLL�������Դ  
		return 1;
}


//������������Ϣ�߳�hThread_2
DWORD WINAPI recvMessage(LPVOID rev)
{  
	int recvbytes;
	int i=1;
	char clientName[20];
	char talk_2[1024];
	
	recvbytes=recv(NewConnection,clientName,20,0);  //���տͻ����ǳ�
	settextcolor(LIGHTBLUE);
	int y = 30;
	while(i)  
	{  
		if((recvbytes=recv(NewConnection,talk_2,1024,0)) != -1)   
		{  
			if(y >= 430 )
			{
				clearrectangle(210, 31, 800, 430);	//���֮ǰ����Ϣ
				error();
				prompt();
				loadimage(NULL,"image\\3.bmp");
				inputUI();
				y = 30;
			}
			setbkmode(TRANSPARENT);			//�������ֻ�ͼƬ�ı���͸��
			RECT a={210,y,800,y+20};
			drawtext(clientName, &a, DT_RIGHT);			//�Ҷ������ð��
			RECT b={210,y,800-textwidth(clientName),y+20};
			drawtext(":", &b,DT_RIGHT);	//�Ҷ�������ǳ�
			RECT c={210,y,800-textwidth(":")-textwidth(clientName),y+20};
			drawtext(talk_2, &c,DT_RIGHT);			//�Ҷ��������Ϣ
			input(clientName,talk_2);				//д�����ݿ�
			y+=20;
			RECT d={210,y,800,y+20};
			drawtext(sysTime(), &d, DT_RIGHT);		//�Ҷ������ʱ��
			if(strcmp(talk_2,"886")==0)    
			{
				promptInfo("�Է�������");
				getch();
				break;
			}
		}   
		y+=20;
	}  
	return 0;  
}   