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
	char ipAddress[20];     //���������ip�ַ���
	in_addr ipAddr;			//ip��ַ�ṹ��
	if (flag_2 == 0)
	{
	WSAStartup(MAKEWORD(2,2), &S.wsaData);                                     //��ʼ��Windows Socket 2.2        
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                           //����һ���µ�Socket�����ӷ�����    
	S.ServerAddr.sin_family = AF_INET;  
	S.ServerAddr.sin_port = htons(PORT);  

	if(InputBox((TCHAR *)ipAddress,20,"ȷ��-->ȷ��ip\nȡ��-->Ĭ��Ϊ����������" , "���������ip",NULL,50,50,false) == false )
			strcpy(ipAddress,"127.0.0.1");
	ipAddr.S_un.S_addr = inet_addr(ipAddress);							//���ַ���ת��Ϊ�����ַ��ʽ
	S.ServerAddr.sin_addr.s_addr = ipAddr.S_un.S_addr;					//��дҪ����ͨ�ŵķ�����ip��ַ  
	
	if( (result = connect(s,(SOCKADDR *) &S.ServerAddr, sizeof(S.ServerAddr)) ) == SOCKET_ERROR )//������������������� 
	{	
		errorInfo("�޷��������ӣ�����,�����������"); 
		getch();
		return 0;
	}
	//���ӳɹ�
	flag_2 = 1;
	if(InputBox((TCHAR *)A.clientName,20,"ȷ��-->ȷ���ǳ�\nȡ��-->Ĭ���ǳ�ΪYiWa" , "�����ǳ�",NULL,50,50,false) == false )
				strcpy(A.clientName,"YiWa");
	char t[40]={"���������ӳɹ���"};
	strcat(t,"��Esc���ɺ�̨����");
	promptInfo(t);  //������ӵ�ip��ַ
	hThread_3 = CreateThread(NULL,NULL,cliRecvMess,NULL,0,&dwThreadId_3); //��Ϣͬ�������߳�
	} //end if(flag==0)
	//�ڶ��ν���ֱ����������
	inputUI();
	promptInfo("��Esc���ɺ�̨����");
	if(hThread_3!=NULL)
	{  
		int j =1;
		int y=30; //��һ����Ϣ���������
		while(j)  
		{  
			if(InputBox((TCHAR*)A.talk_2,1024,"ȷ��-->������Ϣ\nȡ��-->����������,���Լ������ܶԷ���Ϣ" , "������������",NULL, 100, 100,false) == false)
				longjmp(jmpstar,1);  //����������
			if(send(s,A.talk_2,sizeof(A.talk_2),0) == -1)  
			{
				errorInfo("���ͳ���!");
				getch();
				j=0;
				return 0;
				break;  
				}
				else  
				{	
					if(y >= 430 )
					{
						clearrectangle(210, 31, 800, 430);	//���֮ǰ����Ϣ
						error();
						prompt();
						loadimage(NULL,_T("IMAGE"),_T("back_2"));
						inputUI();
						y = 30;
					}
					setbkmode(TRANSPARENT);			//�������ֻ�ͼƬ�ı���͸��
					outtextxy(210,y,A.clientName);
					outtextxy(210+textwidth(A.clientName),y,":");
					outtextxy(210+textwidth(A.clientName)+textwidth(":"),y,A.talk_2);
					y+=20;
					outtextxy(210, y ,sysTime());
					input(A.clientName,A.talk_2);   //д�����ݿ�
				}
				if(strcmp(A.talk_2,"886")==0)   
				{
					promptInfo("��������,�����������");
					getch();
					break;
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
	closesocket(s);  
	WSACleanup();  
	return 1;
}  


//�ͻ��˽�����Ϣ�߳�
DWORD WINAPI cliRecvMess(LPVOID cli)  
{  
	int recvbytes; 
	int j =1;
	char serverName[20];
	char talk_1[1024];
	recvbytes=recv(s,serverName,20,0); //���ܷ������ǳ�
	settextcolor(LIGHTBLUE);
	int y = 31;
	while(j)  
	{  
		if((recvbytes=recv(s,talk_1,1024,0)) != -1)   
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
			drawtext(serverName, &a, DT_RIGHT);			//�Ҷ������ð��
			RECT b={210,y,800-textwidth(serverName),y+20};
			drawtext(":", &b,DT_RIGHT);	//�Ҷ�������ǳ�
			RECT c={210,y,800-textwidth(":")-textwidth(serverName),y+20};
			drawtext(talk_1, &c,DT_RIGHT);			//�Ҷ��������Ϣ
			input(serverName,talk_1);				//д�����ݿ�
			y+=20;
			RECT d={210,y,800,y+20};
			drawtext(sysTime(), &d, DT_RIGHT);		//�Ҷ������ʱ��
			if(strcmp(talk_1,"886")==0)    
			{
				promptInfo("�Է�������");
				j=0;  
			}
		}   
		y+=20;
		if(y >= 430 )
			clearrectangle(210, 31, 800, 430);	//���֮ǰ����Ϣ
	}  
	return 0;  
}   