#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=203*2;
const int maxM=20010*2+maxN*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Q[maxM],Dist[maxN],Flow[maxN],Path[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&m);S=1;T=n+n;
    for (int i=2;i<n;i++) Add_Edge(i,i+n,1,0),Add_Edge(i+n,i,0,0),Add_Edge(i+n,i,1,0),Add_Edge(i,i+n,0,0);
    Add_Edge(1,1+n,inf,0);Add_Edge(n,n+n,inf,0);
    for (int i=1;i<=m;i++)
    {
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u+n,v,1,w);Add_Edge(v,u+n,0,-w);
    }
    int mxflow=0,Ans=0;
    while (Spfa())
    {
	int now=T;
	while (now!=S)
	{
	    E[Path[now]].flow-=Flow[T];
	    E[Path[now]^1].flow+=Flow[T];
	    now=E[Path[now]].u;
	}
	mxflow+=Flow[T];
	Ans+=Flow[T]*Dist[T];
    }
    printf("%d %d\n",mxflow,Ans);
    return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].flow=flow;E[edgecnt].w=w;
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(vis,0);mem(Flow,0);
    int h=1,t=0;Q[1]=S;Dist[S]=0;Flow[S]=inf;vis[S]=1;
    do
    {
	int u=Q[++t];vis[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((E[i].flow>0)&&((Dist[v]==-1)||(Dist[v]>Dist[u]+E[i].w)))
	    {
		Dist[v]=Dist[u]+E[i].w;Flow[v]=min(Flow[u],E[i].flow);Path[v]=i;
		if (vis[v]==0) vis[Q[++h]=v]=1;
	    }
	}
    }
    while (t!=h);
    //for (int i=1;i<=n;i++) cout<<Dist[i]<<" ";cout<<endl;
    //for (int i=1;i<=n;i++) cout<<Flow[i]<<" ";cout<<endl;
    if (Dist[T]==-1) return 0;
    return 1;
}
