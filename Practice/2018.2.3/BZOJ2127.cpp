#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=101;
const int maxN=maxMap*maxMap;
const int maxM=maxN*100;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m,S,T;
int Mat1[maxMap][maxMap],Mat2[maxMap][maxMap],Mat3[maxMap][maxMap],Mat4[maxMap][maxMap],Mat5[maxMap][maxMap],Mat6[maxMap][maxMap],Id[maxMap][maxMap];
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
	int Ans=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mat1[i][j]),Ans+=Mat1[i][j];
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mat2[i][j]),Ans+=Mat2[i][j];
	for (int i=1;i<n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mat3[i][j]),Ans+=Mat3[i][j];
	for (int i=1;i<n;i++) for (int j=1;j<=m;j++) scanf("%d",&Mat4[i][j]),Ans+=Mat4[i][j];
	for (int i=1;i<=n;i++) for (int j=1;j<m;j++) scanf("%d",&Mat5[i][j]),Ans+=Mat5[i][j];
	for (int i=1;i<=n;i++) for (int j=1;j<m;j++) scanf("%d",&Mat6[i][j]),Ans+=Mat6[i][j];
	int idcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt;
	S=idcnt+1;T=idcnt+2;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			Add_Edge(S,Id[i][j],Mat1[i][j]*2+Mat3[i][j]+Mat3[i-1][j]+Mat5[i][j]+Mat5[i][j-1],0);
			Add_Edge(Id[i][j],T,Mat2[i][j]*2+Mat4[i][j]+Mat4[i-1][j]+Mat6[i][j]+Mat6[i][j-1],0);
			if (i!=n) Add_Edge(Id[i][j],Id[i+1][j],Mat3[i][j]+Mat4[i][j],1);
			if (j!=m) Add_Edge(Id[i][j],Id[i][j+1],Mat5[i][j]+Mat6[i][j],1);
		}
	int mxflow=0;
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf)) mxflow+=di;
	}
	printf("%d\n",Ans-mxflow/2);
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
	for(int &i=cur[u];i!=-1;i=Next[i])
		if ((Depth[E[i].v]==Depth[u]+1)&&(E[i].flow>0))
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
