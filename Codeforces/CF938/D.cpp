#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200100;
const int maxM=200100*2;
const int inf=2147483647;

class Edge
{
public:
	ll v,w;
};

class Queue_Data
{
public:
	ll id,dis;
};

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.dis>B.dis;
}

int n,m;
ll edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
bool vis[maxN];
ll Ans[maxN],Dist[maxN];
priority_queue<Queue_Data> Q;

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		ll u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].w=w;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].w=w;
	}
	for (int i=1;i<=n;i++)
	{
		ll val;scanf("%lld",&val);Dist[i]=val;
		Q.push((Queue_Data){i,val});
	}
	do
	{
		Queue_Data u=Q.top();Q.pop();if (vis[u.id]) continue;
		vis[u.id]=1;Ans[u.id]=u.dis;
		for (int i=Head[u.id];i!=-1;i=Next[i])
			if ((vis[E[i].v]==0)&&(Dist[E[i].v]>u.dis+E[i].w*2ll))
			{
				Dist[E[i].v]=u.dis+E[i].w*2ll;Q.push((Queue_Data){E[i].v,Dist[E[i].v]});
			}
	}
	while (!Q.empty());
	for (int i=1;i<=n;i++) printf("%lld ",Ans[i]);
	return 0;
}
