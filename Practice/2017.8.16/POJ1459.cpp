#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=300;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow;
};

int n,np,nc;
int m;
int cnt=-1;
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
	while (cin>>n>>np>>nc>>m)
	{
		cnt=-1;
		memset(Head,-1,sizeof(Head));
		while (m--)
		{
			int u,v,w;
			while (getchar()!='(');
			scanf("%d,%d)%d",&u,&v,&w);
			Add_Edge(u+1,v+1,w);
		}
		while (np--)
		{
			int u,maxflow;
			while (getchar()!='(');
			scanf("%d)%d",&u,&maxflow);
			Add_Edge(0,u+1,maxflow);
		}
		while (nc--)
		{
			int u,maxflow;
			while (getchar()!='(');
			scanf("%d)%d",&u,&maxflow);
			Add_Edge(u+1,n+1,maxflow);
		}
		/*for (int i=0;i<=n+1;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
				cout<<i<<" "<<E[j].v<<" "<<E[j].flow<<endl;
			cout<<endl;
		}
		//*/
		int Ans=0;
		while (bfs())
		{
			for (int i=0;i<=n+1;i++)
				cur[i]=Head[i];
			while (int di=dfs(0,inf))
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
			if ((E[i].flow>0)&&(depth[v]==-1))
			{
				depth[v]=depth[u]+1;
				h++;
				Q[h]=v;
			}
		}
	}
	while (t!=h);
	if (depth[n+1]==-1)
		return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==n+1)
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
