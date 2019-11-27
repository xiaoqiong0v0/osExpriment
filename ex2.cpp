//编写环境windows vs2017 c++库 版本10.0.17763.0
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
	int in_c;//输入顺序
	char name[10]; // 进程名称
	int come_time; // 到达时间
	int run_time; // 运行时间
	int start_time; // 开始运行时间
	int end_time;// 结束运行时间
	int wait_time; // 等待时间
}task[N];

int num;//进程数目

void sleep(int n)
{
	int st = clock();
	while ((clock() - st) <= n);
}

int GetData()
{
	int i = 0;
	while (1) {
		printf("第%d个进程信息输入：\n", i+1);
		printf("请输入进程名称,输入q结束：\n");
		cin >> task[i].name;
		if (strcmp(task[i].name, "q") == 0) {
			break;
		}
		printf("请输入进程到达时间：\n");
		cin >> task[i].come_time;
		printf("请输入进程服务时间：\n");
		cin >> task[i].run_time;
		task[i].in_c = i;
		i++;
		if (i >= N) {
			break;
		}
	}
	printf("进程信息输入完毕！！！\n");
	return i;
}

void Print()//打印运行结果
{
	printf("模拟进程运行信息：\n");
	printf("task_name  come_time   start_time   run_time   end_time\n");
	for (int i = 0; i < num; i++)
	{
		printf("     %-9s%-13d", task[i].name, task[i].come_time);
		printf("%-10d%-12d", task[i].start_time, task[i].run_time);
		printf("%-4d\n", task[i].end_time);
	}
}
//按要求服务时间比较
bool cmp1(const struct Task& a, const struct Task& b)
{
	return a.run_time < b.run_time;
}

//短作业优先算法
void SJF()
{
	/**
	功能：实现短作业优先算法，将进程的运行结束信息
		  按照进程运行顺序输出。
	*/

	sort(task, task + num, cmp1);
	int countt = 0;
	for (int i = 0; i < num; i++)
	{
		printf("%s进程正在执行", task[i].name);
		for (int j = 0; j < 10; j++)
		{
			sleep(rt * task[i].run_time); printf(".");
		}
		putchar('\n');
		task[i].start_time = countt;
		countt += task[i].run_time;
		task[i].end_time = countt;
	}
	printf("\n所有进程全部执行完毕！！！\n\n");
	Print();
	printf("\n\n");
}
//按到达时间比较
bool cmp2(const struct Task& a, const struct Task& b)
{
	return a.come_time < b.come_time;
}

//先来先服务算法
void FCFS()
{
	/**
	功能：实现先来先服务算法，将进程的运行结束信息
		  按照进程运行顺序输出。
	*/

	int countt = 0;
	sort(task, task + num, cmp2);

	for (int i = 0; i < num; i++)
	{
		printf("%s进程正在执行", task[i].name);
		for (int j = 0; j < 10; j++)
		{
			sleep(rt * task[i].run_time); printf(".");
		}
		putchar('\n');
		task[i].start_time = countt;
		countt += task[i].run_time;
		task[i].end_time = countt;
	}
	printf("\n所有进程全部执行完毕！！！\n\n");
	Print();
	printf("\n\n");
}

//按响应比比较
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
//按开始时间比较
bool cmp4(const struct Task& a, const struct Task& b)
{
	return a.start_time < b.start_time;
}
//按输入顺序比较
bool cmp5(const struct Task& a, const struct Task& b)
{
	return a.in_c < b.in_c;
}
// 非抢占 高响应比 优先调度算法
void HRRN()
{
	/**
	功能；运行非抢占式 高响应比 优先调度算法执行进程，将进程的运行结束信息
		  按照进程运行顺序输出。
	*/
	//初始化进程的结束时间 -1
	for (int i = 0; i < num; i++)
		task[i].end_time = -1;

	int countt = 0;  //计时器
	while (true)
	{
		//反复运行与排序，让高响应比前置
		for (int i = 0; i < num; i++)
			task[i].wait_time = countt - task[i].come_time;
		sort(task, task + num, cmp3);

		if (task[0].end_time >= 0) break;

		printf("%s进程正在执行", task[0].name);
		for (int j = 0; j < 10; j++)
		{
			sleep(rt * task[0].run_time); printf(".");
		}
		putchar('\n');
		task[0].start_time = countt;
		countt += task[0].run_time;
		task[0].end_time = countt;
	}
	printf("\n所有进程全部执行完毕！！！\n\n");
	sort(task, task + num, cmp4);//重新按开始运行时间排序
	Print();
	printf("\n\n");
}

void Menu()
{
	printf("             命令\n");
	printf("       **** 1.FCFS算法\n");
	printf("       **** 2.SJF算法\n");
	printf("       **** 3.HRRN算法\n");
	printf("       **** 4.返回上级\n\n");
}

int main()
{
	int menu;
	int flag = 1;
	printf("             《进程调度实验程序》\n\n");
	while (1)
	{
		if (num != 0) {
			printf("输入q退出，否则继续.\n");
			char s[10];
			cin >> s;
			if (strcmp(s, "q") == 0) {
				break;
			}
		}
		num = GetData();//输入进程信息返回进程数
		if (num < 1) {
			printf("未输入进程信息!\n");
			continue;
		}
		while (flag) {
			printf("请输入命令: ");
			Menu();
			cin >> menu;
			switch (menu)
			{
			case 1:
				printf("     <启动 FCFS 调度算法>\n");
				FCFS();
				break;
			case 2:
				printf("     <启动 SJF 调度算法>\n");
				SJF();
				break;
			case 3:
				printf("     <启动非抢占式 HRRN 调度算法>\n");
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