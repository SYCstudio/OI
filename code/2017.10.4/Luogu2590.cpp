#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=350000;
const int inf=2147483647;

class Edge
{
public:
	int u,v,nex;
};

class SegmentTree
{
public:
	ll mx,sum;
	SegmentTree()
	{
		mx=0;
		sum=0;
	}
};

class Tree_Chain
{
public:
	int f,sz,top,hson,depth;
};

int n;
int cnt;
int Head[maxN];
Edge E[maxN*2];
ll W[maxN];
Tree_Chain T[maxN];
int dfn[maxN];
SegmentTree Seg[maxN*4];

void Add_Edge(int u,int v);
//Tree_Chain
void dfs1(int u,int father);
void dfs2(int u,int Top);
ll LCA_sum(int u,int v);
ll LCA_max(int u,int v);
//SegmentTree
//void Build(int l,int r,int now);
void Update(int l,int r,int now,int pos,int key);
ll Query_sum(int l,int r,int now,int ql,int qr);
ll Query_max(int l,int r,int now,int ql,int qr);

int main()
{
	cnt=0;
	memset(Head,-1,sizeof(Head));
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	T[1].f=0;
	T[1].depth=1;
	dfs1(1,1);
	cnt=0;
	dfs2(1,1);
	for (int i=1;i<=n;i++)
		scanf("%lld",&W[i]);
	for (int i=1;i<=n;i++)
		Update(1,n,1,dfn[i],W[i]);
	//Build(1,n,1);
	int qus;
	scanf("%d",&qus);
	while (qus--)
	{
		char str[10];
		scanf("%s",str);
		if (str[0]=='Q')
		{
			int u,v;
			scanf("%d%d",&u,&v);
			//u=dfn[u];
			//v=dfn[v];
			if (str[1]=='M')
				printf("%lld\n",LCA_max(u,v));
			else
			{
				printf("%lld\n",LCA_sum(u,v));
			}
		}
		else
		{
			int pos,key;
			scanf("%d%d",&pos,&key);
			pos=dfn[pos];
			Update(1,n,1,pos,key);
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	cnt++;
	E[cnt].nex=Head[u];
	Head[u]=cnt;
	E[cnt].u=u;
	E[cnt].v=v;
	return;
}

void dfs1(int u,int father)
{
	T[u].sz=1;
	T[u].hson=0;
	for (int i=Head[u];i!=-1;i=E[i].nex)
	{
		int v=E[i].v;
		if (v==father)
			continue;
		T[v].f=u;
		T[v].depth=T[u].depth+1;
		dfs1(v,u);
		T[u].sz=T[u].sz+T[v].sz;
		if ((T[u].hson==0)||(T[T[u].hson].sz<T[v].sz))
			T[u].hson=v;
	}
	return;
}

void dfs2(int u,int Top)
{
	cnt++;
	dfn[u]=cnt;
	T[u].top=Top;
	if (T[u].hson==0)
		return;
	dfs2(T[u].hson,Top);
	for (int i=Head[u];i!=-1;i=E[i].nex)
	{
		int v=E[i].v;
		if ((v==T[u].f)||(v==T[u].hson))
			continue;
		dfs2(v,v);
	}
	return;
}

ll LCA_max(int u,int v)
{
	ll mx=-inf;
	while (T[u].top!=T[v].top)
	{
		if (T[T[u].top].depth<T[T[v].top].depth)
			swap(u,v);
		mx=max(mx,Query_max(1,n,1,dfn[T[u].top],dfn[u]));
		u=T[T[u].top].f;
	}
	if (dfn[v]<dfn[u])
		swap(u,v);
	mx=max(mx,Query_max(1,n,1,dfn[u],dfn[v]));
	return mx;
}

ll LCA_sum(int u,int v)
{
	ll sum=0;
	while (T[u].top!=T[v].top)
	{
		if (T[T[u].top].depth<T[T[v].top].depth)
			swap(u,v);
		sum=sum+Query_sum(1,n,1,dfn[T[u].top],dfn[u]);
		u=T[T[u].top].f;
	}
	if (dfn[v]<dfn[u])
		swap(u,v);
	sum=sum+Query_sum(1,n,1,dfn[u],dfn[v]);
	return sum;
}

void Update(int l,int r,int now,int pos,int key)
{
	if (l==r)
	{
		Seg[now].mx=Seg[now].sum=key;
		return;
	}
	int mid=(l+r)/2;
	if (pos<=mid)
		Update(l,mid,now*2,pos,key);
	if (pos>=mid+1)
		Update(mid+1,r,now*2+1,pos,key);
	Seg[now].sum=Seg[now*2].sum+Seg[now*2+1].sum;
	Seg[now].mx=max(Seg[now*2].mx,Seg[now*2+1].mx);
	return;
}

ll Query_sum(int l,int r,int now,int ql,int qr)
{
	if ((l==ql)&&(r==qr))
		return Seg[now].sum;
	int mid=(l+r)/2;
	if (qr<=mid)
		return Query_sum(l,mid,now*2,ql,qr);
	else if (ql>=mid+1)
		return Query_sum(mid+1,r,now*2+1,ql,qr);
	else
		return Query_sum(l,mid,now*2,ql,mid)+Query_sum(mid+1,r,now*2+1,mid+1,qr);
	//cout<<"Q_sum:"<<l<<" "<<r<<" "<<ql<<" "<<qr<<":"<<ret<<endl;
}

ll Query_max(int l,int r,int now,int ql,int qr)
{
	if ((l==ql)&&(r==qr))
		return Seg[now].mx;
	int mid=(l+r)/2;
	if (qr<=mid)
		return Query_max(l,mid,now*2,ql,qr);
	if (ql>=mid+1)
		return Query_max(mid+1,r,now*2+1,ql,qr);
	return max(Query_max(l,mid,now*2,ql,mid),Query_max(mid+1,r,now*2+1,mid+1,qr));
}
