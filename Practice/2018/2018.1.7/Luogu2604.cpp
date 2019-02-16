#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=5010*2*2;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

int n,m,S,T,K;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN],Queue[maxN],Flow[maxN],Path[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,int w);
void _Add(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&K);S=1;T=n;
    for (int i=1;i<=m;i++)
    {
	int u,v,c,w;scanf("%d%d%d%d",&u,&v,&c,&w);
	Add_Edge(u,v,c,0);
	Add_Edge(u,v,0,w);
    }
    int flow=0;
    while(Spfa())
    {
	int now=T;
	while (now!=S)
	{
	    E[Path[now]].flow-=Flow[T];
	    E[Path[now]^1].flow+=Flow[T];
	    now=E[Path[now]].u;
	}
	flow+=Flow[T];
    }
    printf("%d ",flow);
    flow=0;int Ans=0;
    while (flow<K)
    {
	for (int i=0;i<=edgecnt;i++) if (E[i].w>0) E[i].flow=E[i].flow+K;
	while (Spfa())
	{
	    int now=T;
	    while (now!=S)
	    {
		E[Path[now]].flow-=Flow[T];
		E[Path[now]^1].flow+=Flow[T];
		now=E[Path[now]].u;
	    }
	    if (flow+Flow[T]>K) Flow[T]=K-flow;
	    Ans=Ans+Flow[T]*Dist[T];
	    flow=flow+Flow[T];
	    if (flow==K) break;
	}
    }
    printf("%d\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
    _Add(u,v,flow,w);_Add(v,u,0,-w);
    return;
}

void _Add(int u,int v,int flow,int w)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].flow=flow;E[edgecnt].w=w;
    return;
}

bool Spfa()
{
    mem(Dist,-1);mem(inqueue,0);
    int h=1,t=0;Queue[1]=S;Dist[S]=0;Flow[S]=inf;inqueue[S]=1;
    do
    {
	t++;if (t>=maxN) t=0;
	int u=Queue[t];inqueue[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	    if ((E[i].flow>0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u]+E[i].w)))
	    {
		Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
		if (inqueue[E[i].v]==0)
		{
		    inqueue[E[i].v]=1;
		    h++;if (h>=maxN) h=0;
		    Queue[h]=E[i].v;
		}
	    }
    }
    while (t!=h);
    if (Dist[T]==-1) return 0;
    return 1;
}
