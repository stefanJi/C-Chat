#include "wechat.h"

MY SQL;   //定义为全局变量
jmp_buf jmpstar;
int flag_1,flag_2;
int main()
{

	UserInfo A; 
	SCO S;
	UI();		//画操作界面
	void(*backStar)() = &UI;
	error();	//画错误提示区
	loadimage(NULL,_T("IMAGE"),_T("back_3"));
	if(initInfo(A,S)==0 )  //初始化各个变量和数据库
	{
		errorInfo("初始化失败,按任意键退出…");
		getch();
		return 0;
	}
	if( choose(A,S) == 0 )//画功能选择界面	
	{
		errorInfo("功能选择界面出错\n按任意键退出");
		getch();
		return 0;
	}
	getch();
	return 0;
}