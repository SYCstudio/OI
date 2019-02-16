#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000*2;
const int maxM=maxN*5;
const int inf=2147483647;

int n,m,nodecnt,Q;
int edgecnt,Head[maxN],Next[maxM],V[maxM],Val[maxN];
vector<int> T[maxN];
int dfncnt,dfn[maxN],low[maxN],top,St[maxN],From[maxN];
int Size[maxN],MxSon[maxN],Depth[maxN],Fa[maxN],Top[maxN];
int Mn[maxN<<2];
multiset<int> Set[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void dfs1(int u,int v);
void dfs2(int u,int top);
void GetLCA(int u,int v,int &mn,int &lca);
void Build(int now,int l,int r);
int Query(int now,int l,int r,int ql,int qr);
void Modify(int now,int l,int r,int pos,int key);

int main()
{
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
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

	dfncnt=0;
	dfs1(1,0);
	dfs2(1,0);
	Build(1,1,nodecnt);
	for (int i=1;i<=n;i++) Modify(1,1,nodecnt,dfn[i],Val[i]);
	for (int i=n+1;i<=nodecnt;i++) Modify(1,1,nodecnt,dfn[i],(*Set[i].begin()));

	/*
	for (int i=1;i<=nodecnt;i++) cout<<From[i]<<" ";cout<<endl;
	for (int i=n+1;i<=nodecnt;i++){
		for (multiset<int>::iterator it=Set[i].begin();it!=Set[i].end();it++)
			cout<<(*it)<<" ";
		cout<<endl;
	}
	//*/

	while (Q--)
	{
		char opt;scanf(" %c",&opt);
		if (opt=='C')
		{
			int a,w;scanf("%d%d",&a,&w);
			Modify(1,1,nodecnt,dfn[a],w);
			if (From[a])
			{
				int id=From[a];
				Set[id].erase(Set[id].find(Val[a]));
				Set[id].insert(w);
				Modify(1,1,nodecnt,dfn[id],(*Set[id].begin()));
			}
			Val[a]=w;
		}
		if (opt=='A')
		{
			int a,b;scanf("%d%d",&a,&b);
			int lca,mn;
			GetLCA(a,b,lca,mn);
			if (lca<=n) printf("%d\n",mn);
			else printf("%d\n",min(mn,Val[Fa[lca]]));
		}
	}

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void tarjan(int u,int fa)
{
	//cout<<"tarjan:"<<u<<endl;
	dfn[u]=low[u]=++dfncnt;St[++top]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		//if (V[i]!=fa)
		{
			int v=V[i];
			if (dfn[v]==0){
				tarjan(v,u);low[u]=min(low[u],low[v]);
				if (low[v]>=dfn[u])
				{
					nodecnt++;int w;
					do{
						w=St[top--];//cout<<w<<" ";
						T[w].push_back(nodecnt);
						T[nodecnt].push_back(w);
					}
					while (w!=v);
					//cout<<endl;
					T[u].push_back(nodecnt);T[nodecnt].push_back(u);
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
	return;
}

void dfs1(int u,int fa)
{
	Size[u]=1;
	int sz=T[u].size();
	for (int i=0;i<sz;i++)
		if (T[u][i]!=fa){
			Depth[T[u][i]]=Depth[u]+1;Fa[T[u][i]]=u;
			dfs1(T[u][i],u);
			Size[u]+=Size[T[u][i]];
			if (Size[MxSon[u]]<Size[T[u][i]]) MxSon[u]=T[u][i];
		}
	if (u>n)
	{
		for (int i=0;i<sz;i++)
			if (T[u][i]!=fa){
				Set[u].insert(Val[T[u][i]]);
				From[T[u][i]]=u;
			}
	}
	return;
}

void dfs2(int u,int top)
{
	Top[u]=top;dfn[u]=++dfncnt;
	if (MxSon[u]==0) return;
	dfs2(MxSon[u],top);
	int sz=T[u].size();
	for (int i=0;i<sz;i++)
		if ((T[u][i]!=Fa[u])&&(T[u][i]!=MxSon[u]))
			dfs2(T[u][i],T[u][i]);
	return;
}

void GetLCA(int u,int v,int &lca,int &mn)
{
	mn=inf;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		mn=min(mn,Query(1,1,nodecnt,dfn[Top[u]],dfn[u]));
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	mn=min(mn,Query(1,1,nodecnt,dfn[u],dfn[v]));
	lca=u;
	return;
}

int Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return Mn[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

void Build(int now,int l,int r)
{
	Mn[now]=inf;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	return;
}

void Modify(int now,int l,int r,int pos,int key){
	if (l==r){
		Mn[now]=key;return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Mn[now]=min(Mn[lson],Mn[rson]);
	return;
}
