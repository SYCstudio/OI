#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int maxM=maxN*300;
const int inf=100000000;

class Edge
{
public:
	int v,flow;
};

class EDGE
{
public:
	int u,v,l,r,id;
};

int n,m;
int edgecnt,ecnt,Head[maxN],Next[maxM],Sum[maxN];
int Id[maxM];
Edge E[maxM];
EDGE EE[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
int Dinic(int S,int T);
bool Bfs(int S,int T);
int dfs(int u,int flow,int T);

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		edgecnt=-1;ecnt=0;mem(Head,-1);mem(Sum,0);mem(Id,0);
		int S=n+m+1,T=S+1,SS=T+1,TT=SS+1,qcnt=0,sum=0;
		for (int i=1;i<=m;i++)
		{
			int key;scanf("%d",&key);
			EE[++ecnt]=((EDGE){i+n,T,key,inf});
		}
		for (int i=1;i<=n;i++)
		{
			int C,D;scanf("%d%d",&C,&D);
			EE[++ecnt]=((EDGE){S,i,0,D});
			for (int j=1;j<=C;j++)
			{
				int t,l,r;scanf("%d%d%d",&t,&l,&r);
				EE[Id[++qcnt]=++ecnt]=((EDGE){i,t+n+1,l,r});
			}
		}
		//for (int i=1;i<=ecnt;i++)
		//	cout<<EE[i].u<<" "<<EE[i].v<<" ["<<EE[i].l<<","<<EE[i].r<<"]"<<endl;

		for (int i=1;i<=ecnt;i++)
		{
			EE[i].id=edgecnt+1;
			Add_Edge(EE[i].u,EE[i].v,EE[i].r-EE[i].l);
			Sum[EE[i].v]+=EE[i].l;Sum[EE[i].u]-=EE[i].l;
		}
		for (int i=1;i<=T;i++)
			if (Sum[i]>0) Add_Edge(SS,i,Sum[i]),sum+=Sum[i];
			else Add_Edge(i,TT,-Sum[i]);

		Add_Edge(T,S,inf);
		if (Dinic(SS,TT)!=sum){
			printf("-1\n\n");continue;
		}

		int mxflow=0;
		Dinic(S,T);Add_Edge(T,S,-inf);
		for (int i=Head[S];i!=-1;i=Next[i])
			mxflow+=E[i^1].flow;

		printf("%d\n",mxflow);
		for (int i=1;i<=qcnt;i++) printf("%d\n",E[EE[Id[i]].id^1].flow+EE[Id[i]].l);
		printf("\n");
	}
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
	return;
}

int Dinic(int S,int T)
{
	int Ret=0;
	while (Bfs(S,T))
	{
		for (int i=1;i<=T+1;i++) cur[i]=Head[i];
		while (int di=dfs(S,inf,T)) Ret+=di;
	}
	return Ret;
}

bool Bfs(int S,int T)
{
	mem(Depth,-1);Depth[S]=1;
	int h=1,t=0;Q[1]=S;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

int dfs(int u,int flow,int T)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow),T)){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}
