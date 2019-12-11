//编写环境windows vs2017 c++库 版本10.0.17763.0 编码 Unicode
#include"pch.h"
#include<iostream>
#include<time.h>
using namespace std;
void rand(int n, int p[])//这函数是产生n个1~10的随机数放到p[]数组里面
{
	int START = 1;
	int END = 10;
	int v;
	int i;
	srand((unsigned int)time(NULL));
	cout << "产生随机请求:" << endl;
	for (i = 0; i < n; i++) {
		printf("%3d", i);
	}
	cout << endl;
	for (i = 0; i < n; i++)
	{
		v = rand() % (END - START + 1) + START;
		p[i] = v;
		printf("%3d", v);
	}
	cout << endl;
}
struct Pro {
	int num, time; //num存放具体的内容，time在不同算法里面有不同的意义 
};
//它们是物理块和页面的数据结构
void Input(int m, int N, Pro *p, Pro  *page)//完成p[]数组和page[]的初始化工作
{
	//p[]数组是存放页面的空间，m是页面的长度
	//page[]是可以使用的物理块，N是物理块的大小
	int *p2 = new int[m];
	rand(m, p2);
	for (int i = 0; i < m; i++) {
		p[i].num = p2[i];
		p[i].time = 0;
	}
	for (int i = 0; i < N; i++) { //初始化页面基本情况
		page[i].num = 0;
		page[i].time = N + 2 - i;
	}
}
int Search(int e, Pro *page, int N)//算法里面都要用到它。
{
	//它是找e页是否在page物理块中，N是物理块的大小 
	for (int i = 0; i < N; i++)
		if (e == page[i].num)
			return i; //如果找到，就返回在物理块中的位置给Search
	return -1;//找不到，就返回-1
}
int Max(Pro *page, int N)//LRU算法用到的
{
	//找出在page块中，time最大的值和位置，同时位置返回 //time最大，就代表了最久没被使用的数
	int e = page[0].time, i = 0;
	int k = 0;
	while (i < N)//找出离现在时间最长的页面 
	{
		if (e < page[i].time) {
			e = page[i].time;
			k = i;
		}
		i++;
	}
	cout << "换出页面：" << k << endl;
	return k;

}
int Compfu(Pro *page, int i, int t, Pro p[], int m)//OPT算法用到的
{
	//找出如果page[t]要等于p，并且zai p[i]~p[m]这个区间内，走的次数，最大的数
	int count = 0;//count是保存走的步数
	for (int j = i; j < m; j++)
	{
		if (page[t].num == p[j].num)
			break;//如果相等，跳出循环
		else
			count++;//不等就步数加1

	}
	return count;
}
int Min(Pro page[], int N)//LFU算法用到的
{
	//page[]是可以使用的物理块，N是物理块的大小 //找到出现次数最小的的数，并把位置返回
	int k = 0;
	int min = page[0].time;
	for (int i = 0; i < N; i++)
	{
		if (min > page[i].time) {
			min = page[i].time;
			k = i;
		}
	}
	return k;
}
void FIFO(Pro p[], Pro page[], int m, int N)//p[]数组是存放页面的空间，m是页面的长度
{
	//page[]是可以使用的物理块，N是物理块的大小
	float n = 0;//n用来保存缺页的次数
	int i = 0;//i是循环变量，它是表示走到页面的位置
	int t = 0;//t是用来表示物理块走到的位置
	cout << "页面置换情况:" << endl;
	for (i = 0; i < m; i++)
	{
		int s = Search(p[i].num, page, N);
		if ( s >= 0) {
			cout << i << ":" << " ";
			cout << "存在页面:" << s << ":" << page[s].num << endl;
			continue;//找到相同的页面，就跳到下一次循环，不做处理。
		}
		else//在找不到的时候，通过t=t%N,求出这次来替换物理块的位置   
		{
			n++;//缺页数加1   
			cout << i << ":" << " ";
			cout << "发生缺页，需换进页：" << p[i].num << endl;
			int rpn = n <= N ? (int)n:t%N;
			if (n > N) {
				cout << "换出页面：" << rpn << endl;
			}
			page[rpn].num = p[i].num;
			t++;//位置加1
		}
	}
	cout << "缺页次数：" << n << "    缺页率：" << n / m << "    命中率：" << 1 - n / m << endl;
}
void LFU(Pro p[], Pro page[], int m, int N)//p[]数组是存放页面的空间，m是页面的长度
{
	//近期最少使用
	//page[]是可以使用的物理块，N是物理块的大小， 
	float n = 0;//缺页次数
	int i = 0;
	int t = 0;
	for (i = 0; i < N; i++)
		page[i].time = 0;
	cout << "页面置换情况:   " << endl;
	for (i = 0; i < m; i++)
	{
		int s = Search(p[i].num, page, N);
		if (s >= 0) {
			cout << i << ":" << " ";
			cout << "存在页面:" << s << ":" << page[s].num << endl;
			page[s].time++;//找到相同的页面，time加1
			continue;//  
		}
		else
		{
			n++;//缺页数加1
			//找出使用最少的页面进行调换   
			t = n <= N ? (int)n : Min(page, N);//找到出现次数最小的的数，并把位置返回t
			cout << i << ": " << "发生缺页，需换进页：" << p[i].num << endl;
			if (n > N) {
				cout << "换出页面：" << t << endl;
			}
			page[t].num = p[i].num;
			page[t].time = 0;//该页time清零   
		}
	}
	cout << "缺页次数：" << n << "    缺页率：" << n / m << "    命中率：" << 1 - n / m << endl;
}

void OPT(Pro p[], Pro page[], int m, int N)//p[]数组是存放页面的空间，m是页面的长度
{
	//最优置换算法 未来最不会被使用
	//page[]是可以使用的物理块，N是物理块的大小      
	float n = 0;//n用来保存缺页的次数        
	int i = 0;//i是循环变量，它是表示走到页面的位置。         
	int t = 0; //t循环变量
	while (i < m)
	{
		int s = Search(p[i].num, page, N);
		if (s >= 0) {
			cout << i << ":" << " ";
			cout << "存在页面:" << s << ":" << page[s].num << endl;
			i++;//如果找到了，就不做处理。
		} 
		else//如果找不到    
		{
			int temp = 0, cn;//cn用来保存离后面最远的数     
			for (t = 0; t < N; t++)//对物理块里面的每个数进行遍历     
			{
				if (temp < Compfu(page, i, t, p, m))//temp用来保存      
				{
					//page[t]= p[i]~p[m]这个区间内，走的次数，最大的数        
					temp = Compfu(page, i, t, p, m);
					cn = t;
				}
			}
			n++;//缺页数加1
			int rpn = n <= N ? (int)n : cn;
			cout << i << ": " << "发生缺页，需换进页：" << p[i].num << endl;
			if (n > N) {
				cout << "换出页面：" << cn << endl;
			}
			page[rpn] = p[i];//替换最不可能被使用的数        
			i++;//跳到下一次循环    
		}
	}
	cout << "缺页次数：" << n << "    缺页率：" << n / m << "    命中率：" << 1 - n / m << endl;
}
void LRU(Pro p[], Pro page[], int m, int N)//p[]数组是存放页面的空间，m是页面的长度
{
	//最近最久没被使用
	//page[]是可以使用的物理块，N是物理块的大小    
	float n = 0;//n用来保存缺页的次数 
	int i = 0;//i是循环变量，它是表示走到页面的位置。 
	int t = 0;  //t是用来表示物理块走到的位置  
	cout << "页面置换情况:" << endl;
	while (i < m)
	{
		int k;
		k = t = Search(p[i].num, page, N);
		if (t >= 0) {
			cout << i << ":" << " ";
			cout << "存在页面:" << k << ":" << page[k].num << endl;
			page[t].time = 0;//如果找到，就要把当前的page[t].time次数清零
		}
		else//找不到的时候，发生缺页   
		{
			cout << i << ": " <<"发生缺页，需换进页：" << p[i].num << endl;
			n++; //缺页数加1
			t = n<=N?(int)n:Max(page, N);//找出page物理块里面，最久没被时候的数 或 最近一个没变占用的块               
			//同时把最久没被时候的数在物理块里的位置传给t        
			page[t].num = p[i].num;//最久没被使用的是被现在的数代替
			page[t].time = 0;//同时清零    
		}
		for (int j = 0; j < N; j++)//把缺页以外的数，把它没被使用的次数加1    
		{
			if (j == t)
				continue;
			page[j].time++;
		}
		i++;//跳到下一次循环    
	}
	cout << "缺页次数：" << n << "    缺页率：" << n / m << "    命中率：" << 1 - n / m << endl;
}
int main()
{
	int m = 0, t = 0, N = 0;
	cout << "请输入总页数：";
	cin >> m;
	Pro *p = new Pro[m];//p是用来放页面的地方    
	cout << "请输入物理块数：" << endl;
	cin >> N;
	Pro *page = new Pro[N];//page是放物理块的地方 
	int c;
	float n = 0;
	Input(m, N, p, page);//m是页面的总长，N是物理块的长度
	cout<< endl;
	while (true) {
		cout << "===选择操作===" << endl;
		cout << "1:FIFO页面置换" << endl;
		cout << "2:LRU页面置换" << endl;
		cout << "3:OPT页面置换" << endl;
		cout << "4:LFU页面置换" << endl;
		cout << "0:结束" << endl;
		cin >> c;
		switch (c) {
		case 1:
			FIFO(p, page, m, N);
			break;
		case 2:
			LRU(p, page, m, N);
			break;
		case 3:
			OPT(p, page, m, N);
			break;
		case 4:
			LFU(p, page, m, N);
			break;
		case 0:
			exit(0);
		default:
			cout << "没有与输入相匹配的操作，请重新输入" << endl;
		}
	}
}
