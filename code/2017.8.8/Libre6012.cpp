#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=300;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
	int u,v,cost,flow;
};

int n;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Dist[maxN];
bool inqueue[maxN];
int Q[maxM];
int Path[maxN];
int Flow[maxN];
int G[maxN][maxN];

void Add_Edge(int u,int v,int cost,int flow);
bool spfa1();
bool spfa2();

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&G[i][j]);
	//Q1
	cnt=-1;
	memset(Head,-1,sizeof(Head));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			Add_Edge(i,j+n,G[i][j],1);
	for (int i=1;i<=n;i++)
	{
		Add_Edge(0,i,0,1);
		Add_Edge(i+n,n*2+1,0,1);
	}
	int Ans=0;
	while (spfa1())
	{
		int now=n*2+1;
		int last=Path[now];
		while (now!=0)
		{
			E[last].flow-=Flow[n*2+1];
			E[last^1].flow+=Flow[n*2+1];
			now=E[last].u;
			last=Path[now];
		}
		Ans+=Dist[n*2+1]*Flow[n*2+1];
	}
	cout<<Ans<<endl;
	//Q2
	cnt=-1;
	memset(Head,-1,sizeof(Head));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			Add_Edge(i,j+n,G[i][j],1);
	for (int i=1;i<=n;i++)
	{
		Add_Edge(0,i,0,1);
		Add_Edge(i+n,n*2+1,0,1);
	}
	Ans=0;
	while (spfa2())
	{
		int now=n*2+1;
		int last=Path[now];
		while (now!=0)
		{
			E[last].flow-=Flow[n*2+1];
			E[last^1].flow+=Flow[n*2+1];
			now=E[last].u;
			last=Path[now];
		}
		Ans+=Dist[n*2+1]*Flow[n*2+1];
	}
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int cost,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].cost=cost;
	E[cnt].flow=flow;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].u=v;
	E[cnt].v=u;
	E[cnt].flow=0;
	E[cnt].cost=-cost;
}

bool spfa1()
{
	for (int i=0;i<=n*2+1;i++)
		Dist[i]=inf;
	memset(inqueue,0,sizeof(inqueue));
	int h=1,t=0;
	Q[1]=0;
	inqueue[0]=1;
	Dist[0]=0;
	Flow[0]=inf;
	do
	{
		t++;
		int u=Q[t];
		inqueue[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&(Dist[v]>Dist[u]+E[i].cost))
			{
				Dist[v]=Dist[u]+E[i].cost;
				Flow[v]=min(Flow[u],E[i].flow);
				Path[v]=i;
				if (inqueue[v]==0)
				{
					h++;
					Q[h]=v;
					inqueue[v]=1;
				}
			}
		}
	}
	while (h!=t);
	if (Dist[n*2+1]==inf)
		return 0;
	return 1;
}

bool spfa2()
{
	for (int i=0;i<=n*2+1;i++)
		Dist[i]=-inf;
	memset(inqueue,0,sizeof(inqueue));
	int h=1,t=0;
	Q[1]=0;
	inqueue[0]=1;
	Dist[0]=0;
	Flow[0]=inf;
	do
	{
		t++;
		int u=Q[t];
		inqueue[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&(Dist[v]<Dist[u]+E[i].cost))
			{
				Dist[v]=Dist[u]+E[i].cost;
				Flow[v]=min(Flow[u],E[i].flow);
				Path[v]=i;
				if (inqueue[v]==0)
				{
					h++;
					Q[h]=v;
					inqueue[v]=1;
				}
			}
		}
	}
	while (h!=t);
	if (Dist[n*2+1]==-inf)
		return 0;
	return 1;
}
