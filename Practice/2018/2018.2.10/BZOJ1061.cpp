#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=(10100+maxN*2)*2;
const int maxQueue=maxN*10;
const int inf=2147483647;
const ll INF=1e15;

class Edge
{
public:
	ll u,v,flow,w;
};

int n,m,S,T;
int Pl[maxN];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
ll Dist[maxN],inqueue[maxN],Queue[maxQueue];
ll Flow[maxN],Path[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool spfa();

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);S=n+2;T=n+3;
	for (int i=1;i<=n;i++) scanf("%d",&Pl[i]);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v+1,inf,w);
	}
	for (int i=1;i<=n+1;i++)
	{
		int p=Pl[i]-Pl[i-1];
		if (p>=0) Add_Edge(S,i,p,0);
		if (p<0) Add_Edge(i,T,-p,0);
		if (i>1) Add_Edge(i,i-1,inf,0);
	}
	ll Ans=0;
	while (spfa())
	{
		Ans=Ans+Dist[T]*Flow[T];
		int now=T;
		while (now!=S)
		{
			E[Path[now]].flow-=Flow[T];
			E[Path[now]^1].flow+=Flow[T];
			now=E[Path[now]].u;
		}
	}
	printf("%lld\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
	//cout<<"Add:"<<u<<" "<<v<<" "<<flow<<" "<<w<<endl;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].w=w;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].u=v;E[edgecnt].v=u;E[edgecnt].w=-w;E[edgecnt].flow=0;
	return;
}

bool spfa()
{
	mem(inqueue,0);
	for (int i=1;i<=T;i++) Dist[i]=INF;
	int h=1,t=0;Queue[1]=S;Dist[S]=0;inqueue[S]=1;Flow[S]=inf;
	do
	{
		t++;if (t>=maxQueue) t=0;
		int u=Queue[t];
		//cout<<"u:"<<u<<endl;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			//cout<<u<<" "<<E[i].v<<" "<<E[i].flow<<" "<<E[i].w<<endl;
			if ((E[i].flow>0)&&(Dist[E[i].v]>Dist[u]+E[i].w))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;
				Path[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
				if (inqueue[E[i].v]==0)
				{
					h++;if (h>=maxQueue) h=0;
					inqueue[Queue[h]=E[i].v]=1;
				}
			}
		}
		inqueue[u]=0;
	}
	while (t!=h);
	//for (int i=1;i<=T;i++) cout<<Dist[i]<<" ";cout<<endl;
	if (Dist[T]==INF) return 0;
	return 1;
}
