#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=5001;
const int maxM=50001;
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow,cost;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Flow[maxN];
int Pre[maxN];
int Dist[maxN];
bool inqueue[maxN];

void Add_Edge(int u,int v,int flow,int cost);
void _Add(int u,int v,int flow,int cost);
bool spfa();

int main()
{
	//while (cin>>n>>m)
	cin>>n>>m;
	{
		memset(Head,-1,sizeof(Head));
		memset(Next,-1,sizeof(Next));
		for (int i=1;i<=m;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			Add_Edge(u,v,1,w);
			Add_Edge(v,u,1,w);
		}
		Add_Edge(0,1,2,0);
		Add_Edge(n,n+1,2,0);
		/*for (int i=0;i<=n+1;i++)
		{
			for (int j=Head[i];j!=-1;j=Next[j])
				cout<<E[j].u<<' '<<E[j].v<<" "<<E[j].cost<<" "<<E[j].flow<<endl;
			cout<<endl;
			}*/
		int Ans=0;
		while (spfa())
		{
			int now=n+1;
			int last=Pre[now];
			while (now!=0)
			{
				E[last].flow-=Flow[n+1];
				E[last^1].flow+=Flow[n+1];
				now=E[last].u;
				last=Pre[now];
			}
			Ans+=Dist[n+1]*Flow[n+1];
		}
		cout<<Ans<<endl;
	}
}

void Add_Edge(int u,int v,int flow,int cost)
{
	_Add(u,v,flow,cost);
	_Add(v,u,0,-cost);
	return;
}

void _Add(int u,int v,int flow,int cost)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	E[cnt].flow=flow;
	E[cnt].cost=cost;
	return;
}

bool spfa()
{
	memset(Pre,-1,sizeof(Pre));
	memset(inqueue,0,sizeof(inqueue));
	memset(Flow,0,sizeof(Flow));
	memset(Dist,127,sizeof(Dist));
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	Q.push(0);
	Dist[0]=0;
	Flow[0]=inf;
	inqueue[0]=1;
	do
	{
		int u=Q.front();
		//cout<<u<<endl;
		inqueue[u]=0;
		Q.pop();
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			int v=E[i].v;
			if ((E[i].flow>0)&&(Dist[u]+E[i].cost<Dist[v]))
			{
				Dist[v]=E[i].cost+Dist[u];
				Pre[v]=i;
				Flow[v]=min(Flow[u],E[i].flow);
				if (inqueue[v]==0)
				{
					Q.push(v);
					inqueue[v]=1;
				}
			}
		}
	}
	while (!Q.empty());
	/*for (int i=0;i<=n+1;i++)
		cout<<Dist[i]<<" ";
	cout<<endl;
	for (int i=0;i<=n+1;i++)
		cout<<Pre[i]<<" ";
		cout<<endl;*/
	if (Pre[n+1]==-1)
		return 0;
	return 1;
}
