#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=600;
const int maxM=20001*20;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int S,T;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int Q[maxM];
int cur[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
    while (cin>>n>>m)
	{
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		scanf("%d%d",&S,&T);
		T=T+n;
		for (int i=1;i<=n;i++)
		{
			int cost;
			scanf("%d",&cost);
			Add_Edge(i,i+n,cost);
		}
		for (int i=1;i<=m;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			Add_Edge(u+n,v,inf);
			Add_Edge(v+n,u,inf);
		}
		int Ans=0;
		while (bfs())
		{
			for (int i=1;i<=2*n;i++)
				cur[i]=Head[i];
			while (int di=dfs(S,inf))
				Ans+=di;
		}
		printf("%d\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].flow=flow;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].u=v;
	E[cnt].v=u;
	E[cnt].flow=0;
	return;
}

bool bfs()
{
	memset(depth,-1,sizeof(depth));
	int h=1,t=0;
	Q[1]=S;
	depth[S]=1;
	do
	{
		t++;
		int u=Q[t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((depth[v]==-1)&&(E[i].flow>0))
			{
				depth[v]=depth[u]+1;
				h++;
				Q[h]=v;
			}
		}
	}
	while (t!=h);
	if (depth[T]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==T)
		return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if ((depth[v]==depth[u]+1)&&(E[i].flow>0))
		{
			int di=dfs(v,min(flow,E[i].flow));
			if (di>0)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	}
	return 0;
}
