#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxM=200010;
const int inf=2147483647;

int n,m,S;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Degree[maxN];
int Fa0[maxN],Fa1[maxN],Queue[maxN];
bool vis[maxN];

void Add_Edge(int u,int v);

int main()
{
	mem(Head,-1);mem(Fa1,-1);mem(Fa2,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		int cnt;cin>>cnt;
		for (int i=1;i<=cnt;i++)
		{
			int v;cin>>v;Add_Edge(i,v);
		}
	}
	cin>>S;Fa0[S]=0;
	int h=1,t=0;Queue[1]=S;
	bool circle=0;
	bool win=0;int winpos;
	do
	{
		int u=Queue[++t];vis[u]=1;
		if ((Fa1[u]!=-1)&&(Head[u]==-1)){
			win=1;winpos=u;
		}
		for (int i=Head[u];i!=-1;i=Next[i])
			if (vis[V[i]]==0)
			{
				Degree[V[i]]--;
				if (Fa0[u]!=-1) Fa1[V[i]]=u;
				if (Fa1[u]!=-1) Fa0[V[i]]=u;
				if (Degree[V[i]]==0) Queue[++h]=V[i];
			}
	}
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Degree[v]++;return;
}
