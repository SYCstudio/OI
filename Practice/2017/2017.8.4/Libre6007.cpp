#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define pos(x,y) (x-1)*n+y

const int maxN=40;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,m;
int cnt=-1;
int Mat[maxN][maxN];
int Head[maxN*maxN];
int Next[maxN*maxN*maxN*maxN];
Edge E[maxN*maxN*maxN*maxN];
int depth[maxN*maxN];
int cur[maxN*maxN];
int Q[maxN*maxN*maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
	memset(Head,-1,sizeof(Head));
	int sum=0;
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
		{
			int num;
			scanf("%d",&num);
			sum+=num;
			if (i%2==j%2)
			{
				Add_Edge(0,pos(i,j),num);
				if (i!=1)
					Add_Edge(pos(i,j),pos(i-1,j),inf);
				if (i!=m)
					Add_Edge(pos(i,j),pos(i+1,j),inf);
				if (j!=1)
					Add_Edge(pos(i,j),pos(i,j-1),inf);
				if (j!=n)
					Add_Edge(pos(i,j),pos(i,j+1),inf);
			}
			else
				Add_Edge(pos(i,j),n*m+1,num);
		}
	int Ans=0;
	while (bfs())
	{
	    memcpy(cur,Head,sizeof(cur));
		while (int di=dfs(0,inf))
			Ans+=di;
	}
	cout<<sum-Ans<<endl;
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
			if ((E[i].flow>0)&&(depth[v]==-1))
			{
				h++;
				Q[h]=v;
				depth[v]=depth[u]+1;
			}
		}
	}
	while (t!=h);
	if (depth[n*m+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==n*m+1)
		return flow;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if ((E[i].flow>0)&&(depth[v]==depth[u]+1))
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
