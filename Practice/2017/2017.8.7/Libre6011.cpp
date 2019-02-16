#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long 

const int maxN=301;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
	int u,v,cost,flow;
};

int n,m;
int cnt=-1;
int A[maxN];
int B[maxN];
int Map[maxN][maxN];
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Dist[maxN];
int Flow[maxN];
int Q[maxM];
int Path[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int cost,int flow);
bool spfa1();
bool spfa2();

int main()
{
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++)
		scanf("%d",&A[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&B[i]);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&Map[i][j]);
	//min
	memset(Head,-1,sizeof(Head));
	cnt=-1;
	for (int i=1;i<=m;i++)
		Add_Edge(0,i,0,A[i]);
	for (int i=1;i<=n;i++)
		Add_Edge(i+m,n+m+1,0,B[i]);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			Add_Edge(i,j+m,Map[i][j],inf);
	ll Ans=0;
	while (spfa1())
	{
		//cout<<"A"<<endl;
		int now=n+m+1;
		int last=Path[now];
		while (now!=0)
		{
			E[last].flow-=Flow[n+m+1];
			E[last^1].flow+=Flow[n+m+1];
			now=E[last].u;
			last=Path[now];
		}
		Ans+=Dist[n+m+1]*Flow[n+m+1];
	}
	cout<<Ans<<endl;
	//max
	memset(Head,-1,sizeof(Head));
	cnt=-1;
	for (int i=1;i<=m;i++)
		Add_Edge(0,i,0,A[i]);
	for (int i=1;i<=n;i++)
		Add_Edge(i+m,n+m+1,0,B[i]);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++)
			Add_Edge(i,j+m,Map[i][j],inf);
	Ans=0;
	while (spfa2())
	{
		int now=n+m+1;
		int last=Path[now];
		while (now!=0)
		{
			E[last].flow-=Flow[n+m+1];
			E[last^1].flow+=Flow[n+m+1];
			now=E[last].u;
			last=Path[now];
		}
		Ans+=Dist[n+m+1]*Flow[n+m+1];
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
	E[cnt].cost=-cost;
	E[cnt].flow=0;
}

bool spfa1()
{
	for (int i=0;i<=n+m+1;i++)
		Dist[i]=inf;
	int h=1,t=0;
	Q[1]=0;
	inqueue[0]=1;
	Flow[0]=inf;
	Dist[0]=0;
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
	if (Dist[n+m+1]==inf)
		return 0;
	return 1;
}

bool spfa2()
{
	for (int i=0;i<=n+m+1;i++)
		Dist[i]=-inf;
	int h=1,t=0;
	Q[1]=0;
	inqueue[0]=1;
	Flow[0]=inf;
	Dist[0]=0;
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
	if (Dist[n+m+1]==-inf)
		return 0;
	return 1;
}
