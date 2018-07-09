#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=maxN*maxN*10;
const int inf=47483647;

class Edge
{
public:
	int v,flow;
};

int n;
int S,T,SS,TT;
int edgecnt=-1,Head[maxN],Next[maxM],Sum[maxN],Depth[maxN],Q[maxN],cur[maxN];
Edge E[maxM];

void Add_Edge(int u,int v,int flow);
int Dinic();
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);S=n+1;T=n+2;SS=n+3;TT=n+4;
	for (int i=1;i<=n;i++)
	{
		int C;scanf("%d",&C);
		while (C--)
		{
			int v;scanf("%d",&v);
			Sum[v]++;Sum[i]--;
			Add_Edge(i,v,inf);
		}
	}

	for (int i=1;i<=n;i++) Add_Edge(S,i,inf),Add_Edge(i,T,inf);

	int sum=0;
	for (int i=1;i<=T;i++)
		if (Sum[i]>0) Add_Edge(SS,i,Sum[i]);
		else if (Sum[i]<0) Add_Edge(i,TT,-Sum[i]);
	Dinic();
	Add_Edge(T,S,inf);
	int Ans=Dinic();

	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

int Dinic()
{
	int Ret=0;
	while (Bfs())
	{
		for (int i=1;i<=TT;i++) cur[i]=Head[i];
		while (int di=dfs(SS,inf)) Ret+=di;
	}
	return Ret;
}

bool Bfs()
{
	mem(Depth,-1);Depth[SS]=1;Q[1]=SS;
	int h=1,t=0;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[TT]!=-1;
}

int dfs(int u,int flow)
{
	if (u==TT) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow)&&(Depth[E[i].v]==Depth[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow))){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}
