#ifndef _WECHAT_H
#define _WECHAT_H
#define WIN32_LEAN_AND_MEAN //工程不使用MFC声明,在编译链接时，包括最后生成的一些供调试用的模块时，速度更快，容量更小。
/************头文件&引用***********/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include <setjmp.h>					//为了实现函数跳转 
#include <iostream>
#pragma comment(lib,"ws2_32.lib")	//引用ws2_32.lib库文件
#include "graphics.h"
#include "mysql.h"
//调用外部程序文件路径
#define EXE_PATH "G:\\Learning\\C-sources\\DB-MYSQL\\NavicatforMySQL\\NavicatforMySQL\\Navicat_for_MySQL\\navicat.exe"
#define PORT 80						//连接端口
#define CLIENT_MAX 20				//服务器允许客户端最大连接数
#define FILE_PATH "chatting.txt"	//文件路径
//聊天信息结构体
typedef struct 
{
	char serverName[20];				//服务器端昵称
	char clientName[20];
	char talk_1[1024];
	char talk_2[1024];
}UserInfo;
//mysql连接参数结构体
typedef struct 
{
	MYSQL *conn;
	char *host;
	char *dbname;
	const char *username;
	const char *password;
	unsigned int port;
}MY;
//scoket相关参数
typedef struct 
{
WSADATA      wsaData;		//该结构用来存储被WSAStartup函数调用后返回的Windows Sockets数据
SOCKADDR_IN  ServerAddr;    //服务器网络地址
SOCKADDR_IN  ClientAddr;	//客户端网络地址
}SCO;

extern MY SQL;
extern int is_file;		  //数据库或文件读写标识 0：数据库，1：文件
extern int flag_1,flag_2; //是否可以后台聊天标示符
extern jmp_buf jmpstar;   //设置函数跳转
/********************************模块设计***************************/
//（1）server服务器模块:server 
		int server(UserInfo &A,SCO &S);  //消息接收发送
		int serLink(SCO &S);	//建立scoket服务器
		DWORD WINAPI recvMessage(LPVOID recv);
		DWORD WINAPI serUI(LPVOID serui) ;

//（2）client客户端模块:client
		int client(UserInfo &A,SCO &S);  //客户端建立
		DWORD WINAPI cliRecvMess(LPVOID cli);  //创建线程
		
//（3）数据模块:data
//	（3.1）初始化数据模块
		int dbLink();				//数据库连接
		int initInfo(UserInfo &A,SCO &S);				//全局变量初始化
		int initDb();				//数据库数据初始化
//	（3.2） 数据读写模块
		char* sysTime();	                       //系统时间日期获取
		int readDb();
		int input(char * name,char *talk);		//写入记录
		int in_file(char * name,char *talk);
		int re_file();

//（4）UI模块 :UI
		void UI();										//界面初始化
		int  choose(UserInfo &A,SCO &S);			//功能选择界面
		int  dbUI();									//数据库管理界面
		//void backStar();								//返回主菜单
		void draw3_rectangle(char *a,char *b,char *c);	//画3个功能矩形
		void errorInfo(char *a);						//打印错误信息
		void promptInfo(char *a);						//打印提示信息
		void error();									//画错误提示区
		void prompt();									//画信息提示区

		//形参： a,b,c 对应各功能名称
		void draw2_rectangle(char *a,char *b);				//画2个功能矩形
		//形参：a,b 对应各功能名称
		void draw1_rectangle(char *a);
		void outInfo(char *a);								//画退出信息
		//形参：a 退出描述
		void clear3_rectangl();								//清除3个矩形
		void rect3_angle(int w,int h);						//画3个方框（选择框）
		//形参：w h 最后一个选择框的右坐标和下坐标增长值
		void inputUI();										//画文本输入框
#endif

/**********相关函数说明****************************************
	/*************相关参数说明****************
	1·INADDR_ANY表示机器上的所用网络地址;比如你的机器上有两张网卡,那么到达这两张网卡的数据,你的socket都可以得到通知
	2·htonl将IP地址转换为网络格式

	int socket(int domain,int type,int protocol)
	用于创建一个socket描述符,它唯一标识一个socket
		1·domain:协议域  type：指定socket类型  protocol:指定协议,取0时，将自动选择type类型对应的默认协议
		2·AF_INET字段是表示网络地址的类型（协议族/域），AF_INET是internet域中进行通信  
		3·SOCK_STREAM表示socket的类型，SOCK_STREAM表示是流套接字IPPROTO_TCP表明协议类型  
		4·PPROTO_TCP或者0表示TCP/IP协议
	 
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	把一个地址族中的特定地址赋给socket，例如对应AF_INET、AF_INET6,就是把一个ipv4或ipv6地址和端口号组合赋给socket
	1·sockfd：即socket描述字,它是通过socket()创建了的唯一的一个socket标识,bind()就是将给这个描述字绑定一个名字
	2·addr：一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址，
		这个地址结构根据地址创建socket时的地址协议族的不同而不同
	3·addrlen：对应的是地址的长度	
******************************************************************/
//mysql命令
//自动编号/自动增长字段清零: 
	//ALTER TABLE `tbl_wechat` AUTO_INCREMENT =1
//插入数据
	// INSERT INTO tbl_wechat(serID,cliID,time,serName,cliName,serInfo,cliInfo) VALUES('%d','%d','%s','%s','%s','%s','%s')",3,3,"15:21","xian","zai","jia","a!");
//读取数据
	// SELECT * FROM `tbl_wechat` LIMIT 0,100
//删除表
	//DROP TABLE IF EXISTS tbl_wechat