#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5010;
const int maxM=3010*2;
const ld eps=1e-8;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
bool vis[maxN];
ld W[maxM],Dist[maxN];

void Add_Edge(int u,int v,ld w);
bool Check(ld k);
bool Spfa(int u,ld k);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	ld L=inf,R=0,Ans;
	for (int i=1;i<=m;i++)
	{
		int u,v,a,b,c,d;scanf("%d%d%d%d%d%d",&u,&v,&a,&b,&c,&d);
		if (u==n+1) continue;
		Add_Edge(u,v,b+d);L=min(L,(ld)b+d);R=max(R,(ld)b+d);
		if (c) Add_Edge(v,u,a-d),L=min(L,(ld)a-d),R=max(R,(ld)a-d);
	}
	L-=eps;R+=eps;
	do
	{
		//cout<<"("<<L<<","<<R<<")"<<endl;
		ld mid=(L+R)/2.0;
		if (Check(mid)) Ans=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<R);
	printf("%.2LF\n",-Ans);
	return 0;
}

void Add_Edge(int u,int v,ld w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

bool Check(ld k)
{
	mem(vis,0);mem(Dist,0);
	for (int i=1;i<=n+2;i++) if (Spfa(i,k)==0) return 0;
	return 1;
}

bool Spfa(int u,ld k)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Dist[V[i]]>Dist[u]+W[i]-k)
		{
			if (vis[V[i]]) return 0;
			Dist[V[i]]=Dist[u]+W[i]-k;
			if (Spfa(V[i],k)==0) return 0;
		}
	vis[u]=0;
	return 1;
}
