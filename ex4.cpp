//编写环境windows vs2017 c++库 版本10.0.17763.0 编码 UTF-8 dom
#include "pch.h"
#include<iostream>
using namespace std;

#define MAXPROCESS 7//最大进程数 7!=5040
#define MAXRESOURCE 50//最大资源数
#define MAXWAYS 5041//MAXPROCESS!+1

struct Resource//资源
{
	int innum;//输入顺序
	char name[16];
	int total;
	int available;//可用数
}Resources[MAXRESOURCE];

struct Process//进程
{
	int innum;//输入顺序
	char name[16];
	int obtained[MAXRESOURCE];
	int needs[MAXRESOURCE];
}Processes[MAXPROCESS];

int res_count = 0;//资源数量
int pro_count = 0;//程序数量
/**
*获取资源，返回资源数量
* @res 存资源的数组
*/
int GetResources(Resource *res) {
	int i = 0;
	while (1) {
		printf("第%d个资源信息输入：\n", i + 1);
		printf("请输入资源名称,输入q结束,输入d返回上一个输入：\n");
		cin >> res[i].name;
		if (strcmp(res[i].name, "q") == 0) {
			break;
		}
		if (strcmp(res[i].name, "d") == 0) {
			i>0 && i--;
			continue;
		}
		printf("请输入资源总量：\n");
		cin >> res[i].total;
		res[i].available = res[i].total;
		res[i].innum = i;
		i++;
		if (i >= MAXRESOURCE) {
			break;
		}
	}
	printf("输入完毕.\n");
	return i;
}
/**
* 获取进程,返回进程数量
* @pro 存进程的数组
* @res 资源
* @count 资源数量
*/
int GetProcesses(Process *pro,Resource *res, int count) {
	int i = 0;
	while (1) {
		printf("第%d个进程信息输入：\n", i + 1);
		printf("请输入进程名称,输入q结束,输入d返回上一个输入：\n");
		cin >> pro[i].name;
		if (strcmp(pro[i].name, "q") == 0) {
			break;
		}
		if (strcmp(pro[i].name, "d") == 0) {
			i > 0 && i--;
			for (int x = 0; x < count; x++) {
				res[x].available += pro[i].obtained[x];
			}
			continue;
		}
		for (int x = 0; x < count; x++) {
			printf("请输入进程对资源'%s'的目前占有量(当前余量'%d'): \n",res[x].name,res[x].available);
			cin >> pro[i].obtained[x];
			if (res[x].available - pro[i].obtained[x] < 0) {
				printf("输入错误,占有量大于余量.\n");
				x--;
				continue;
			}
			res[x].available -= pro[i].obtained[x];
			printf("请输入进程资源对 %s 的最大需求量(总量'%d'): \n",res[x].name,res[x].total);
			cin >> pro[i].needs[x];
			if (pro[i].obtained[x] > pro[i].needs[x]) {
				printf("输入错误,最大需求量小于占有量.\n");
				x--;
				continue;
			}
			if (pro[i].needs[x] < 0) {
				printf("输入错误,最大需求量不能小于1.\n");
				x--;
				continue;
			}
			if (pro[i].needs[x] > res[x].total) {
				printf("输入错误,最大需求量大于总资源量.\n");
				x--;
				continue;
			}
		}
		pro[i].innum = i;
		i++;
		if (i >= MAXPROCESS) {
			break;
		}
	}
	printf("输入完毕.\n");
	return i;
}
/**
* 显示资源与进程信息
* @res 资源数组
* @resl 资源数量
* @pro 进程数组
* @prol 进程数量
*/
void ShowRP(Resource *res, int resl, Process * pro, int prol) {
	for (int i = 0; i < resl; i++) {
		printf("资源:%-4s;总量:%-3d;余量:%-3d\n", res[i].name, res[i].total, res[i].available);
	}
	for (int i = 0; i < prol; i++) {
		printf("进程:%-4s\n", pro[i].name);
		for (int x = 0; x < resl; x++) {
			printf("    资源:%-4s;占有:%-3d;最大需求:%-3d\n",
				res[x].name, pro[i].obtained[x], pro[i].needs[x]);
		}
	}
}
/**
* @显示路径
*/
void ShowWays(Process (*ways)[MAXPROCESS],int rows,int cols) {
	printf("length:%d\n", rows);
	for (int row = 0; row < rows; row++) {
		printf("way%d: ", row+1);
		for (int col = 0; col < cols-1; col++) {
			printf("%s->", ways[row][col].name);
		}
		printf("%s\n",ways[row][cols-1].name);
	}
}
/**
* 生成所有路径（全排列）
* @s[]每次可以选择的点的数组
* @l数组的长度
* @&len固定的路径长度
* @(*save)[MAXPROCESS] 用来保存返回的路径二维数组
* @&savel 已经保存的组数
*/
void FindWay(int s[],int l,const int &len,int (*save)[MAXPROCESS],int &savel) {
	for (int i = 0; i < l; i++) {
		int tmp[MAXPROCESS];
		int k = 0;
		for (int j = 0; j < l; j++) {
			if (j != i ) {
				tmp[k] = s[j];
				k++;
			}
		}
		save[savel][len - 1 - k] = s[i];//选择当前第n级第i个覆盖
		if (k != 0) {
			FindWay(tmp, k, len, save, savel);//查找下一级
		}
		else
		{
			savel++;
			for (int j = k; j < len; j++) {
				save[savel][j] = save[savel - 1][j];
			}
		}
	}
}
/**
* 获取所有安全序列
* @pro 进程数组
* @prol 进程数量
* @res 资源数组
* @resl 资源数量
* @ways 存储路径的二维数组
* @&wl 可行路径数
*/
void SafeBank(Process *pro, int prol,Resource *res,int resl,Process (*ways)[MAXPROCESS],int &wl) {
	wl = 0;
	int(*save)[MAXPROCESS] = new int[MAXWAYS][MAXPROCESS];
	const int len = prol;
	int al = 0;
	int sort[MAXPROCESS];
	for (int i = 0; i < prol; i++) {
		sort[i] = i;
	}
	FindWay(sort, prol, len, save, al);
	for (int i = 0; i < al; i++) {
		Resource restmp[MAXRESOURCE];
		for (int j = 0; j < resl; j++) {
			restmp[j] = res[j];
		}
		Process protmp[MAXPROCESS];
		for (int j = 0; j < prol; j++) {
			protmp[j] = pro[save[i][j]];
		}
		bool safe = true;
		for (int j = 0; j < prol; j++) {//判断路径是否安全
			for (int k = 0; k < resl; k++) {//判断是否能获取资源
				printf("%s->need:%d;available:%d;\n", 
					protmp[j].name,(protmp[j].needs[k] - protmp[j].obtained[k]), restmp[k].available);
				if (protmp[j].needs[k] - protmp[j].obtained[k] > restmp[k].available) {
					printf("break;\n");
					safe = false;
					break;
				}
			}
			if (!safe) {
				break;
			}
			else {//能获取值->完成->释放
				for (int k = 0; k < resl; k++) {
					restmp[k].available += protmp[j].needs[k];
				}
			}
		}
		if (safe) {//安全则保存该路径
			for (int j = 0; j < prol; j++) {
				ways[wl][j] = protmp[j];
			}
			wl++;
		}
	}
}
/**
*模拟请求
*/
void Request(Process *pro, int prol, Resource *res, int resl) {
	int p = 0;
	while (true)
	{
		printf("请输入发出请求的进程序号(0开始):\n");
		cin >> p;
		if (p >= 0 && p < prol) {
			break;
		}
		else
		{
			printf("输入错误!\n");
		}
	}
	Process protmp[MAXPROCESS];
	for (int i = 0; i < prol; i++) {
		protmp[i] = pro[i];
	}
	Resource restmp[MAXRESOURCE];
	for (int i = 0; i < resl; i++) {
		restmp[i] = res[i];
	}
	for (int i = 0; i < resl; i++) {
		int v = 0;
		while (true)
		{
			printf("请输入进程 %s 对资源 %s 的请求量(最大需求:%d)\n", 
				protmp[p].name, restmp[i].name, protmp[p].needs[i]);
			cin >> v;
			if (v >= 0 && v <= protmp[p].needs[i]) {
				break;
			}
			printf("输入错误.超出范围.\n");
		}
		if (restmp[i].available < v) {//如果余量不够则不满足
			printf("该请求不会被满足!\n");
		}
		else {
			protmp[p].obtained[i] += v;
			restmp[i].available -= v;
		}
	}
	//如果余量足够则判断是否安全
	Process(*save)[MAXPROCESS] = new Process[MAXWAYS][MAXPROCESS];
	int wl = 0;
	SafeBank(protmp, prol, restmp, resl, save, wl);
	ShowWays(save, wl, prol);
	if (wl > 0) {
		printf("系统将满足该进程的请求!\n");
	}
	else {
		printf("该请求不会被满足!\n");
	}
}
int main() {
	/*
	//测试数据
	printf("Max %d ways\n", (1 * 1024 * 1024 / (sizeof(int)*MAXPROCESS)));
	int c = 3;
	int p = 3;
	Resource Resources[3] = {
		{0,"A",20,16},
		{1,"B",30,14},
		{2,"C",20,13}
	};
	Process Processes[3] = {
		{0,"P0",{1,2,3},{5,9,6}},
		{1,"P1",{2,3,2},{4,5,3}},
		{2,"P2",{1,1,2},{2,6,8}}
	};
	//
	*/
	int c = GetResources(Resources);
	int p = GetProcesses(Processes,Resources,c);
	ShowRP(Resources,c,Processes,p);
	Process (*save)[MAXPROCESS]  = new Process[MAXWAYS][MAXPROCESS];
	int wl = 0;
	SafeBank(Processes, p,Resources,c,save,wl);
	ShowWays(save, wl, p);
	Request(Processes, p, Resources, c);
	getchar();
	return 0;
}