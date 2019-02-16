#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=2010;
const int maxM=40001;
const int inf=2147483647;

class Edge
{
public:
	int u,v,cost,flow;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int dist[maxN];
int pre[maxN];
int flow[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int cost,int flow);
void _Add(int u,int v,int cost,int flow);
bool spfa();

int main()
{
	memset(Head,-1,sizeof(Head));
	memset(Next,-1,sizeof(Next));
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int cost;
		scanf("%d",&cost);
		Add_Edge(0,i,0,1);//添加源点到入点的边
		Add_Edge(0,i+n,cost,1);//添加源点直接连到出点的边
		Add_Edge(i+n,n*2+1,0,1);//添加出点到汇点的边
	}
	for (int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if (u>v)
			swap(u,v);
		Add_Edge(u,v+n,w,1);//添加入点到出点的边
	}
	int Ans=0;
	/*for (int i=0;i<=cnt;i++)
		cout<<E[i].u<<" "<<E[i].v<<" "<<E[i].cost<<" "<<E[i].flow<<endl;
		cout<<endl;*/
	while (spfa())
	{
		int now=n*2+1;
		int last=pre[now];
		/*for (int i=0;i<=cnt;i++)
			cout<<E[i].u<<" "<<E[i].v<<" "<<E[i].cost<<" "<<E[i].flow<<endl;
			cout<<endl;*/
		while (now!=0)
		{
			//cout<<now<<' ';
			E[last].flow-=flow[n*2+1];
			E[last^1].flow+=flow[n*2+1];
			now=E[last].u;
			last=pre[now];
		}
		//cout<<endl;
		//cout<<"Dist:"<<dist[n*2+1]<<endl;
		Ans+=dist[n*2+1];
	}
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int cost,int flow)
{
	_Add(u,v,cost,flow);
	_Add(v,u,-cost,0);
}

void _Add(int u,int v,int cost,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].cost=cost;
	E[cnt].flow=flow;
}

bool spfa()
{
	memset(pre,-1,sizeof(pre));
	memset(dist,127,sizeof(dist));
	memset(flow,0,sizeof(flow));
	memset(inqueue,0,sizeof(inqueue));
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	flow[0]=inf;
	dist[0]=0;
	inqueue[0]=1;
	Q.push(0);
	do
	{
		int u=Q.front();
		Q.pop();
		inqueue[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&(dist[v]>dist[u]+E[i].cost))
			{
				dist[v]=dist[u]+E[i].cost;
				pre[v]=i;
				flow[v]=min(flow[u],E[i].flow);
				if (inqueue[v]==0)
				{
					Q.push(v);
					inqueue[v]=1;
				}
			}
		}
	}
	while (!Q.empty());
	if (flow[n*2+1]==0)
		return 0;
	return 1;
}
