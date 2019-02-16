#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=500;
const int maxM=5201;
const int inf=2147483647;

int n,m;
int S,T;
int cnt=-1;
int Head[maxN];
int Next[maxM];
int V[maxM];
int W[maxM];
int cur[maxN];
int Depth[maxN];

void Add_Edge(int u,int v,int flow);
void _Add(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	memset(Head,-1,sizeof(Head));
	memset(Next,-1,sizeof(Next));
	scanf("%d%d%d%d",&n,&m,&S,&T);
	T=n+T;
	for (int i=1;i<=n;i++)
	{
		Add_Edge(i,i+n,1);
		Add_Edge(i+n,i,1);
	}
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v+n,inf);
		Add_Edge(v,u+n,inf);
	}
	int Ans=0;
	while (bfs())
	{
		for (int i=1;i<=n*2;i++)
			cur[i]=Head[i];
		while (int di=dfs(S,inf))
			Ans+=di;
	}
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	_Add(u,v,flow);
	_Add(v,u,0);
	return;
}

void _Add(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	V[cnt]=v;
	W[cnt]=flow;
	return;
}

bool bfs()
{
	memset(Depth,-1,sizeof(Depth));
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	Q.push(S);
	Depth[S]=1;
	do
	{
		int u=Q.front();
		Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			if ((Depth[V[i]]==-1)&&(W[i]>0))
			{
				Depth[V[i]]=Depth[u]+1;
				Q.push(V[i]);
			}
		}
	}
	while (!Q.empty());
	if (Depth[T]==-1)
		return 0;
    return 1;
}

int dfs(int u,int flow)
{
	if (u==T)
		return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
	{
		if ((Depth[V[i]]==Depth[u]+1)&&(W[i]>0))
		{
			int di=dfs(V[i],min(flow,W[i]));
			if (di>0)
			{
				W[i]-=di;
				W[i^1]+=di;
				return di;
			}
		}
	}
	return 0;
}
