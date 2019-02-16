#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=600*2;
const int maxM=maxN*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow,w;
};

int n,m,K;
int Inx[maxN],Iny[maxN];
int Number[maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
map<int,int> Map;
int Dist[maxN],Path[maxN],Q[maxM],Flow[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int flow,int w);
void _Add(int u,int v,int flow,int w);
bool Spfa();

int main()
{
    Map.clear();mem(Head,-1);
    scanf("%d%d",&m,&K);
    for (int i=1;i<=m;i++)
    {
	scanf("%d%d",&Inx[i],&Iny[i]);
	if (Iny[i]<Inx[i]) swap(Iny[i],Inx[i]);
	if (Map[Inx[i]]==0) Map[Inx[i]]=1,Number[++n]=Inx[i];
	if (Map[Iny[i]]==0) Map[Iny[i]]=1,Number[++n]=Iny[i];
    }
    sort(&Number[1],&Number[n+1]);
    for (int i=1;i<=n;i++) Map[Number[i]]=i;
    for (int i=1;i<n;i++) Add_Edge(i,i+1,K,0);
    for (int i=1;i<=m;i++) Add_Edge(Map[Inx[i]],Map[Iny[i]],1,Iny[i]-Inx[i]);
    Add_Edge(0,1,K,0);
    Add_Edge(n,n+1,K,0);
    int Ans=0;
    while (Spfa())
    {
	int now=n+1,minflow=Flow[n+1];
	while (now!=1)
	{
	    E[Path[now]].flow-=minflow;
	    E[Path[now]^1].flow+=minflow;
	    now=E[Path[now]].u;
	}
	Ans=Ans+minflow*Dist[n+1];
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
    mem(Dist,-1);mem(vis,0);mem(Flow,0);
    int h=1,t=0;Q[1]=0;Dist[0]=0;vis[0]=1;Flow[0]=inf;
    do
    {
	int u=Q[++t];vis[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((E[i].flow>0)&&((E[i].w+Dist[u]>Dist[v])||(Dist[v]==-1)))
	    {
		Dist[v]=Dist[u]+E[i].w;Path[v]=i;Flow[v]=min(Flow[u],E[i].flow);
		if (vis[v]==0) vis[Q[++h]=v]=1;
	    }
	}
    }
    while (t!=h);
    if (Dist[n+1]==-1) return 0;
    return 1;
}
