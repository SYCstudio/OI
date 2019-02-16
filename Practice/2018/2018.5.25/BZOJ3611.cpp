#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000*2;
const int maxM=maxN*2;
const int maxBit=20;
const int inf=2000000000;
const ll INF=1e18;

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt=0,Dfn[maxN],Last[maxN],Fa[maxBit][maxN];
ll Depth[maxN];
int Node[maxN<<1],Stack[maxN];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
bool cmp(int a,int b);
int GetLCA(int u,int v);
int Dist(int u,int v);

namespace Tree
{
	int nodecnt,Mark[maxN];
	int edgecnt,Head[maxN],Next[maxM],V[maxM];
	ll Size[maxN],F[maxN],E[maxN];
	ll Ans1,Ans2,Ans3;

	void Add_Edge(int u,int v);
	void Do();
	void dfs(int u,int fa);
}

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	
	dfs_init(1,0);
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if ((Fa[i-1][j])&&(Fa[i-1][Fa[i-1][j]]))
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	int TQ;scanf("%d",&TQ);
	while (TQ--)
	{
		scanf("%d",&K);
		for (int i=1;i<=K;i++) scanf("%d",&Node[i]);
		Tree::nodecnt=K;
		for (int i=1;i<=K;i++) Tree::Mark[Node[i]]=1;
		
		sort(&Node[1],&Node[K+1],cmp);
		for (int i=1;i<K;i++) Node[i+K]=GetLCA(Node[i],Node[i+1]);
		K=K+K-1;Node[++K]=1;
		sort(&Node[1],&Node[K+1],cmp);K=unique(&Node[1],&Node[K+1])-Node-1;

		//for (int i=1;i<=K;i++) cout<<Node[i]<<" ";cout<<endl;

		Tree::edgecnt=0;
		for (int i=1;i<=K;i++) Tree::Head[Node[i]]=-1;

		int top=0;
		for (int i=1;i<=K;i++)
		{
			while ((top)&&(Last[Stack[top]]<Dfn[Node[i]])) top--;
			if (top) Tree::Add_Edge(Stack[top],Node[i]);
			Stack[++top]=Node[i];
		}
		Tree::Do();
		
		printf("%lld %lld %lld\n",Tree::Ans1,Tree::Ans2,Tree::Ans3);
		for (int i=1;i<=K;i++) Tree::Mark[Node[i]]=0;
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs_init(int u,int fa)
{
	Dfn[u]=++dfncnt;Depth[u]=Depth[fa]+1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[0][V[i]]=u;
			dfs_init(V[i],u);
		}
	Last[u]=dfncnt;return;
}

bool cmp(int a,int b){
	return Dfn[a]<Dfn[b];
}

int GetLCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

int Dist(int u,int v)
{
	int lca=GetLCA(u,v);
	return Depth[u]+Depth[v]-2*Depth[lca];
}

namespace Tree
{
	void Add_Edge(int u,int v)
	{
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
		return;
	}

	void Do()
	{
		Ans1=0;Ans2=INF;Ans3=-INF;
		dfs(1,0);
	}

	void dfs(int u,int fa)
	{
		F[u]=(Mark[u])?(0):(-INF);
		E[u]=(Mark[u])?(0):(INF);
		Size[u]=Mark[u];
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa)
			{
				dfs(V[i],u);Size[u]+=Size[V[i]];
				int w=Dist(V[i],u);
				Ans1=Ans1+1ll*Size[V[i]]*(nodecnt-Size[V[i]])*w;
				Ans2=min(Ans2,E[u]+E[V[i]]+w);
				Ans3=max(Ans3,F[u]+F[V[i]]+w);
				E[u]=min(E[u],E[V[i]]+w);
				F[u]=max(F[u],F[V[i]]+w);
			}
		return;
	}
}
