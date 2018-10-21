#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1001;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int N,F,D;
int cnt=-1;
char str[maxN];
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	while (cin>>N>>F>>D)
	{
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		for (int i=1;i<=F;i++)
		{
			int maxflow;
			scanf("%d",&maxflow);
			Add_Edge(0,N*2+i,maxflow);
		}
		for (int i=1;i<=D;i++)
		{
			int maxflow;
			scanf("%d",&maxflow);
			Add_Edge(N*2+F+i,N*2+F+D+1,maxflow);
		}
		for (int i=1;i<=N;i++)
		{
			scanf("%s",str);
			for (int j=0;j<F;j++)
				if (str[j]=='Y')
					Add_Edge(N*2+j+1,i,1);
		}
		for (int i=1;i<=N;i++)
		{
			scanf("%s",str);
			for (int j=0;j<D;j++)
				if (str[j]=='Y')
					Add_Edge(N+i,N*2+F+j+1,1);
		}
		for (int i=1;i<=N;i++)
			Add_Edge(i,N+i,1);
		int Ans=0;
		while (bfs())
		{
			for (int i=0;i<=2*N+F+D+1;i++)
				cur[i]=Head[i];
			while (int di=dfs(0,inf))
				Ans+=di;
		}
		cout<<Ans<<endl;
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
	depth[0]=1;
	Q[1]=0;
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
	if (depth[N*2+F+D+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==N*2+F+D+1)
		return flow;
	for (int i=Head[u];i!=-1;i=Next[i])
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
