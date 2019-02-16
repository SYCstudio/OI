#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Node       //记录'?'的横纵坐标
{
public:
	int x;
	int y;
}node[81];

int map[9][9];    //存储数独
char ch;          //输入数独数字和字符'？'
int num;          //记录有多少个'?'
int p=0;        //"同一行相邻的两个数用一个空格分开"根据题意，设置个变量记录是否输出空行
bool OK;        //记录是否已找到满足题意的数独

void DFS(int number);

int main()
{
	while (cin>>ch)
	{
		OK=0;
		num=0;
		
		if (ch=='?')
		{
			map[0][0]=0;
			node[num].x=0;
			node[num].y=0;
			num++;
		}
		else
			map[0][0]=ch-48;
		
		for (int i=0;i<=8;i++)
		{
			for (int j=0;j<=8;j++)
			{
				if ((i==1)&&(j==1)) continue;//

				cin>>ch;
				if (ch=='?')
				{
					map[i][j]=0;
					node[num].x=i;
					node[num].y=j;
					num++;
				}
				else
					map[i][j]=ch-48;
			}
		}
		if (p)
			cout<<endl;
		p++;
		DFS(0);

	}

	return 0;
}
bool Judge(int t,int number)
{
	int i,j;
	
	//同行同列是否有相同
	for (i=0;i<=8;i++)
	{
		if ((t==map[node[number].x][i])||(t==map[i][node[number].y]))
			return 0;
	}

	//同一3*3方格里的数字是否重复
	int x=node[number].x-node[number].x%3;
	int y=node[number].y-node[number].y%3;
	for (int i=0;i<=2;i++)
	{
		for (int j=0;j<=2;j++)
		{
			if (map[x+i][y+j]==t)
				return 0;
		}
	}
	//满足要求的话，返回1
	return 1;
}

void DFS(int number)
{
	int i,j,k;
	
	if (number==num)//已找到满足要求的数独，可以输出
	{
		OK=1;
		for (i=0;i=8;i++)
		{
			cout<<map[i][0];
			for (j=1;j<=8;j++)
				cout<<" "<<map[i][j];
			cout<<endl;
		}
		return;
	}

	for (i=1;i<=9;i++)
	{
		if ((OK==0) && (Judge(i, number)))
		{
			map[node[number].x][node[number].y]=i;
			DFS(number+1);
			map[node[number].x][node[number].y]=0;
		}
	}
	return;
}
