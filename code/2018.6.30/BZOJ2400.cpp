#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxM=2010*10;
const int inf=2147483647;

class Edge
{
public:
	int v,flow;
};

int n,m;
ll Ans1,Ans2;
int S,T;
int Val[maxN];
int EU[maxM],EV[maxM];
int edgecnt,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow,int opt);
void Graph(int bit);
bool Bfs();
int dfs(int u,int flow);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
	for (int i=1;i<=m;i++) scanf("%d%d",&EU[i],&EV[i]);
	S=n+1;T=n+2;

	for (int i=31;i>=0;i--)
	{
		Graph(i);
		//cout<<"Build over:"<<i<<endl;
		int mxflow=0;
		while (Bfs())
		{
			for (int j=1;j<=T;j++) cur[j]=Head[j];
			while (ll di=dfs(S,inf)) mxflow+=di;
		}
		//cout<<mxflow<<endl;
		
		int sum1=mxflow/10000,sum2=mxflow%10000;
		//if (sum1||sum2) cout<<sum1<<" "<<sum2<<" "<<mxflow<<endl;
		Ans1=Ans1+(1ll<<i)*sum1;
		Ans2=Ans2+(1ll<<i)*sum2;
	}

	printf("%lld\n%lld\n",Ans1,Ans2);
	return 0;
}

void Add_Edge(int u,int v,int flow,int opt)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,flow*opt});
	return;
}

void Graph(int bit)
{
	mem(Head,-1);edgecnt=-1;
	for (int i=1;i<=n;i++)
		if (Val[i]>=0)
		{
			if ( (Val[i]&(1<<bit)) !=0) Add_Edge(i,T,inf,0),Add_Edge(S,i,1,0);
			else Add_Edge(S,i,inf,0);
		}
		else Add_Edge(S,i,1,0);
	for (int i=1;i<=m;i++) Add_Edge(EU[i],EV[i],10000,1);
	return;
}

bool Bfs()
{
	mem(Depth,-1);Q[1]=S;Depth[S]=1;
	int h=1,t=0;
	do
		for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	while (t!=h);
	return Depth[T]!=-1;
}

int dfs(int u,int flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
			if (int di=dfs(E[i].v,min(flow,E[i].flow))){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
	return 0;
}
