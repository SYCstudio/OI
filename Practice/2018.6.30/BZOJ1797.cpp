#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=4010;
const int maxM=60100*4;
const int inf=2147483647;

class Edge
{
public:
	int v,flow,id;
};

int n,m;
int S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Q[maxN],Depth[maxN],cur[maxN];
int dfncnt,dfn[maxN],low[maxN],idcnt,Id[maxN];
int top,St[maxN];
bool ink[maxN];

void Add_Edge(int u,int v,int flow,int id);
bool Bfs();
int dfs(int u,int flow);
void tarjan(int u);

int main()
{
	mem(Head,-1);
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w,i);
	}

	while (Bfs())
	{
		for (int i=1;i<=n;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) ;
	}

	for (int i=1;i<=n;i++) if (dfn[i]==0) tarjan(i);

	for (int i=0;i<=edgecnt;i+=2)
	{
		if (E[i].flow==0)
		{
			if (Id[E[i].v]!=Id[E[i^1].v]) printf("1 ");
			else printf("0 ");
			if ((Id[E[i].v]==Id[T])&&(Id[E[i^1].v]==Id[S])) printf("1\n");
			else printf("0\n");
		}
		else printf("0 0\n");
	}
	return 0;
}

void Add_Edge(int u,int v,int flow,int id)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,id});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

bool Bfs()
{
	mem(Depth,-1);Q[1]=S;Depth[S]=1;
	int h=1,t=0;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

int dfs(int u,int flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow))){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++dfncnt;
	St[++top]=u;ink[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (E[i].flow>0)
		{
			if (dfn[E[i].v]==0){
				tarjan(E[i].v);low[u]=min(low[u],low[E[i].v]);
			}
			else if (ink[E[i].v]) low[u]=min(low[u],dfn[E[i].v]);
		}
	if (dfn[u]==low[u])
	{
		int v;idcnt++;
		do v=St[top--],ink[v]=0,Id[v]=idcnt;
		while (v!=u);
	}
	return;
}
