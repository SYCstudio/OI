#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30010;
const int maxM=maxN*2;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int mn,mx;
	int mega;
};

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Fa[maxN],Size[maxN],Hson[maxN],Top[maxN],Faedge[maxN],Depth[maxN];
int idcnt=0,Id[maxN];
SegmentData S[maxN*6];

void Add_Edge(int u,int v,int w);
void _Add(int u,int v,int w);
void dfs1(int u);
void dfs2(int u,int top);
int QC_max(int u,int v);
int QC_min(int u,int v);
int QC_sum(int u,int v);
void QC_nega(int u,int v);
void PushDown(int now);
void Update(int now);
void Modify(int now,int l,int r,int pos,int key);
void Makenega(int now,int l,int r,int ql,int qr);
int Query_max(int now,int l,int r,int ql,int qr);
int Query_min(int now,int l,int r,int ql,int qr);
int Query_sum(int now,int l,int r,int ql,int qr);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);u++;v++;
		Add_Edge(u,v,w);
	}
	Depth[1]=1;
	dfs1(1);
	dfs2(1,1);
	int Q;scanf("%d",&Q);
	char opt[10];
	while (Q--)
	{
		scanf("%s",opt);
		if (opt[0]=='C')
		{
			int pos,key;scanf("%d%d",&pos,&key);pos++;
			pos=Id[pos];
			Modify(1,1,n,pos,key);
		}
		if (opt[0]=='N')
		{
			int u,v;scanf("%d%d",&u,&v);u++;v++;
			QC_nega(u,v);
		}
		if (opt[0]=='S')
		{
			int u,v;scanf("%d%d",&u,&v);u++;v++;
			printf("%d\n",QC_sum(u,v));
		}
		if (opt[1]=='A')
		{
			int u,v;scanf("%d%d",&u,&v);u++;v++;
			printf("%d\n",QC_max(u,v));
		}
		if (opt[1]=='I')
		{
			int u,v;scanf("%d%d",&u,&v);u++;v++;
			printf("%d\n",QC_min(u,v));
		}
	}
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	_Add(u,v,w);_Add(v,u,w);return;
}

void _Add(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs1(int u)
{
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Fa[u])
		{
			Fa[V[i]]=u;Faedge[V[i]]=W[i];
			Depth[V[i]]=Depth[u]+1;
			dfs1(V[i]);
			Size[u]+=Size[V[i]];
			if (Size[V[i]]>Size[Hson[u]]) Hson[u]=V[i];
		}
	return;
}

void dfs2(int u,int top)
{
	Id[u]=++idcnt;
	Modify(1,1,n,idcnt,Faedge[u]);
	Top[u]=top;
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u])) dfs2(V[i],V[i]);
	return;
}

int QC_max(int u,int v)
{
	int ret=-inf;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		ret=max(ret,Query_max(1,1,n,Id[Top[u]],Id[u]));
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	if (u!=v) ret=max(ret,Query_max(1,1,n,Id[u]+1,Id[v]));
	return ret;
}

int QC_min(int u,int v)
{
	int ret=inf;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		ret=min(ret,Query_min(1,1,n,Id[Top[u]],Id[u]));
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	if (u!=v) ret=min(ret,Query_min(1,1,n,Id[u]+1,Id[v]));
	return ret;
}

int QC_sum(int u,int v)
{
	int ret=0;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		ret=ret+Query_sum(1,1,n,Id[Top[u]],Id[u]);
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	if (u!=v) ret=ret+Query_sum(1,1,n,Id[u]+1,Id[v]);
	return ret;
}

void QC_nega(int u,int v)
{
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		Makenega(1,1,n,Id[Top[u]],Id[u]);
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	if (u!=v) Makenega(1,1,n,Id[u]+1,Id[v]);
	return;
}

void PushDown(int now)
{
	if (S[now].mega)
	{
		S[now].mega=0;
		int lson=now*2,rson=now*2+1;
		swap(S[lson].mx,S[lson].mn);swap(S[rson].mx,S[rson].mn);
		S[lson].mx=-S[lson].mx;S[lson].mn=-S[lson].mn;
		S[rson].mx=-S[rson].mx;S[rson].mn=-S[rson].mn;
		S[lson].sum=-S[lson].sum;S[rson].sum=-S[rson].sum;
		S[lson].mega^=1;S[rson].mega^=1;
	}
	return;
}

void Update(int now)
{
	int lson=now*2,rson=now*2+1;
	S[now].mx=max(S[lson].mx,S[rson].mx);
	S[now].mn=min(S[lson].mn,S[rson].mn);
	S[now].sum=S[lson].sum+S[rson].sum;
	return;
}

void Modify(int now,int l,int r,int pos,int key)
{
	PushDown(now);
	if (l==r)
	{
		S[now].mx=S[now].mn=S[now].sum=key;
		return;
	}
	int mid=(l+r)/2;
	if (pos<=mid) Modify(now*2,l,mid,pos,key);
	if (pos>=mid+1) Modify(now*2+1,mid+1,r,pos,key);
	Update(now);return;
}

void Makenega(int now,int l,int r,int ql,int qr)
{
	PushDown(now);
	if ((l==ql)&&(r==qr))
	{
		S[now].mega^=1;swap(S[now].mx,S[now].mn);
		S[now].mx=-S[now].mx;S[now].mn=-S[now].mn;
		S[now].sum=-S[now].sum;
		return;
	}
	int mid=(l+r)/2;
	if (qr<=mid) Makenega(now*2,l,mid,ql,qr);
	else if (ql>=mid+1) Makenega(now*2+1,mid+1,r,ql,qr);
	else
	{
		Makenega(now*2,l,mid,ql,mid);Makenega(now*2+1,mid+1,r,mid+1,qr);
	}
	Update(now);return;
}

int Query_max(int now,int l,int r,int ql,int qr)
{
	PushDown(now);
	if ((l==ql)&&(r==qr)) return S[now].mx;
	int mid=(l+r)/2;
	if (qr<=mid) return Query_max(now*2,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_max(now*2+1,mid+1,r,ql,qr);
	else return max(Query_max(now*2,l,mid,ql,mid),Query_max(now*2+1,mid+1,r,mid+1,qr));
}

int Query_min(int now,int l,int r,int ql,int qr)
{
	PushDown(now);
	if ((l==ql)&&(r==qr)) return S[now].mn;
	int mid=(l+r)/2;
	if (qr<=mid) return Query_min(now*2,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_min(now*2+1,mid+1,r,ql,qr);
	else return min(Query_min(now*2,l,mid,ql,mid),Query_min(now*2+1,mid+1,r,mid+1,qr));
}

int Query_sum(int now,int l,int r,int ql,int qr)
{
	PushDown(now);
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)/2;
	if (qr<=mid) return Query_sum(now*2,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_sum(now*2+1,mid+1,r,ql,qr);
	else return Query_sum(now*2,l,mid,ql,mid)+Query_sum(now*2+1,mid+1,r,mid+1,qr);
}
