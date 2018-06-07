#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int maxM=10100;
const ld eps=1e-10;
const int inf=2147483647;

class EDGE
{
public:
	int u,v;
	ld w;
};

int n,m;
EDGE EE[maxM];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Cnt[maxN];
ld W[maxM],Dist[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,ld w);
bool Check(ld mid);
bool Spfa(int u);

int main()
{
	//freopen("in.in","r",stdin);
	scanf("%d%d",&n,&m);
	ld L=inf,R=0,Ans;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%LF",&EE[i].u,&EE[i].v,&EE[i].w);
		L=min(L,EE[i].w);R=max(R,EE[i].w);
	}
	R=4500;
	do
	{
		//cout<<L<<" "<<R<<endl;
		ld mid=(L+R)/2.0;
		if (Check(mid)) Ans=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);
	printf("%.8LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,ld w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

bool Check(ld mid)
{
	edgecnt=0;mem(Head,-1);
	for (int i=1;i<=m;i++) Add_Edge(EE[i].u,EE[i].v,EE[i].w-mid);
	mem(vis,0);mem(Dist,0);
	for (int i=1;i<=n;i++) if (Spfa(i)==0) return 0;
	return 1;
}

bool Spfa(int u)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Dist[u]+W[i]<Dist[V[i]])
		{
			if (vis[V[i]]) return 0;
			Dist[V[i]]=Dist[u]+W[i];
			if (Spfa(V[i])==0) return 0;
		}
	vis[u]=0;
	return 1;
}
