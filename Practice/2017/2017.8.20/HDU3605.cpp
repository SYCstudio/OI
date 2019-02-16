#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

const int maxN=100101;
const int maxM=maxN*70;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int cnt;
int tot;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxN];
map<int,int> Cnt;

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	while (cin>>n>>m)
	{
		cnt=-1;
		tot=0;
		memset(Head,-1,sizeof(Head));
		Cnt.clear();
		for (int i=1;i<=n;i++)
		{
			int ret=0;
			for (int j=1;j<=m;j++)
			{
				int is;
				scanf("%d",&is);
				ret=ret+(is<<j);
			}
			Cnt[ret]++;
		}
		map<int,int>::iterator loop;
		for (loop=Cnt.begin();loop!=Cnt.end();loop++)
		{
			tot++;
			for (int i=1;i<=m;i++)
				if ((loop->first)&(1<<i))
					Add_Edge(tot,Cnt.size()+i,loop->second);
			Add_Edge(0,tot,loop->second);
		}
		for (int i=1;i<=m;i++)
		{
			int flow;
			scanf("%d",&flow);
			Add_Edge(tot+i,tot+m+1,flow);
		}
		int Ans=0;
		while (bfs())
		{
			for (int i=0;i<=tot+m+1;i++)
				cur[i]=Head[i];
			while (int di=dfs(0,inf))
				Ans+=di;
		}
		if (Ans==n)
			printf("YES\n");
		else
			printf("NO\n");
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
}

bool bfs()
{
	memset(depth,-1,sizeof(depth));
	int h=1,t=0;
	Q[1]=0;
	depth[0]=1;
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
	while (h!=t);
	if (depth[tot+m+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==tot+m+1)
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
