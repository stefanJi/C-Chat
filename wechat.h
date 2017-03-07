#ifndef _WECHAT_H
#define _WECHAT_H
#define WIN32_LEAN_AND_MEAN //���̲�ʹ��MFC����,�ڱ�������ʱ������������ɵ�һЩ�������õ�ģ��ʱ���ٶȸ��죬������С��
/************ͷ�ļ�&����***********/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include <setjmp.h>					//Ϊ��ʵ�ֺ�����ת 
#include <iostream>
#pragma comment(lib,"ws2_32.lib")	//����ws2_32.lib���ļ�
#include "graphics.h"
#include "mysql.h"
//�����ⲿ�����ļ�·��
#define EXE_PATH "G:\\Learning\\C-sources\\DB-MYSQL\\NavicatforMySQL\\NavicatforMySQL\\Navicat_for_MySQL\\navicat.exe"
#define PORT 80						//���Ӷ˿�
#define CLIENT_MAX 20				//����������ͻ������������
#define FILE_PATH "chatting.txt"	//�ļ�·��
//������Ϣ�ṹ��
typedef struct 
{
	char serverName[20];				//���������ǳ�
	char clientName[20];
	char talk_1[1024];
	char talk_2[1024];
}UserInfo;
//mysql���Ӳ����ṹ��
typedef struct 
{
	MYSQL *conn;
	char *host;
	char *dbname;
	const char *username;
	const char *password;
	unsigned int port;
}MY;
//scoket��ز���
typedef struct 
{
WSADATA      wsaData;		//�ýṹ�����洢��WSAStartup�������ú󷵻ص�Windows Sockets����
SOCKADDR_IN  ServerAddr;    //�����������ַ
SOCKADDR_IN  ClientAddr;	//�ͻ��������ַ
}SCO;

extern MY SQL;
extern int is_file;		  //���ݿ���ļ���д��ʶ 0�����ݿ⣬1���ļ�
extern int flag_1,flag_2; //�Ƿ���Ժ�̨�����ʾ��
extern jmp_buf jmpstar;   //���ú�����ת
/********************************ģ�����***************************/
//��1��server������ģ��:server 
		int server(UserInfo &A,SCO &S);  //��Ϣ���շ���
		int serLink(SCO &S);	//����scoket������
		DWORD WINAPI recvMessage(LPVOID recv);
		DWORD WINAPI serUI(LPVOID serui) ;

//��2��client�ͻ���ģ��:client
		int client(UserInfo &A,SCO &S);  //�ͻ��˽���
		DWORD WINAPI cliRecvMess(LPVOID cli);  //�����߳�
		
//��3������ģ��:data
//	��3.1����ʼ������ģ��
		int dbLink();				//���ݿ�����
		int initInfo(UserInfo &A,SCO &S);				//ȫ�ֱ�����ʼ��
		int initDb();				//���ݿ����ݳ�ʼ��
//	��3.2�� ���ݶ�дģ��
		char* sysTime();	                       //ϵͳʱ�����ڻ�ȡ
		int readDb();
		int input(char * name,char *talk);		//д���¼
		int in_file(char * name,char *talk);
		int re_file();

//��4��UIģ�� :UI
		void UI();										//�����ʼ��
		int  choose(UserInfo &A,SCO &S);			//����ѡ�����
		int  dbUI();									//���ݿ�������
		//void backStar();								//�������˵�
		void draw3_rectangle(char *a,char *b,char *c);	//��3�����ܾ���
		void errorInfo(char *a);						//��ӡ������Ϣ
		void promptInfo(char *a);						//��ӡ��ʾ��Ϣ
		void error();									//��������ʾ��
		void prompt();									//����Ϣ��ʾ��

		//�βΣ� a,b,c ��Ӧ����������
		void draw2_rectangle(char *a,char *b);				//��2�����ܾ���
		//�βΣ�a,b ��Ӧ����������
		void draw1_rectangle(char *a);
		void outInfo(char *a);								//���˳���Ϣ
		//�βΣ�a �˳�����
		void clear3_rectangl();								//���3������
		void rect3_angle(int w,int h);						//��3������ѡ���
		//�βΣ�w h ���һ��ѡ���������������������ֵ
		void inputUI();										//���ı������
#endif

/**********��غ���˵��****************************************
	/*************��ز���˵��****************
	1��INADDR_ANY��ʾ�����ϵ����������ַ;������Ļ���������������,��ô��������������������,���socket�����Եõ�֪ͨ
	2��htonl��IP��ַת��Ϊ�����ʽ

	int socket(int domain,int type,int protocol)
	���ڴ���һ��socket������,��Ψһ��ʶһ��socket
		1��domain:Э����  type��ָ��socket����  protocol:ָ��Э��,ȡ0ʱ�����Զ�ѡ��type���Ͷ�Ӧ��Ĭ��Э��
		2��AF_INET�ֶ��Ǳ�ʾ�����ַ�����ͣ�Э����/�򣩣�AF_INET��internet���н���ͨ��  
		3��SOCK_STREAM��ʾsocket�����ͣ�SOCK_STREAM��ʾ�����׽���IPPROTO_TCP����Э������  
		4��PPROTO_TCP����0��ʾTCP/IPЭ��
	 
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	��һ����ַ���е��ض���ַ����socket�������ӦAF_INET��AF_INET6,���ǰ�һ��ipv4��ipv6��ַ�Ͷ˿ں���ϸ���socket
	1��sockfd����socket������,����ͨ��socket()�����˵�Ψһ��һ��socket��ʶ,bind()���ǽ�����������ְ�һ������
	2��addr��һ��const struct sockaddr *ָ�룬ָ��Ҫ�󶨸�sockfd��Э���ַ��
		�����ַ�ṹ���ݵ�ַ����socketʱ�ĵ�ַЭ����Ĳ�ͬ����ͬ
	3��addrlen����Ӧ���ǵ�ַ�ĳ���	
******************************************************************/
//mysql����
//�Զ����/�Զ������ֶ�����: 
	//ALTER TABLE `tbl_wechat` AUTO_INCREMENT =1
//��������
	// INSERT INTO tbl_wechat(serID,cliID,time,serName,cliName,serInfo,cliInfo) VALUES('%d','%d','%s','%s','%s','%s','%s')",3,3,"15:21","xian","zai","jia","a!");
//��ȡ����
	// SELECT * FROM `tbl_wechat` LIMIT 0,100
//ɾ����
	//DROP TABLE IF EXISTS tbl_wechat