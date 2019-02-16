#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y) ((x-1)*Q+y)

const int maxMap=18;
const int maxN=maxMap*maxMap;
const int maxM=maxN*100;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

int P,Q,S,T,na,nb;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Queue[maxN],Dist[maxN],Flow[maxN],Path[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,int w);
void _Add(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    mem(Head,-1);
    scanf("%d%d",&na,&nb);
    scanf("%d%d",&P,&Q);P++;Q++;
    S=P*Q+1;T=P*Q+2;
    for (int i=1;i<=P;i++)
		for (int j=1;j<Q;j++)
		{
			int w;scanf("%d",&w);
			Add_Edge(Id(i,j),Id(i,j+1),1,w);
			Add_Edge(Id(i,j),Id(i,j+1),inf,0);
		}
    for (int i=1;i<=Q;i++)
		for (int j=1;j<P;j++)
		{
			int w;scanf("%d",&w);
			Add_Edge(Id(j,i),Id(j+1,i),1,w);
			Add_Edge(Id(j,i),Id(j+1,i),inf,0);
		}
    for (int i=1;i<=na;i++)
    {
		int k,x,y;scanf("%d%d%d",&k,&x,&y);x++;y++;
		Add_Edge(S,Id(x,y),k,0);
    }
    for (int i=1;i<=nb;i++)
    {
		int k,x,y;scanf("%d%d%d",&k,&x,&y);x++;y++;
		Add_Edge(Id(x,y),T,k,0);
    }
    int Ans=0;
    while (Spfa())
    {
		int now=T;
		while (now!=S)
		{
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]].u;
		}
		Ans+=Flow[T]*Dist[T];
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
			if ((E[i].flow>0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]<Dist[u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				if (inqueue[E[i].v]==0)
				{
					h++;if (h>=maxN) h=0;
					inqueue[Queue[h]=E[i].v]=1;
				}
			}
    }
    while (t!=h);
    if (Dist[T]==-1) return 0;
    return 1;
}
