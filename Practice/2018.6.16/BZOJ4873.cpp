#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=151;
const int maxN=maxMap*maxMap;
const int maxM=maxN*20;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m;
int D[maxMap][maxMap],Id[maxMap][maxMap],A[maxN];
bool vis[maxN];
int S=1,T=2,nodecnt=2;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Q[maxN],Depth[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	for (int i=1;i<=n;i++) for (int j=i;j<=n;j++) scanf("%d",&D[i][j]),Id[i][j]=++nodecnt;
	int Ans=0;
	for (int i=1;i<=n;i++)
		if (vis[i]==0)
		{
			Add_Edge(++nodecnt,T,m*A[i]*A[i]);//vis[i]=1;
			for (int j=i;j<=n;j++)
				if ((vis[j]==0)&&(A[i]==A[j])) Add_Edge(Id[j][j],nodecnt,inf),vis[j]=1;
		}
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j++)
		{
			int x=D[i][j];
			if (i<j) Add_Edge(Id[i][j],Id[i][j-1],inf),Add_Edge(Id[i][j],Id[i+1][j],inf);
			else x-=A[i];
			if (x>0) Ans+=x,Add_Edge(S,Id[i][j],x);
			if (x<0) Add_Edge(Id[i][j],T,-x);
		}
	//cout<<"Sum:"<<Ans<<endl;

	while (Bfs())
	{
		for (int i=1;i<=nodecnt;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) Ans-=di;
	}

	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

bool Bfs()
{
	mem(Depth,-1);Depth[S]=1;Q[1]=S;
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
