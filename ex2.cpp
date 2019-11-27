//��д����windows vs2017 c++�� �汾10.0.17763.0
#include"pch.h"
#include<iostream>
#include<Windows.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<map>
#include<stdio.h>

using namespace std;

const int N = 1000;
const int rt = 1;
struct Task
{
	int in_c;//����˳��
	char name[10]; // ��������
	int come_time; // ����ʱ��
	int run_time; // ����ʱ��
	int start_time; // ��ʼ����ʱ��
	int end_time;// ��������ʱ��
	int wait_time; // �ȴ�ʱ��
}task[N];

int num;//������Ŀ

void sleep(int n)
{
	int st = clock();
	while ((clock() - st) <= n);
}

int GetData()
{
	int i = 0;
	while (1) {
		printf("��%d��������Ϣ���룺\n", i+1);
		printf("�������������,����q������\n");
		cin >> task[i].name;
		if (strcmp(task[i].name, "q") == 0) {
			break;
		}
		printf("��������̵���ʱ�䣺\n");
		cin >> task[i].come_time;
		printf("��������̷���ʱ�䣺\n");
		cin >> task[i].run_time;
		task[i].in_c = i;
		i++;
		if (i >= N) {
			break;
		}
	}
	printf("������Ϣ������ϣ�����\n");
	return i;
}

void Print()//��ӡ���н��
{
	printf("ģ�����������Ϣ��\n");
	printf("task_name  come_time   start_time   run_time   end_time\n");
	for (int i = 0; i < num; i++)
	{
		printf("     %-9s%-13d", task[i].name, task[i].come_time);
		printf("%-10d%-12d", task[i].start_time, task[i].run_time);
		printf("%-4d\n", task[i].end_time);
	}
}
//��Ҫ�����ʱ��Ƚ�
bool cmp1(const struct Task& a, const struct Task& b)
{
	return a.run_time < b.run_time;
}

//����ҵ�����㷨
void SJF()
{
	/**
	���ܣ�ʵ�ֶ���ҵ�����㷨�������̵����н�����Ϣ
		  ���ս�������˳�������
	*/

	sort(task, task + num, cmp1);
	int countt = 0;
	for (int i = 0; i < num; i++)
	{
		printf("%s��������ִ��", task[i].name);
		for (int j = 0; j < 10; j++)
		{
			sleep(rt * task[i].run_time); printf(".");
		}
		putchar('\n');
		task[i].start_time = countt;
		countt += task[i].run_time;
		task[i].end_time = countt;
	}
	printf("\n���н���ȫ��ִ����ϣ�����\n\n");
	Print();
	printf("\n\n");
}
//������ʱ��Ƚ�
bool cmp2(const struct Task& a, const struct Task& b)
{
	return a.come_time < b.come_time;
}

//�����ȷ����㷨
void FCFS()
{
	/**
	���ܣ�ʵ�������ȷ����㷨�������̵����н�����Ϣ
		  ���ս�������˳�������
	*/

	int countt = 0;
	sort(task, task + num, cmp2);

	for (int i = 0; i < num; i++)
	{
		printf("%s��������ִ��", task[i].name);
		for (int j = 0; j < 10; j++)
		{
			sleep(rt * task[i].run_time); printf(".");
		}
		putchar('\n');
		task[i].start_time = countt;
		countt += task[i].run_time;
		task[i].end_time = countt;
	}
	printf("\n���н���ȫ��ִ����ϣ�����\n\n");
	Print();
	printf("\n\n");
}

//����Ӧ�ȱȽ�
bool cmp3(const struct Task& a, const struct Task& b)
{
	if (a.end_time < 0 && b.end_time < 0)
	{
		double ra = (a.wait_time + a.run_time) * 1.0 / a.run_time;
		double rb = (b.wait_time + b.run_time) * 1.0 / b.run_time;
		return ra > rb;
	}
	else
		return a.end_time < b.end_time;
}
//����ʼʱ��Ƚ�
bool cmp4(const struct Task& a, const struct Task& b)
{
	return a.start_time < b.start_time;
}
//������˳��Ƚ�
bool cmp5(const struct Task& a, const struct Task& b)
{
	return a.in_c < b.in_c;
}
// ����ռ ����Ӧ�� ���ȵ����㷨
void HRRN()
{
	/**
	���ܣ����з���ռʽ ����Ӧ�� ���ȵ����㷨ִ�н��̣������̵����н�����Ϣ
		  ���ս�������˳�������
	*/
	//��ʼ�����̵Ľ���ʱ�� -1
	for (int i = 0; i < num; i++)
		task[i].end_time = -1;

	int countt = 0;  //��ʱ��
	while (true)
	{
		//���������������ø���Ӧ��ǰ��
		for (int i = 0; i < num; i++)
			task[i].wait_time = countt - task[i].come_time;
		sort(task, task + num, cmp3);

		if (task[0].end_time >= 0) break;

		printf("%s��������ִ��", task[0].name);
		for (int j = 0; j < 10; j++)
		{
			sleep(rt * task[0].run_time); printf(".");
		}
		putchar('\n');
		task[0].start_time = countt;
		countt += task[0].run_time;
		task[0].end_time = countt;
	}
	printf("\n���н���ȫ��ִ����ϣ�����\n\n");
	sort(task, task + num, cmp4);//���°���ʼ����ʱ������
	Print();
	printf("\n\n");
}

void Menu()
{
	printf("             ����\n");
	printf("       **** 1.FCFS�㷨\n");
	printf("       **** 2.SJF�㷨\n");
	printf("       **** 3.HRRN�㷨\n");
	printf("       **** 4.�����ϼ�\n\n");
}

int main()
{
	int menu;
	int flag = 1;
	printf("             �����̵���ʵ�����\n\n");
	while (1)
	{
		if (num != 0) {
			printf("����q�˳����������.\n");
			char s[10];
			cin >> s;
			if (strcmp(s, "q") == 0) {
				break;
			}
		}
		num = GetData();//���������Ϣ���ؽ�����
		if (num < 1) {
			printf("δ���������Ϣ!\n");
			continue;
		}
		while (flag) {
			printf("����������: ");
			Menu();
			cin >> menu;
			switch (menu)
			{
			case 1:
				printf("     <���� FCFS �����㷨>\n");
				FCFS();
				break;
			case 2:
				printf("     <���� SJF �����㷨>\n");
				SJF();
				break;
			case 3:
				printf("     <��������ռʽ HRRN �����㷨>\n");
				HRRN();
				break;
			case 4:
				flag = 0;
				break;

			}
			sort(task, task + num, cmp5);
		}
	}
	return 0;
}