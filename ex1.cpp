//��д����windows vs2017 c++�� �汾10.0.17763.0
#include"pch.h"
#include<iostream>
#include<Windows.h>

using namespace std;

//ת��char �� wchar
wchar_t *GetWCHAR(const char *cstr)
{
	size_t len = strlen(cstr) + 1;
	size_t converted = 0;
	wchar_t* wstr = (wchar_t*)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted,wstr, len,cstr, _TRUNCATE);
	return wstr;
}

int main() {
	//����������UCAִ�м���Ϊ�������Ա
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));//��ʼ���ṹ��
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE"
	char app[] = "C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE ";
	char file[] = "";
	wchar_t * run = GetWCHAR(app);

	//����C++�� CreateProcess �� lpCommandLine ��������Ϊ wchar_t * Ĭ���ַ���Ϊ const char * ��Ҫת��
	if (!CreateProcess(NULL,run, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		fprintf(stderr, "��������ʧ��!\n");
	}

	int x;
	while (true) {
		cout << "������Ҫѡ��Ĳ�����\n0:���ٽ���\n1:�������\n2:�������\n3:�˳�\n";
		cin >> x;
		switch (x) {
		case 0:
			if (TerminateProcess(pi.hProcess, 0))//���ٽ��̽��̾�����˳���0 ��Ҫ����ԱȨ��
				cout << "���ٽ��̳ɹ�" << endl;
			else
				cout << "����ʧ��" << endl;
			break;
		case 1:
			if (SuspendThread(pi.hThread))//�����߳��߳̾��
				cout << "������̳ɹ�" << endl;
			else
				cout << "����ʧ��" << endl;
			break;
		case 2:
			if (ResumeThread(pi.hThread))//�����߳��߳̾��
				cout << "������̳ɹ�" << endl;
			else
				cout << "����ʧ��" << endl;
			break;
		case 3:
			exit(0);
		default:
			cout << "ѡ���ȷ" << endl;
		}

	}
	system("pause");
	return 0;
}