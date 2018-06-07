#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=101;
const int maxN=maxMap*maxMap*2;
const int maxM=(maxMap*maxMap*6)*2;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m;
int S,T;
int A[maxMap][maxMap],B[maxMap][maxMap],C[maxMap][maxMap],Id[maxMap][maxMap];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Queue[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow,int opt);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&A[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&B[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&C[i][j]);
	int idcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt;
	S=idcnt+1;T=idcnt+2;
	int Ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if ((i+j)&1)
			{
				Add_Edge(S,Id[i][j],A[i][j],0);
				Add_Edge(Id[i][j],T,B[i][j],0);
				Ans+=A[i][j]+B[i][j];
				if (i!=1) Add_Edge(Id[i][j],Id[i-1][j],C[i][j]+C[i-1][j],1),Ans+=C[i][j]+C[i-1][j];
				if (i!=n) Add_Edge(Id[i][j],Id[i+1][j],C[i][j]+C[i+1][j],1),Ans+=C[i][j]+C[i+1][j];
				if (j!=1) Add_Edge(Id[i][j],Id[i][j-1],C[i][j]+C[i][j-1],1),Ans+=C[i][j]+C[i][j-1];
				if (j!=m) Add_Edge(Id[i][j],Id[i][j+1],C[i][j]+C[i][j+1],1),Ans+=C[i][j]+C[i][j+1];
			}
			else
			{
				Add_Edge(S,Id[i][j],B[i][j],0);
				Add_Edge(Id[i][j],T,A[i][j],0);
				Ans+=A[i][j]+B[i][j];
			}
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) Ans-=di;
	}
	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int flow,int opt)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].flow=opt*flow;
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
			if ((Depth[E[i].v]==-1)&&(E[i].flow>0))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
	}
	while (t!=h);
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
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
