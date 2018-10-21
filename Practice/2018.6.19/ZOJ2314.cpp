#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=250;
const int maxM=maxN*maxN*5;
const int inf=2147483647;

class Edge
{
public:
	int v,flow,cap;
};

class EDGE
{
public:
	int u,v,l,r,id;
};

int n,m;
int SS,TT;
int edgecnt,Head[maxN],Next[maxM];
int Sum[maxN];
Edge E[maxM];
EDGE EE[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		scanf("%d%d",&n,&m);
		edgecnt=-1;mem(Head,-1);mem(Sum,0);
		SS=n+1;TT=n+2;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d%d",&EE[i].u,&EE[i].v,&EE[i].l,&EE[i].r);
			EE[i].id=edgecnt+1;
			Add_Edge(EE[i].u,EE[i].v,EE[i].r-EE[i].l);
			Sum[EE[i].v]+=EE[i].l;Sum[EE[i].u]-=EE[i].l;
		}
		int sum1=0,sum2=0;
		for (int i=1;i<=n;i++)
			if (Sum[i]>=0) Add_Edge(SS,i,Sum[i]),sum1+=Sum[i];
			else Add_Edge(i,TT,-Sum[i]),sum2-=Sum[i];
		//cout<<"Init finish sum:"<<sum1<<" "<<sum2<<endl;
		//for (int i=1;i<=n;i++) cout<<Sum[i]<<" ";cout<<endl;
		
		int mxflow=0;
		while (Bfs())
		{
			for (int i=1;i<=TT;i++) cur[i]=Head[i];
			while (int di=dfs(SS,inf)) mxflow+=di;
		}

		if (mxflow!=sum1) printf("NO\n");
		else
		{
			printf("YES\n");
			for (int i=1;i<=m;i++) printf("%d\n",EE[i].l+E[EE[i].id].cap-E[EE[i].id].flow);
		}

		if (TTT) printf("\n");
	}
	return 0;
}

void Add_Edge(int u,int v,int flow)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,0});
	return;
}

bool Bfs()
{
	mem(Depth,-1);
	int h=1,t=0;Depth[SS]=1;Q[1]=SS;
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
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
		{
			int di=dfs(E[i].v,min(flow,E[i].flow));
			if (di){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
