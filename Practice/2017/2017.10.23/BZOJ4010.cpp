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
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mcp(Arr,Brr) memcpy(Arr,Brr,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

int n,m;
int cnt=0;
int Head[maxN];
int Next[maxN*2];
int V[maxN*2];
priority_queue<int> Q;
int InDegree[maxN];
bool inqueue[maxN];
int Ans[maxN];

int read();
void Add_Edge(int u,int v);

int main()
{
	int D=read();
	while (D--)
	{
		cnt=0;
		mem(Head,-1);
		mem(InDegree,0);
		mem(inqueue,0);
		n=read();
		m=read();
		while (!Q.empty())
			Q.pop();
		for (int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			Add_Edge(v,u);
		}
		for (int i=1;i<=n;i++)
			if (InDegree[i]==0)
			{
				Q.push(i);
				inqueue[i]=1;
			}
		bool get_ans=1;
		for (int i=n;i>=1;i--)
		{
			//cout<<Q.empty()<<endl;
			if (Q.empty())
			{
				get_ans=0;
				break;
			}
			Ans[i]=Q.top();
			Q.pop();
			for (int j=Head[Ans[i]];j!=-1;j=Next[j])
			{
				int v=V[j];
				InDegree[v]--;
				if (InDegree[v]==0)
					Q.push(v);
			}
		}
		if (get_ans==0)
		{
			printf("Impossible!\n");
			continue;
		}
		for (int i=1;i<=n;i++)
			printf("%d ",Ans[i]);
		printf("\n");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

int read()
{
	int x=0,k=1;
	char ch=getchar();
	while (((ch<'0')||(ch>'9'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}

void Add_Edge(int u,int v)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	V[cnt]=v;
	InDegree[v]++;
	return;
}
