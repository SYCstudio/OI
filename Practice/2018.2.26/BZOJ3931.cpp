#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510*2;
const int maxM=(100010+maxN)*10;
const ll INF=1e17;

class Edge
{
public:
	ll v,flow;
	ll w;
};

class Queue_Data
{
public:
	int u;
	ll dis;
};

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.dis>B.dis;
}

int n,m,S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
ll Dist[maxN];
int Depth[maxN],Queue[maxN],cur[maxN];
priority_queue<Queue_Data> Q;
bool vis[maxN];

void Add_Edge(int u,int v,ll w,ll flow);
bool Bfs();
ll dfs(int u,ll flow);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m;S=1;T=n+n;
	for (int i=1;i<=m;i++)
	{
		int u,v;ll w;cin>>u>>v>>w;
		if (u!=n) Add_Edge(u+n,v,w,INF);
		if (v!=n) Add_Edge(v+n,u,w,INF);
	}
	for (int i=1;i<=n;i++)
	{
		ll w;cin>>w;
		Add_Edge(i,i+n,0,w);
	}
	Add_Edge(1,1+n,0,INF);Add_Edge(n,n+n,0,INF);
	mem(Dist,-1);Dist[S]=0;
	Q.push((Queue_Data){S,0});
	do
	{
		Queue_Data u=Q.top();Q.pop();
		if (vis[u.u]) continue;
		vis[u.u]=1;
		for (int i=Head[u.u];i!=-1;i=Next[i])
			if ((vis[E[i].v]==0)&&(E[i].flow>0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u.u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u.u]+E[i].w;
				Q.push((Queue_Data){E[i].v,Dist[E[i].v]});
			}
	}
	while (!Q.empty());
	//for (int i=1;i<=T;i++) cout<<Dist[i]<<" ";cout<<endl;
	ll mxflow=0;
	while (Bfs())
	{
		for (int i=S;i<=T;i++) cur[i]=Head[i];
		while (ll di=dfs(S,INF)) mxflow=mxflow+di;
	}
	printf("%lld\n",mxflow);
	return 0;
}

void Add_Edge(int u,int v,ll w,ll flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].v=v;E[edgecnt].w=w;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;
	E[edgecnt].v=u;E[edgecnt].w=-w;E[edgecnt].flow=0;
	return;
}

bool Bfs()
{
	mem(Depth,-1);
	int h=1,t=0;Queue[1]=S;Depth[S]=1;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Dist[E[i].v]==Dist[u]+E[i].w)&&(Depth[E[i].v]==-1))
				Depth[Queue[++h]=E[i].v]=Depth[u]+1;
	}
	while (t!=h);
	if (Depth[T]==-1) return 0;
	return 1;
}

ll dfs(int u,ll flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>0)&&(Dist[E[i].v]==Dist[u]+E[i].w)&&(Depth[E[i].v]==Depth[u]+1))
		{
			ll di=dfs(E[i].v,min(flow,E[i].flow));
			if (di)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}
