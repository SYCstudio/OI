#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=51;
const int maxN=maxMap*maxMap;
const int maxM=maxN*20;
const int inf=2147483647;
const ll INF=1e17;

class Edge
{
public:
	int v;
	ll flow;
};

int n,m;
int S,T;
int edgecnt,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Queue[maxN],cur[maxN];
ll Id[maxMap][maxMap],Mat[maxMap][maxMap];

bool Check(ll num);
void Add_Edge(int u,int v,ll flow);
bool Bfs();
ll dfs(int u,ll flow);

int main()
{
	int Cas;
	scanf("%d",&Cas);
	while (Cas--)
	{
		scanf("%d%d",&n,&m);S=n*m+1;T=S+1;
		ll sum1=0,sum2=0,idcnt=0,cnt1=0,cnt2=0;
		ll maxnum=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				scanf("%lld",&Mat[i][j]);
				Id[i][j]=++idcnt;
				maxnum=max(maxnum,Mat[i][j]);
				if ((i+j)%2==0) sum1+=Mat[i][j],cnt1++;
				else sum2+=Mat[i][j],cnt2++;
			}
		if (cnt1==cnt2)
		{
			if (sum1!=sum2)
			{
				printf("-1\n");
				continue;
			}
			else
			{
				ll L=maxnum,R=1ll<<35;
				ll Num=0;
				do
				{
					ll mid=(L+R)>>1;
					if (Check(mid)) Num=mid,R=mid-1;
					else L=mid+1;
				}
				while (L<=R);
				printf("%lld\n",1ll*Num*cnt1-sum1);
			}
		}
		else
		{
			ll X=(sum1-sum2)/(cnt1-cnt2);
			if (X<maxnum)
			{
				printf("-1\n");
				continue;
			}
			if (Check(X)) printf("%lld\n",1ll*X*cnt1-sum1);
			else printf("-1\n");
		}
	}
	return 0;
}

bool Check(ll num)
{
	mem(Head,-1);edgecnt=-1;
	ll sum=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if ((i+j)%2==0)
			{
				sum=sum+num-Mat[i][j];
				Add_Edge(S,Id[i][j],num-Mat[i][j]);
				if (i!=1) Add_Edge(Id[i][j],Id[i-1][j],INF);
				if (j!=1) Add_Edge(Id[i][j],Id[i][j-1],INF);
				if (i!=n) Add_Edge(Id[i][j],Id[i+1][j],INF);
				if (j!=m) Add_Edge(Id[i][j],Id[i][j+1],INF);
			}
			else Add_Edge(Id[i][j],T,num-Mat[i][j]);
	ll mxflow=0;
	while (Bfs())
	{
		for (int i=1;i<=T;i++) cur[i]=Head[i];
		while (ll di=dfs(S,inf))
			mxflow+=di;
	}
	if (mxflow==sum) return 1;
	else return 0;
}

void Add_Edge(int u,int v,ll flow)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].flow=flow;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].flow=0;
	return;
}

bool Bfs()
{
	mem(Depth,-1);
	int h=1,t=0;
	Depth[S]=1;Queue[1]=S;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
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
		if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
		{
			ll di=dfs(E[i].v,min(flow,E[i].flow));
			if (di)
			{
				E[i].flow-=di;E[i^1].flow+=di;
				return di;
			}
		}
	return 0;
}

