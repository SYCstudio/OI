#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Node       //��¼'?'�ĺ�������
{
public:
	int x;
	int y;
}node[81];

int map[9][9];    //�洢����
char ch;          //�����������ֺ��ַ�'��'
int num;          //��¼�ж��ٸ�'?'
int p=0;        //"ͬһ�����ڵ���������һ���ո�ֿ�"�������⣬���ø�������¼�Ƿ��������
bool OK;        //��¼�Ƿ����ҵ��������������

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
	
	//ͬ��ͬ���Ƿ�����ͬ
	for (i=0;i<=8;i++)
	{
		if ((t==map[node[number].x][i])||(t==map[i][node[number].y]))
			return 0;
	}

	//ͬһ3*3������������Ƿ��ظ�
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
	//����Ҫ��Ļ�������1
	return 1;
}

void DFS(int number)
{
	int i,j,k;
	
	if (number==num)//���ҵ�����Ҫ����������������
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
