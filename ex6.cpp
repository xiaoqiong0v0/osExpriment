//��д����windows vs2017 c++�� �汾10.0.17763.0 ���� Unicode
#include"pch.h"
#include<iostream>
#include<time.h>
using namespace std;
void rand(int n, int p[])//�⺯���ǲ���n��1~10��������ŵ�p[]��������
{
	int START = 1;
	int END = 10;
	int v;
	int i;
	srand((unsigned int)time(NULL));
	cout << "�����������:" << endl;
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
	int num, time; //num��ž�������ݣ�time�ڲ�ͬ�㷨�����в�ͬ������ 
};
//������������ҳ������ݽṹ
void Input(int m, int N, Pro *p, Pro  *page)//���p[]�����page[]�ĳ�ʼ������
{
	//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С
	int *p2 = new int[m];
	rand(m, p2);
	for (int i = 0; i < m; i++) {
		p[i].num = p2[i];
		p[i].time = 0;
	}
	for (int i = 0; i < N; i++) { //��ʼ��ҳ��������
		page[i].num = 0;
		page[i].time = N + 2 - i;
	}
}
int Search(int e, Pro *page, int N)//�㷨���涼Ҫ�õ�����
{
	//������eҳ�Ƿ���page������У�N�������Ĵ�С 
	for (int i = 0; i < N; i++)
		if (e == page[i].num)
			return i; //����ҵ����ͷ�����������е�λ�ø�Search
	return -1;//�Ҳ������ͷ���-1
}
int Max(Pro *page, int N)//LRU�㷨�õ���
{
	//�ҳ���page���У�time����ֵ��λ�ã�ͬʱλ�÷��� //time��󣬾ʹ��������û��ʹ�õ���
	int e = page[0].time, i = 0;
	int k = 0;
	while (i < N)//�ҳ�������ʱ�����ҳ�� 
	{
		if (e < page[i].time) {
			e = page[i].time;
			k = i;
		}
		i++;
	}
	cout << "����ҳ�棺" << k << endl;
	return k;

}
int Compfu(Pro *page, int i, int t, Pro p[], int m)//OPT�㷨�õ���
{
	//�ҳ����page[t]Ҫ����p������zai p[i]~p[m]��������ڣ��ߵĴ�����������
	int count = 0;//count�Ǳ����ߵĲ���
	for (int j = i; j < m; j++)
	{
		if (page[t].num == p[j].num)
			break;//�����ȣ�����ѭ��
		else
			count++;//���ȾͲ�����1

	}
	return count;
}
int Min(Pro page[], int N)//LFU�㷨�õ���
{
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С //�ҵ����ִ�����С�ĵ���������λ�÷���
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
void FIFO(Pro p[], Pro page[], int m, int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С
	float n = 0;//n��������ȱҳ�Ĵ���
	int i = 0;//i��ѭ�����������Ǳ�ʾ�ߵ�ҳ���λ��
	int t = 0;//t��������ʾ������ߵ���λ��
	cout << "ҳ���û����:" << endl;
	for (i = 0; i < m; i++)
	{
		int s = Search(p[i].num, page, N);
		if ( s >= 0) {
			cout << i << ":" << " ";
			cout << "����ҳ��:" << s << ":" << page[s].num << endl;
			continue;//�ҵ���ͬ��ҳ�棬��������һ��ѭ������������
		}
		else//���Ҳ�����ʱ��ͨ��t=t%N,���������滻������λ��   
		{
			n++;//ȱҳ����1   
			cout << i << ":" << " ";
			cout << "����ȱҳ���軻��ҳ��" << p[i].num << endl;
			int rpn = n <= N ? (int)n:t%N;
			if (n > N) {
				cout << "����ҳ�棺" << rpn << endl;
			}
			page[rpn].num = p[i].num;
			t++;//λ�ü�1
		}
	}
	cout << "ȱҳ������" << n << "    ȱҳ�ʣ�" << n / m << "    �����ʣ�" << 1 - n / m << endl;
}
void LFU(Pro p[], Pro page[], int m, int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{
	//��������ʹ��
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С�� 
	float n = 0;//ȱҳ����
	int i = 0;
	int t = 0;
	for (i = 0; i < N; i++)
		page[i].time = 0;
	cout << "ҳ���û����:   " << endl;
	for (i = 0; i < m; i++)
	{
		int s = Search(p[i].num, page, N);
		if (s >= 0) {
			cout << i << ":" << " ";
			cout << "����ҳ��:" << s << ":" << page[s].num << endl;
			page[s].time++;//�ҵ���ͬ��ҳ�棬time��1
			continue;//  
		}
		else
		{
			n++;//ȱҳ����1
			//�ҳ�ʹ�����ٵ�ҳ����е���   
			t = n <= N ? (int)n : Min(page, N);//�ҵ����ִ�����С�ĵ���������λ�÷���t
			cout << i << ": " << "����ȱҳ���軻��ҳ��" << p[i].num << endl;
			if (n > N) {
				cout << "����ҳ�棺" << t << endl;
			}
			page[t].num = p[i].num;
			page[t].time = 0;//��ҳtime����   
		}
	}
	cout << "ȱҳ������" << n << "    ȱҳ�ʣ�" << n / m << "    �����ʣ�" << 1 - n / m << endl;
}

void OPT(Pro p[], Pro page[], int m, int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{
	//�����û��㷨 δ����ᱻʹ��
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С      
	float n = 0;//n��������ȱҳ�Ĵ���        
	int i = 0;//i��ѭ�����������Ǳ�ʾ�ߵ�ҳ���λ�á�         
	int t = 0; //tѭ������
	while (i < m)
	{
		int s = Search(p[i].num, page, N);
		if (s >= 0) {
			cout << i << ":" << " ";
			cout << "����ҳ��:" << s << ":" << page[s].num << endl;
			i++;//����ҵ��ˣ��Ͳ�������
		} 
		else//����Ҳ���    
		{
			int temp = 0, cn;//cn���������������Զ����     
			for (t = 0; t < N; t++)//������������ÿ�������б���     
			{
				if (temp < Compfu(page, i, t, p, m))//temp��������      
				{
					//page[t]= p[i]~p[m]��������ڣ��ߵĴ�����������        
					temp = Compfu(page, i, t, p, m);
					cn = t;
				}
			}
			n++;//ȱҳ����1
			int rpn = n <= N ? (int)n : cn;
			cout << i << ": " << "����ȱҳ���軻��ҳ��" << p[i].num << endl;
			if (n > N) {
				cout << "����ҳ�棺" << cn << endl;
			}
			page[rpn] = p[i];//�滻����ܱ�ʹ�õ���        
			i++;//������һ��ѭ��    
		}
	}
	cout << "ȱҳ������" << n << "    ȱҳ�ʣ�" << n / m << "    �����ʣ�" << 1 - n / m << endl;
}
void LRU(Pro p[], Pro page[], int m, int N)//p[]�����Ǵ��ҳ��Ŀռ䣬m��ҳ��ĳ���
{
	//������û��ʹ��
	//page[]�ǿ���ʹ�õ�����飬N�������Ĵ�С    
	float n = 0;//n��������ȱҳ�Ĵ��� 
	int i = 0;//i��ѭ�����������Ǳ�ʾ�ߵ�ҳ���λ�á� 
	int t = 0;  //t��������ʾ������ߵ���λ��  
	cout << "ҳ���û����:" << endl;
	while (i < m)
	{
		int k;
		k = t = Search(p[i].num, page, N);
		if (t >= 0) {
			cout << i << ":" << " ";
			cout << "����ҳ��:" << k << ":" << page[k].num << endl;
			page[t].time = 0;//����ҵ�����Ҫ�ѵ�ǰ��page[t].time��������
		}
		else//�Ҳ�����ʱ�򣬷���ȱҳ   
		{
			cout << i << ": " <<"����ȱҳ���軻��ҳ��" << p[i].num << endl;
			n++; //ȱҳ����1
			t = n<=N?(int)n:Max(page, N);//�ҳ�page��������棬���û��ʱ����� �� ���һ��û��ռ�õĿ�               
			//ͬʱ�����û��ʱ���������������λ�ô���t        
			page[t].num = p[i].num;//���û��ʹ�õ��Ǳ����ڵ�������
			page[t].time = 0;//ͬʱ����    
		}
		for (int j = 0; j < N; j++)//��ȱҳ�������������û��ʹ�õĴ�����1    
		{
			if (j == t)
				continue;
			page[j].time++;
		}
		i++;//������һ��ѭ��    
	}
	cout << "ȱҳ������" << n << "    ȱҳ�ʣ�" << n / m << "    �����ʣ�" << 1 - n / m << endl;
}
int main()
{
	int m = 0, t = 0, N = 0;
	cout << "��������ҳ����";
	cin >> m;
	Pro *p = new Pro[m];//p��������ҳ��ĵط�    
	cout << "���������������" << endl;
	cin >> N;
	Pro *page = new Pro[N];//page�Ƿ������ĵط� 
	int c;
	float n = 0;
	Input(m, N, p, page);//m��ҳ����ܳ���N�������ĳ���
	cout<< endl;
	while (true) {
		cout << "===ѡ�����===" << endl;
		cout << "1:FIFOҳ���û�" << endl;
		cout << "2:LRUҳ���û�" << endl;
		cout << "3:OPTҳ���û�" << endl;
		cout << "4:LFUҳ���û�" << endl;
		cout << "0:����" << endl;
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
			cout << "û����������ƥ��Ĳ���������������" << endl;
		}
	}
}
