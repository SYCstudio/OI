#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long

const int maxN=10010;
const int maxM=50010*2;
const int inf=2147483647;
const ll INF=1e15;

class Edge
{
public:
    int v,nex;ll w;
};

int n,m;
ll B;
int cnt=0,Head[maxN];
Edge E[maxM];
ll City[maxN];
bool inqueue[maxN];
int Q[maxN*10];
ll Dist[maxN];

void Add_Edge(int u,int v,ll w);
bool Spfa(ll Limit);

int main()
{
    ll mxCity=0;
    mem(Head,-1);
    scanf("%d%d%lld",&n,&m,&B);
    for (int i=1;i<=n;i++)
    {
	scanf("%lld",&City[i]);
	mxCity=max(mxCity,City[i]);
    }
    for (int i=1;i<=m;i++)
    {
	int u,v;ll w;
	scanf("%d%d%lld",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    ll l=0,r=mxCity;
    ll Ans=-1;
    while (l<=r)
    {
	ll mid=(l+r)/2;
	if (Spfa(mid))
	{
	    Ans=mid;
	    r=mid-1;
	}
	else l=mid+1;
    }
    if (Ans==-1) printf("AFK\n");
    else printf("%lld\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,ll w)
{
    cnt++;E[cnt].nex=Head[u];Head[u]=cnt;
    E[cnt].v=v;E[cnt].w=w;
    return;
}

bool Spfa(ll Limit)
{
    mem(Dist,127);
    Dist[1]=0;inqueue[1]=1;
    int h=1,t=0;Q[1]=1;
    if (City[1]>Limit) return 0;
    do
    {
	int u=Q[++t];
	for (int i=Head[u];i!=-1;i=E[i].nex)
	{
	    int v=E[i].v;if (City[v]>Limit) continue;
	    if (Dist[v]>Dist[u]+E[i].w)
	    {
		Dist[v]=Dist[u]+E[i].w;
		if (inqueue[v]==0){inqueue[v]=1,Q[++h]=v;}
	    }
	}
	inqueue[u]=0;
    }
    while (t<h);
    return Dist[n]<=B;
}
