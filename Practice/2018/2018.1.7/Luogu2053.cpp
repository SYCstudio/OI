#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxPeople=61;
const int maxRep=10;
const int maxN=maxRep*maxPeople+maxPeople;
const int maxM=(maxPeople*maxN)*10;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow,w;
};

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Id[maxRep][maxPeople];
int Queue[maxN],Dist[maxN],Flow[maxN],Path[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,int w);
void _Add(int u,int v,int flow,int w);
bool Spfa();

int main()
{
	mem(Head,-1);
	scanf("%d%d",&m,&n);S=n+n*m+1;T=n+n*m+2;
	int idcnt=n;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			Id[i][j]=++idcnt;
	for (int i=1;i<=n;i++) Add_Edge(S,i,1,0);
	for (int i=1;i<=m;i++) for (int j=1;j<=n;j++) Add_Edge(Id[i][j],T,1,0); 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int tim;scanf("%d",&tim);
			for (int k=1;k<=n;k++) Add_Edge(i,Id[j][k],1,k*tim);
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
		Ans=Ans+Dist[T]*Flow[T];
	}
	printf("%.2LF\n",(long double)(Ans)/n);
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
		++t;if (t>=maxN) t=0;
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
