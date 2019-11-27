//编写环境windows vs2017 c++库 版本10.0.17763.0 编码 UTF-8 dom
#include"pch.h"
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctime>

void sleep(int n);//等待
int getComes();//获取已到进程
void printResult();//打印结果
bool allFinish();//判断进程是否全部运行完毕
void runOnce();//运行一次

using namespace std;

const int N = 100;

struct PCB
{
	int getnum;//表示输入顺序
	char name[16];//进程名
	int cometime;//到达时间
	int needtime;//要求运行时间
	int elapsedtime = 0;//已经运行时间
	int priority = 0;//优先数
	char state = 'r'; //状态,r:就绪,f:完成,
}pcblist[N],//总列表
*comepcblist[N];//已到列表

struct Recoder {
	int pn;//表示第n个进程
	int time;//记录时间
	char name[16];//进程名
	char state;//状态
}recoders[N];

int recnum = 0;//记录条数
int num;//进程数量
int timeslice;//时间片大下
int systime;//系统运行时间（模拟）

void sleep(int n)
{
	int st = clock();
	while ((clock() - st) <= n);
}

int GetData()
{
	int i = 0;
	while (1) {
		printf("第%d个进程信息输入：\n", i + 1);
		printf("请输入进程名称,输入q结束：\n");
		cin >> pcblist[i].name;
		if (strcmp(pcblist[i].name, "q") == 0) {
			break;
		}
		printf("请输入进程到达时间：\n");
		cin >> pcblist[i].cometime;
		printf("请输入进程请求时间：\n");
		cin >> pcblist[i].needtime;
		pcblist[i].getnum = i;
		i++;
		if (i >= N) {
			break;
		}
	}
	printf("请输入时间片大小：\n");
	cin >> timeslice;
	printf("信息输入完毕！！！\n");
	return i;
}

int getComes() {//更新已到就绪列表
	int j = 0;
	for (int i = 0; i < num; i++) {
		if (pcblist[i].cometime <= systime && pcblist[i].state == 'r') {
			comepcblist[j] = &pcblist[i];
			j++;
		}
	}
	return j;
}

bool allFinish() {//检查所有程序运行完毕
	bool af = true;
	for (int i = 0; i < num; i++) {
		if (pcblist[i].state == 'r') {
			af = false;
			break;
		}
	}
	return af;
}

void sortPiontArray(int l) {//给PCB指针数组排序(小的靠前)
	for (int i = 1; i < l; i++) {//冒泡
		for(int j = 0;j<l-i;j++){
			if ((*comepcblist[j]).priority > (*comepcblist[j + 1]).priority) {
				PCB *tmp = comepcblist[j];
				comepcblist[j] = comepcblist[j + 1];
				comepcblist[j + 1] = comepcblist[j];
			}
		}
	}
}
void runOnce() {//运行一次
	int cc = getComes();
	if (cc > 0) {
		sortPiontArray(cc);
		printf("[%d]运行进程:%s\n", systime, (*comepcblist[0]).name);
		strcpy_s(recoders[recnum].name, (*comepcblist[0]).name);
		recoders[recnum].time = systime;
		recoders[recnum].pn = (*comepcblist[0]).getnum;
		for (int i = 0; i < timeslice; i++) {
			(*comepcblist[0]).elapsedtime++;
			if ((*comepcblist[0]).elapsedtime >= (*comepcblist[0]).needtime) {
				printf("进程 '%s' 运行完成\n", (*comepcblist[0]).name);
				(*comepcblist[0]).state = 'f';
			}
			(*comepcblist[0]).priority++;//运行一次优先数+1
		}
		printf("需要时间:%d\n", (*comepcblist[0]).needtime);
		printf("已花费时间:%d\n", (*comepcblist[0]).elapsedtime);
		recnum++;
		systime += timeslice;//运行了
		if (allFinish()) {
			printResult();
		}
		else {
			runOnce();
		}
	}
	else {
		if (allFinish()) {
			printResult();
		}
		else {
			systime++;//如果没有就绪的程序到来系统时间+1
			runOnce();
		}
	}
}

void printResult() {//打印结果
	printf("最终结果:\n");
	cout << "时间";
	for (int i = 0; i < num; i++) {
		printf("%6s", pcblist[i].name);
	}
	cout << endl;
	cout << "----";
	for (int i = 0; i < num; i++) {
		printf("------");
	}
	cout << "---" << endl;
	for (int i = 0; i < systime; i++) {
		if (i % 2 == 0) {
			printf("\033[37;44m");
		}
		else {
			printf("\033[37;43m");
		}
		printf("%4d", i);
		for (int j = 0; j < num; j++) {
			bool have = false;
			for (int k = 0; k < recnum; k++) {
				if (i == recoders[k].time && recoders[k].pn == j) {
					printf("%6s", "|");
					have = true;
					break;
				}
			}
			if (!have) {
				printf("%6s", " ");
			}
		}
		cout << "   " << endl;
	}
	printf("\033[37;40m");
}

int main()
{
	printf("<<基于优先级时间片轮转调度算法实验>>\n");
	num = GetData();
	runOnce();
	getchar();
}