#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=251000*2;
const int maxM=maxN*2;
const int maxBit=20;
const int inf=2147483647;
const ll INF=1e18;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM];
int dfncnt=0,Dfn[maxN],Last[maxN];
int Fa[maxBit][maxN];
ll MinPath[maxN],Depth[maxN];
int Node[maxN*2],Stack[maxN];

void Add_Edge(int u,int v,ll w);
void dfs_init(int u,int fa,ll w);
int GetLCA(int u,int v);
bool cmp(int a,int b);

namespace Tree
{
	int Mark[maxN];
	int edgecnt,Head[maxN],Next[maxM],V[maxM];
	ll F[maxN];

	void Add_Edge(int u,int v);
	void dfs(int u,int fa);
}

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	dfs_init(1,0,INF);
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if ((Fa[i-1][j])&&(Fa[i-1][Fa[i-1][j]]))
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	int TQ;scanf("%d",&TQ);
	while (TQ--)
	{
		int K;scanf("%d",&K);
		for (int i=1;i<=K;i++) scanf("%d",&Node[i]);
		for (int i=1;i<=K;i++) Tree::Mark[Node[i]]=1;
		
		sort(&Node[1],&Node[K+1],cmp);
		for (int i=1;i<K;i++) Node[K+i]=GetLCA(Node[i],Node[i+1]);
		K=K+K-1;Node[++K]=1;
		sort(&Node[1],&Node[K+1],cmp);K=unique(&Node[1],&Node[K+1])-Node-1;

		Tree::edgecnt=0;
		for (int i=1;i<=K;i++) Tree::Head[Node[i]]=-1;
		
		int top=0;
		for (int i=1;i<=K;i++)
		{
			while ((top)&&(Last[Stack[top]]<Dfn[Node[i]])) top--;
			if (top) Tree::Add_Edge(Stack[top],Node[i]);
			Stack[++top]=Node[i];
		}
		Tree::dfs(Node[1],0);
		
		for (int i=1;i<=K;i++) Tree::Mark[Node[i]]=0;
		printf("%lld\n",Tree::F[Node[1]]);
	}
	return 0;
}

void Add_Edge(int u,int v,ll w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs_init(int u,int fa,ll w)
{
	Dfn[u]=++dfncnt;Depth[u]=Depth[fa]+1;MinPath[u]=w;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[0][V[i]]=u;
			dfs_init(V[i],u,min(w,W[i]));
		}
	Last[u]=dfncnt;
	return;
}

int GetLCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

bool cmp(int u,int v)
{
	return Dfn[u]<Dfn[v];
}

namespace Tree
{
	void Add_Edge(int u,int v)
	{
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
		return;
	}

	void dfs(int u,int fa)
	{
		if (Mark[u]){
			F[u]=MinPath[u];return;
		}
		F[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa)
			{
				dfs(V[i],u);
				F[u]=F[u]+F[V[i]];
			}
		F[u]=min(F[u],MinPath[u]);
		return;
	}
}
