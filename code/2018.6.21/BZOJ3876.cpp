#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int maxM=10010*10;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow,w;
};

int n,S,T,SS,TT;
int edgecnt=-1,Head[maxN],Next[maxM],Sum[maxN];
Edge E[maxM];
int Dist[maxN],Path[maxN],Flow[maxN];
queue<int> Q;
bool inq[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool spfa();

int main()
{
	mem(Head,-1);int Ans=0;
	scanf("%d",&n);S=1;T=n+1;SS=T+1;TT=SS+1;
	for (int i=1;i<=n;i++)
	{
		int K;scanf("%d",&K);
		for (int j=1;j<=K;j++)
		{
			int v,t;scanf("%d%d",&v,&t);
			Sum[i]-=1;Sum[v]+=1;
			Add_Edge(i,v,inf,t);Ans+=t;
		}
	}
	for (int i=2;i<=n;i++) Add_Edge(i,T,inf,0);

	for (int i=1;i<=n;i++)
		if (Sum[i]>0) Add_Edge(SS,i,Sum[i],0);
		else if (Sum[i]<0) Add_Edge(i,TT,-Sum[i],0);
	Add_Edge(T,S,inf,0);

	while (spfa())
	{
		Ans=Ans+Flow[TT]*Dist[TT];
		int now=TT;
		while (now!=SS){
			E[Path[now]].flow-=Flow[TT];E[Path[now]^1].flow+=Flow[TT];now=E[Path[now]].u;
		}
	}

	printf("%d\n",Ans);

	return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){u,v,flow,w});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){v,u,0,-w});
	return;
}

bool spfa()
{
	for (int i=1;i<=TT;i++) Dist[i]=inf;mem(inq,0);
	Q.push(SS);Dist[SS]=0;inq[SS]=1;Flow[SS]=inf;
	do
	{
		int u=Q.front();Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Dist[E[i].v]>Dist[u]+E[i].w))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
				if (inq[E[i].v]==0){
					inq[E[i].v]=1;Q.push(E[i].v);
				}
			}
		inq[u]=0;
	}
	while (!Q.empty());
	return Dist[TT]!=inf;
}
