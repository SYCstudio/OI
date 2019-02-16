#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=500;
const int maxM=60000;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int Q[maxM];
int cur[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	memset(Head,-1,sizeof(Head));
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		Add_Edge(0,i,1);
		Add_Edge(i+n,2*n+1,1);
	}
	for (int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v+n,1);
	}
	int Ans=0;
	while (bfs())
	{
		for (int i=0;i<=n*2+1;i++)
			cur[i]=Head[i];
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	memset(vis,0,sizeof(vis));
	Ans=0;
	for (int i=1;i<=n;i++)
	{
		if (vis[i]==1)
			continue;
		int now=i;
		bool get;
		do
		{
			cout<<now<<" ";
			vis[now]=1;
			get=0;
			for (int i=Head[now];i!=-1;i=Next[i])
				if ((E[i].flow==0)&&(E[i].v>n)&&(E[i].v<=2*n))
				{
					now=E[i].v-n;
					get=1;
					break;
				}
		}
		while (get==1);
		cout<<endl;
		Ans++;
	}
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].v=v;
	E[cnt].flow=flow;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].v=u;
	E[cnt].flow=0;
}

bool bfs()
{
	memset(depth,-1,sizeof(depth));
	int t=0,h=1;
	Q[1]=0;
	depth[0]=1;
	do
	{
		t++;
		int u=Q[t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&(depth[v]==-1))
			{
				depth[v]=depth[u]+1;
				h++;
				Q[h]=v;
			}
		}
	}
	while (h!=t);
	if (depth[n*2+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==n*2+1)
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
