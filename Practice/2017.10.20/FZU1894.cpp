// Copyright (C) 2017 SYCstudio.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000100;
const int inf=2147483647;

class Monotone_Queue
{
public:
	int head,tail;
	int Q_num[maxN*4];
	int Q_key[maxN*4];
	Monotone_Queue()
		{
			head=0;
			tail=0;
			memset(Q_num,0,sizeof(Q_num));
			memset(Q_key,0,sizeof(Q_key));
		}
	void init()
		{
			head=0;
			tail=0;
			memset(Q_num,0,sizeof(Q_num));
			memset(Q_key,0,sizeof(Q_key));
		}
	void Insert(int num,int key)//将编号为num,人品为key的人放入单调队列
		{
			if (head==tail)
			{
				head++;
				Q_num[head]=num;
				Q_key[head]=key;
				return;
			}
			while ((head!=tail)&&(Q_key[head]<=key))
				head--;
			head++;
			Q_num[head]=num;
			Q_key[head]=key;
			return;
		}
	void Pop(int num)//将编号小于等于num的全部弹出去
		{
			while ((head!=tail)&&(Q_num[tail+1]<=num))
				tail++;
			return;
		}
	int Top()
		{
			if (head==tail)
				return -1;
			return Q_key[tail+1];
		}
	void Outp()
		{
			if (head==tail)
			{
				cout<<"Empty!"<<endl;
				return;
			}
			for (int i=tail+1;i<=head;i++)
				cout<<"("<<Q_num[i]<<","<<Q_key[i]<<") ";
			cout<<endl;
		}
};

int n;
char str[20];
Monotone_Queue Q;

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int cnt1=0,cnt2=0;
		Q.init();
		while (scanf("%s",str)!=EOF)
			if (str[0]=='S')
				break;
		while (scanf("%s",str)!=EOF)
		{
			if (str[0]=='E')
				break;
			if (str[0]=='C')
			{
				scanf("%s",str);
				int RP;
				scanf("%d",&RP);
				cnt1++;
				Q.Insert(cnt1,RP);
			}
			else if (str[0]=='Q')
			{
				printf("%d\n",Q.Top());
			}
			else if (str[0]=='G')
			{
				cnt2++;
				Q.Pop(cnt2);
			}
		}
	}
	return 0;
}
