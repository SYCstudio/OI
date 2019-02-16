#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=41;
const int maxN=maxMap*maxMap*maxMap;
const int maxM=maxN*5*2;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int P,Q,R,S,T,D;
int Mat[maxMap][maxMap][maxMap],Id[maxMap][maxMap][maxMap];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],cur[maxN],Queue[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int fa);

int main()
{
	ios::sync_with_stdio(false);mem(Head,-1);

	cin>>P>>Q>>R>>D;
	for (int k=1;k<=R;k++)
		for (int i=1;i<=P;i++)
			for (int j=1;j<=Q;j++)
				cin>>Mat[i][j][k];

	int idcnt=0;
	for (int i=1;i<=P;i++) for (int j=1;j<=Q;j++) for (int k=1;k<=R;k++) Id[i][j][k]=++idcnt;
	S=++idcnt;T=++idcnt;
	for (int i=1;i<=P;i++) for (int j=1;j<=Q;j++) Add_Edge(S,Id[i][j][1],Mat[i][j][1]);
	for (int k=1;k<R;k++)
		for (int i=1;i<=P;i++)
			for (int j=1;j<=Q;j++)
			{
				Add_Edge(Id[i][j][k],Id[i][j][k+1],Mat[i][j][k+1]);
				if (k-D<0) continue;
				if (i!=1) Add_Edge(Id[i][j][k],Id[i-1][j][k-D],inf);
				if (i!=P) Add_Edge(Id[i][j][k],Id[i+1][j][k-D],inf);
				if (j!=1) Add_Edge(Id[i][j][k],Id[i][j-1][k-D],inf);
				if (j!=Q) Add_Edge(Id[i][j][k],Id[i][j+1][k-D],inf);
			}
	for (int i=1;i<=P;i++) for (int j=1;j<=Q;j++) Add_Edge(Id[i][j][R],T,Mat[i][j][R]);
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
				E[i].flow-=di;E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
