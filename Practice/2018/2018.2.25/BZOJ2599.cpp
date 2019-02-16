#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200010;
const int maxM=maxN*2;
const int maxNum=1000100;
const int inf=2147483647;

int n,K,root,nowsum;
ll Ans=inf;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM],Depth[maxN],Dist[maxN];
int Size[maxN],mxSon[maxN];
bool vis[maxN];
ll Min[maxNum];
int stacktop=0,Stack[maxN];

void Add_Edge(int u,int v,int w);
void GetRoot(int u,int fa);
void Solve(int u);
void GetAns(int u,int dep,int dis,int fa);

int main()
{
	mem(Head,-1);mem(Min,63);
	ios::sync_with_stdio(false);
	cin>>n>>K;
	for (int i=1;i<n;i++)
	{
		int u,v,w;cin>>u>>v>>w;u++;v++;
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	root=0;mxSon[0]=inf;nowsum=n;
	GetRoot(1,0);
	Solve(root);
	if (Ans==inf) printf("-1\n");
	else printf("%lld\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			GetRoot(V[i],u);Size[u]+=Size[V[i]];
			mxSon[u]=max(mxSon[u],Size[V[i]]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Solve(int u)
{
	Min[0]=0;stacktop=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			int lasttop=stacktop;
			GetAns(V[i],1,W[i],u);
			for (int i=lasttop+1;i<=stacktop;i++){
				int u=Stack[i];
				if ((Dist[u]<=K)&&(Min[Dist[u]]>Depth[u])) Min[Dist[u]]=Depth[u];
			}
		}
	for (int i=1;i<=stacktop;i++) if (Dist[Stack[i]]<=K) Min[Dist[Stack[i]]]=inf;
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

void GetAns(int u,int dep,int dis,int fa)
{
	Depth[u]=dep;Dist[u]=dis;Stack[++stacktop]=u;
	if (Dist[u]<=K)	Ans=min(Ans,dep+Min[K-Dist[u]]);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa))
			GetAns(V[i],dep+1,dis+W[i],u);
	return;
}
