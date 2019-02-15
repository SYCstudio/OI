#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int maxM=202000*20;
const int maxBit=20;
const int inf=2147483647;

int n,m,Q,nodecnt;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],low[maxN],St[maxN],top=0;
vector<int> T[maxN];
int Fa[maxBit][maxN],Depth[maxN],W[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void dfs_fa(int u,int fa);
int LCA(int u,int v);
void dfs_calc(int u,int fa);

int main()
{
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}

	nodecnt=n;
	tarjan(1,0);

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<T[i].size();j++)
			cout<<i<<"->"<<T[i][j]<<endl;
	//*/

	Depth[1]=1;
	dfs_fa(1,0);

	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=nodecnt;j++)
			Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	while (Q--)
	{
		int p,q;scanf("%d%d",&p,&q);
		int lca=LCA(p,q);
		W[p]++;W[q]++;W[lca]--;W[Fa[0][lca]]--;
	}

	dfs_calc(1,0);

	for (int i=1;i<=n;i++) printf("%d\n",W[i]);

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;St[++top]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		//if (V[i]!=fa)
		{
			int v=V[i];
			if (dfn[v]==0){
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if (low[v]>=dfn[u])
				{
					nodecnt++;int w;
					do w=St[top--],T[w].push_back(nodecnt),T[nodecnt].push_back(w);
					while (w!=u);
					St[++top]=u;
				}
				//else T[u].push_back(v),T[v].push_back(u);
			}
			else low[u]=min(low[u],dfn[v]);
		}
	return;
}

void dfs_fa(int u,int fa)
{
	int sz=T[u].size();
	for (int i=0;i<sz;i++)
		if (T[u][i]!=fa){
			Depth[T[u][i]]=Depth[u]+1;Fa[0][T[u][i]]=u;
			dfs_fa(T[u][i],u);
		}
	return;
}

int LCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

void dfs_calc(int u,int fa)
{
	int sz=T[u].size();
	for (int i=0;i<sz;i++)
		if (T[u][i]!=fa){
			dfs_calc(T[u][i],u);W[u]+=W[T[u][i]];
		}
	return;
}
/*
4 4 2
1 2
1 3
2 3
1 4
4 2
4 3
//*/
