#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=501;
const int maxN=maxMap*maxMap;
const int maxM=maxN*10;
const int inf=2147483647;

class Edge
{
public:
	int v;
	ll w;
};

class Queue_Data
{
public:
	int u;
	ll w;
};

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.w>B.w;
}

int n,S,T;
int edgecnt=0,Head[maxN],Next[maxM],Id[maxMap][maxMap];
Edge E[maxM];
ll Dist[maxN];
priority_queue<Queue_Data> Q;
bool vis[maxN];

void Add_Edge(int u,int v,ll w);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n;
	int idcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Id[i][j]=++idcnt;
	S=n*n+1;T=S+1;n++;
	for (int i=1;i<=n;i++)
		for (int j=1;j<n;j++)
		{
			ll w;cin>>w;
			if (i==1) Add_Edge(Id[i][j],T,w);
			else if (i==n) Add_Edge(S,Id[i-1][j],w);
			else Add_Edge(Id[i][j],Id[i-1][j],w);
		}
	for (int i=1;i<n;i++)
		for (int j=1;j<=n;j++)
		{
			ll w;cin>>w;
			if (j==1) Add_Edge(S,Id[i][j],w);
			else if (j==n) Add_Edge(Id[i][j-1],T,w);
			else Add_Edge(Id[i][j-1],Id[i][j],w);
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<n;j++)
		{
			ll w;cin>>w;
			if (i==1) Add_Edge(T,Id[i][j],w);
			else if (i==n) Add_Edge(Id[i-1][j],S,w);
			else Add_Edge(Id[i-1][j],Id[i][j],w);
		}
	for (int i=1;i<n;i++)
		for (int j=1;j<=n;j++)
		{
			ll w;cin>>w;
			if (j==1) Add_Edge(Id[i][j],S,w);
			else if (j==n) Add_Edge(T,Id[i][j-1],w);
			else Add_Edge(Id[i][j],Id[i][j-1],w);
		}
	mem(Dist,-1);Dist[S]=0;
	Q.push((Queue_Data){S,0});
	do
	{
		Queue_Data u=Q.top();Q.pop();
		if (vis[u.u]) continue;
		vis[u.u]=1;
		for (int i=Head[u.u];i!=-1;i=Next[i])
			if ((vis[E[i].v]==0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u.u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u.u]+E[i].w;
				Q.push((Queue_Data){E[i].v,Dist[E[i].v]});
			}
	}
	while (!Q.empty());
	printf("%lld\n",Dist[T]);
	return 0;
}

void Add_Edge(int u,int v,ll w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].v=v;E[edgecnt].w=w;
	return;
}
