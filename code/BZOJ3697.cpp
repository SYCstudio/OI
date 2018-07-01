#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=maxN<<1;
const int Delta=100000;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
bool vis[maxN];
int nowsum,root,Size[maxN],MxSon[maxN];
ll Ans=0;

void Add_Edge(int u,int v,int w);
void dfs_root(int u,int fa);
void Divide(int u);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);if (w==0) w=-1;
		Add_Edge(u,v,w);
	}
	MxSon[0]=inf;root=0;nowsum=n;
	dfs_root(1,1);
	Divide(root);

	printf("%lld\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

void dfs_root(int u,int fa)
{
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			dfs_root(V[i],u);Size[u]+=Size[V[i]];
			MxSon[u]=max(MxSon[u],Size[V[i]]);
		}
	MxSon[u]=max(MxSon[u],nowsum-Size[u]);
	if (MxSon[u]<MxSon[root]) root=u;
	return;
}

void Divide(int u)
{
	return;
}


