#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int maxM=(maxN*maxN+maxN)*2;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Queue[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	ios::sync_with_stdio(false);mem(Head,-1);

	cin>>n>>m;S=n+1;T=n+2;
	for (int i=1;i<=n;i++)
	{
		int opt;cin>>opt;
		if (opt==0) Add_Edge(S,i,1);
		else Add_Edge(i,T,1);
	}
	for (int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		Add_Edge(u,v,1);Add_Edge(v,u,1);
	}
	int Ans=0;
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) Ans+=di;
	}
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].flow=0;
	return;
}

bool Bfs()
{
	mem(Depth,-1);
	int h=1,t=0;Queue[1]=S;Depth[S]=1;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
	}
	while (h!=t);
	if (Depth[T]==-1) return 0;
	return 1;
}

int dfs(int u,int flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
		{
			int di=dfs(E[i].v,min(flow,E[i].flow));
			if (di)
			{
				E[i].flow-=di;E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
