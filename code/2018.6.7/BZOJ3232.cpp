#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=51;
const int maxN=maxMap*maxMap;
const int maxM=maxN*20;
const ld eps=1e-6;
const int inf=2147483647;

class Edge
{
public:
	int v;
	ld flow;
};

int n,m;
int S,T;
int Sum=0;
int V[maxMap][maxMap],C1[maxMap][maxMap],C2[maxMap][maxMap],Id[maxMap][maxMap];
int edgecnt,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

bool Check(ld k);
void Add_Edge(int u,int v,ld flow,int opt);
bool Bfs();
ld dfs(int u,ld flow);

int main()
{
	//freopen("2.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&V[i][j]),Sum+=V[i][j];
	for (int i=1;i<=n+1;i++) for (int j=1;j<=m;j++) scanf("%d",&C1[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=m+1;j++) scanf("%d",&C2[i][j]);
	for (int i=1,idcnt=0;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt;
	S=n*m+1;T=S+1;
	ld L=0,R=100.0*n*m,Ans;
	do
	{
		//cout<<"("<<L<<","<<R<<")"<<endl;
		ld mid=(L+R)/2.0;
		if (Check(mid)) Ans=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);
	printf("%.3LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,ld flow,int opt)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,flow*opt});
	return;
}

bool Check(ld k)
{
	edgecnt=-1;mem(Head,-1);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Add_Edge(S,Id[i][j],V[i][j],0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (i!=n) Add_Edge(Id[i][j],Id[i+1][j],k*C1[i+1][j],1);
			if (j!=m) Add_Edge(Id[i][j],Id[i][j+1],k*C2[i][j+1],1);
		}
	for (int i=1;i<=n;i++) Add_Edge(Id[i][1],T,k*C2[i][1],0),Add_Edge(Id[i][m],T,k*C2[i][m+1],0);
	for (int i=1;i<=m;i++) Add_Edge(Id[1][i],T,k*C1[1][i],0),Add_Edge(Id[n][i],T,k*C1[n+1][i],0);

	//for (int i=1;i<=T;i++) for (int j=Head[i];j!=-1;j=Next[j]) if (E[j].flow) cout<<i<<" -> "<<E[j].v<<" "<<E[j].flow<<endl;
	//cout<<"Build over!"<<endl;
	
	ld mxflow=0;
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (ld di=dfs(S,inf)) mxflow+=di/*,cout<<di<<" "*/;
	}
	//cout<<endl;

	//cout<<mxflow<<endl;

	return Sum-mxflow>eps;
}

bool Bfs()
{
	mem(Depth,-1);
	Depth[S]=1;
	int h=1,t=0;Q[1]=S;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>eps)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

ld dfs(int u,ld flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>eps)&&(Depth[E[i].v]==Depth[u]+1))
		{
			ld di=dfs(E[i].v,min(flow,E[i].flow));
			if (di>eps)
			{
				E[i].flow-=di;E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}

