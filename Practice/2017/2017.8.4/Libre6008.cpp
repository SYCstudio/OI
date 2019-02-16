#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=3100;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

class Edge
{
public:
	int u,v,cost,flow;
};

int n,P,d1,c1,d2,c2;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Dist[maxN];
int path[maxN];
int Q[maxN*100];
bool inqueue[maxN];
int Flow[maxN];

void Add_Edge(int u,int v,int cost,int flow);
bool spfa();

int main()
{
	memset(Head,-1,sizeof(Head));
	scanf("%d%d%d%d%d%d",&n,&P,&d1,&c1,&d2,&c2);
	for (int i=1;i<=n;i++)
	{
		int r;
		scanf("%d",&r);
		Add_Edge(0,i,0,r);//源点到旧餐巾
		Add_Edge(0,i+n,P,inf);//从源点到新餐巾，即新购买餐巾
		Add_Edge(i+n,n*2+1,0,r);//从新餐巾到汇点，表示要用掉这么多餐巾
		if (i+1<=n)
			Add_Edge(i,i+1,0,inf);//延时送洗
		if (i+d1<=n)
			Add_Edge(i,i+d1+n,c1,inf);//送到快洗部
		if (i+d2<=n)
			Add_Edge(i,i+d2+n,c2,inf);//送到慢洗部
	}
	int Ans=0;
	while (spfa())
	{
		int now=n*2+1;
		int p=path[now];
		while (now!=0)
		{
			E[p].flow-=Flow[n*2+1];
			E[p^1].flow+=Flow[n*2+1];
			now=E[p].u;
			p=path[now];
		}
		Ans+=Flow[n*2+1]*Dist[n*2+1];
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

bool spfa()
{
	memset(Dist,-1,sizeof(Dist));
	memset(inqueue,0,sizeof(inqueue));
	int h=1,t=0;
	Q[1]=0;
	Dist[0]=0;
	inqueue[0]=1;
	Flow[0]=inf;
	do
	{
		t++;
		int u=Q[t];
		inqueue[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&((E[i].cost+Dist[u]<Dist[v])||(Dist[v]==-1)))
			{
				Dist[v]=Dist[u]+E[i].cost;
				path[v]=i;
				Flow[v]=min(Flow[u],E[i].flow);
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
	if (Dist[n*2+1]==-1)
		return 0;
	return 1;
}
