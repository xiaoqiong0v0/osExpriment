//编写环境windows vs2017 c++库 版本10.0.17763.0
#include"pch.h"
#include<iostream>
#include<Windows.h>

using namespace std;

//转换char 到 wchar
wchar_t *GetWCHAR(const char *cstr)
{
	size_t len = strlen(cstr) + 1;
	size_t converted = 0;
	wchar_t* wstr = (wchar_t*)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted,wstr, len,cstr, _TRUNCATE);
	return wstr;
}

int main() {
	//运行请配置UCA执行级别为请求管理员
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));//初始化结构体
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE"
	char app[] = "C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE ";
	char file[] = "";
	wchar_t * run = GetWCHAR(app);

	//本次C++库 CreateProcess 库 lpCommandLine 请求类型为 wchar_t * 默认字符串为 const char * 需要转换
	if (!CreateProcess(NULL,run, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "创建进程失败!\n");
	}

	int x;
	while (true) {
		cout << "请输入要选择的操作：\n0:销毁进程\n1:挂起进程\n2:激活进程\n3:退出\n";
		cin >> x;
		switch (x) {
		case 0:
			if (TerminateProcess(pi.hProcess, 0))//销毁进程进程句柄、退出码0 需要管理员权限
				cout << "销毁进程成功" << endl;
			else
				cout << "销毁失败" << endl;
			break;
		case 1:
			if (SuspendThread(pi.hThread))//挂起线程线程句柄
				cout << "挂起进程成功" << endl;
			else
				cout << "挂起失败" << endl;
			break;
		case 2:
			if (ResumeThread(pi.hThread))//挂起线程线程句柄
				cout << "激活进程成功" << endl;
			else
				cout << "激活失败" << endl;
			break;
		case 3:
			exit(0);
		default:
			cout << "选项不正确" << endl;
		}

	}
	system("pause");
	return 0;
}