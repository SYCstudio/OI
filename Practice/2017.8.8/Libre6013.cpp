#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxN=250;
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
int Flow[maxN];
int Path[maxN];
bool inqueue[maxN];
int Q[maxM];

void Add_Edge(int u,int v,int cost,int flow);
bool spfa();

int main()
{
	memset(Head,-1,sizeof(Head));
	int sum=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		int num;
		scanf("%d",&num);
		sum+=num;
		Add_Edge(0,i,0,num);
		if (i==1)
			Add_Edge(1,n,1,inf);
		else
			Add_Edge(i,i-1,1,inf);
		if (i==n)
			Add_Edge(n,1,1,inf);
		else
			Add_Edge(i,i+1,1,inf);
	}
	sum=sum/n;
	for (int i=1;i<=n;i++)
		Add_Edge(i,n+1,0,sum);
	int Ans=0;
	while (spfa())
	{
		int now=n+1;
		int last=Path[now];
		while (now!=0)
		{
			E[last].flow-=Flow[n+1];
			E[last^1].flow+=Flow[n+1];
			now=E[last].u;
			last=Path[now];
		}
		Ans+=Dist[n+1]*Flow[n+1];
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
	E[cnt].flow=flow;
	E[cnt].cost=cost;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].u=v;
	E[cnt].v=u;
	E[cnt].flow=0;
	E[cnt].cost=-cost;
}

bool spfa()
{
	for (int i=0;i<=n+1;i++)
		Dist[i]=inf;
	memset(inqueue,0,sizeof(inqueue));
	Dist[0]=0;
	inqueue[0]=1;
	int h=1,t=0;
	Q[1]=0;
	Flow[0]=inf;
	do
	{
		t++;
		int u=Q[t];
		inqueue[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&(Dist[u]+E[i].cost<Dist[v]))
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
	while(h!=t);
	if (Dist[n+1]==inf)
		return 0;
	return 1;
}
