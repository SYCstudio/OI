#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson ((lson)|1)

const int maxN=101000;
const int maxM=maxN*2;
const int maxBit=18;
const int inf=2147483647;

class SegmentData
{
public:
	int mx;
	int lazy;
};

class LCT
{
public:
	int mx;
	int ch[2],fa;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,Dfn[maxN],Last[maxN],Depth[maxN],Fa[maxBit][maxN],DId[maxN];
SegmentData S[maxN<<2];
LCT T[maxN];

void Add_Edge(int u,int v);
void dfs_dfn(int u);
void Build(int now,int l,int r);
void PushDown(int now);
void Modify(int now,int l,int r,int ql,int qr,int key);
int Query(int now,int l,int r,int ql,int qr);
bool Isroot(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
int GetMinDepth(int x);
int GetLCA(int u,int v);

int main()
{
	mem(Head,-1);
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Depth[1]=1;dfs_dfn(1);
	for (int i=1;i<maxBit;i++) for (int j=1;j<=n;j++) if (Fa[i-1][j]!=0) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	for (int i=1;i<=n;i++) T[i].fa=Fa[0][i];
	Build(1,1,n);
	while (m--)
	{
		int opt;scanf("%d",&opt);
		if (opt==1)
		{
			int x;scanf("%d",&x);
			Access(x);
		}
		if (opt==2)
		{
			int x,y;scanf("%d%d",&x,&y);
			int lca=GetLCA(x,y);
			printf("%d\n",Query(1,1,n,Dfn[x],Dfn[x])+Query(1,1,n,Dfn[y],Dfn[y])-2*Query(1,1,n,Dfn[lca],Dfn[lca])+1);
		}
		if (opt==3)
		{
			int x;scanf("%d",&x);
			printf("%d\n",Query(1,1,n,Dfn[x],Last[x]));
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs_dfn(int u)
{
	Dfn[u]=++dfncnt;DId[dfncnt]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Fa[0][u])
		{
			Depth[V[i]]=Depth[u]+1;Fa[0][V[i]]=u;
			dfs_dfn(V[i]);
		}
	Last[u]=dfncnt;
	return;
}

void Build(int now,int l,int r)
{
	if (l==r)
	{
		S[now].mx=Depth[DId[l]];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now].mx=max(S[lson].mx,S[rson].mx);
	return;
}

void PushDown(int now)
{
	if (S[now].lazy)
	{
		int lz=S[now].lazy;
		S[lson].mx+=lz;S[lson].lazy+=lz;
		S[rson].mx+=lz;S[rson].lazy+=lz;
		S[now].lazy=0;
	}
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
	if ((l==ql)&&(r==qr))
	{
		S[now].mx+=key;S[now].lazy+=key;
		return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	S[now].mx=max(S[lson].mx,S[rson].mx);
	return;
}

int Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now].mx;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return max(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

bool Isroot(int x)
{
	int y=T[x].fa;
	if ((T[y].ch[0]==x)||(T[y].ch[1]==x)) return 0;
	return 1;
}

void Rotate(int x)
{
	int y=T[x].fa,z=T[y].fa;
	int sx=(x==T[y].ch[1]);
	int sy=(y==T[z].ch[1]);
	T[x].fa=z;if (Isroot(y)==0) T[z].ch[sy]=x;
	T[y].ch[sx]=T[x].ch[sx^1];if (T[x].ch[sx^1]) T[T[x].ch[sx^1]].fa=y;
	T[x].ch[sx^1]=y;T[y].fa=x;
	return;
}

void Splay(int x)
{
	while (Isroot(x)==0)
	{
		int y=T[x].fa,z=T[y].fa;
		if (Isroot(y)==0)
			((x==T[y].ch[0])^(y==T[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);
		if (T[x].ch[1]!=0)
		{
			int y=GetMinDepth(T[x].ch[1]);
			Modify(1,1,n,Dfn[y],Last[y],1);
		}
		T[x].ch[1]=lastx;T[lastx].fa=x;
		if (lastx!=0)
		{
			int y=GetMinDepth(lastx);
			Modify(1,1,n,Dfn[y],Last[y],-1);
		}
		lastx=x;x=T[x].fa;
	}
	return;
}

int GetMinDepth(int x)
{
	while (T[x].ch[0]) x=T[x].ch[0];
	return x;
}

int GetLCA(int u,int v)
{
	if (Depth[v]>Depth[u]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u]!=0)&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u]!=0)&&(Fa[i][v]!=0)&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}
