#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=300000;
const int inf=2147483647;

class Question
{
public:
	int u,v,lca;
};

int n,qus;
int cnt;
int Head[maxN];
int Next[maxN*2];
int V[maxN*2];
int root,rootsize;
Question Q[maxN];
//Tree_Chain
int Size[maxN];
int Top[maxN];
int Father[maxN];
int Depth[maxN];
int Heavyson[maxN];
int MaxDepth=0;
//Watcher
int W[maxN];
vector<int> VLCA[maxN];//lca处的差分
vector<int> VST[maxN];//S或T处的差分
int Sum[maxN*4];
int Ans[maxN];

void init();
int read();
void Add_Edge(int u,int v);
void dfs_TC(int u,int father);
void dfs_hvchain(int u,int nowtop);
int LCA(int u,int v);
void dfs_sum1(int u,int father);
void dfs_sum2(int u,int father);

int main()
{
	init();
	n=read();
	qus=read();
	for (int i=1;i<n;i++)
	{
		int u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	root=1;
	//dfs_root(1,1);
	//printf("root:%d\n",root);
	Depth[root]=1;
	Father[root]=1;
	dfs_TC(root,root);
	dfs_hvchain(root,root);

	for (int i=1;i<=n;i++)
		W[i]=read();
	
	for (int i=1;i<=qus;i++)
	{
		Q[i].u=read();
		Q[i].v=read();
		Q[i].lca=LCA(Q[i].u,Q[i].v);
		//printf("%d\n",Q[i].lca);
	}

	for (int i=1;i<=n;i++)
	{
		VST[i].clear();
		VLCA[i].clear();
	}
	for (int i=1;i<=qus;i++)
	{
		VST[Q[i].u].push_back(Depth[Q[i].u]);
		VLCA[Q[i].lca].push_back(Depth[Q[i].u]);
	}

	memset(Sum,0,sizeof(Sum));
	memset(Ans,0,sizeof(Ans));
	dfs_sum1(root,root);

	for (int i=1;i<=n;i++)
	{
		VST[i].clear();
		VLCA[i].clear();
	}
	for (int i=1;i<=qus;i++)
	{
		VST[Q[i].v].push_back(Depth[Q[i].v]-(Depth[Q[i].u]+Depth[Q[i].v]-2*Depth[Q[i].lca])+maxN);
		VLCA[Q[i].lca].push_back(Depth[Q[i].v]-(Depth[Q[i].u]+Depth[Q[i].v]-2*Depth[Q[i].lca])+maxN);
	}

	memset(Sum,0,sizeof(Sum));
	dfs_sum2(root,root);

	for (int i=1;i<=qus;i++)
		if (Depth[Q[i].u]==Depth[Q[i].lca]+W[Q[i].lca])
			Ans[Q[i].lca]--;

	for (int i=1;i<=n;i++)
		printf("%d ",Ans[i]);
	printf("\n");
	return 0;
}

void init()
{
	cnt=0;
	memset(Head,-1,sizeof(Head));
	root=1;
	rootsize=inf;
	return;
}

int read()
{
	int x=0;
	char ch=getchar();
	while ((ch>'9')||(ch<'0'))
		ch=getchar();
	while ((ch<='9')&&(ch>='0'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x;
}

void Add_Edge(int u,int v)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	V[cnt]=v;
	return;
}

void dfs_TC(int u,int father)
{
	int hvson=0;
	MaxDepth=max(MaxDepth,Depth[u]);
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=V[i];
		if (v==father)
			continue;
		Father[v]=u;
		Depth[v]=Depth[u]+1;
		dfs_TC(v,u);
		Size[u]=Size[u]+Size[v];
		if ((hvson==0)||(Size[v]>Size[hvson]))
		    hvson=v;
	}
	Heavyson[u]=hvson;
	return;
}

void dfs_hvchain(int u,int nowtop)
{
	Top[u]=nowtop;
	if (Heavyson[u]==0)
		return;
	dfs_hvchain(Heavyson[u],nowtop);
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=V[i];
		if ((v!=Father[u])&&(v!=Heavyson[u]))
			dfs_hvchain(v,v);
	}
	return;
}

int LCA(int u,int v)
{
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]])
			swap(u,v);
		u=Father[Top[u]];
	}
	if (Depth[u]>Depth[v])
		swap(u,v);
	return u;
}

void dfs_sum1(int u,int father)
{
	int now=Depth[u]+W[u];
	int last;
	if (now<=MaxDepth)
		last=Sum[now];
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=V[i];
		if (v==father)
			continue;
		dfs_sum1(v,u);
	}
	int sz;
	sz=VST[u].size();
	for (int i=0;i<sz;i++)
		Sum[VST[u][i]]++;
	if (now<=MaxDepth)
		Ans[u]+=Sum[now]-last;
	sz=VLCA[u].size();
	for (int i=0;i<sz;i++)
		Sum[VLCA[u][i]]--;
	return;
}

void dfs_sum2(int u,int father)
{
	int now=Depth[u]-W[u]+maxN;
	int last=Sum[now];
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		int v=V[i];
		if (v==father)
			continue;
		dfs_sum2(v,u);
	}
	int sz;
	sz=VST[u].size();
	for (int i=0;i<sz;i++)
		Sum[VST[u][i]]++;
	Ans[u]+=Sum[now]-last;
	sz=VLCA[u].size();
	for (int i=0;i<sz;i++)
		Sum[VLCA[u][i]]--;
	return;
}
