#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=100101;
const int maxM=maxN*2;
const int inf=2147483647;

class Data
{
public:
	int cnt;
	int left,right;
	int cover;
	Data(){
		cover=-1;
	}
};

int n,m;
int Col[maxN];
Data S[maxN<<2];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Hson[maxN],Fa[maxN],Top[maxN],Depth[maxN];
int idcnt,Id[maxN],Di[maxN];

Data operator + (Data A,Data B);
void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Build(int now,int l,int r);
void Modify_TC(int u,int v,int key);
int Query_TC(int u,int v);
void PushDown(int now);
void Modify_Seg(int now,int l,int r,int ql,int qr,int key);
Data Query_Seg(int now,int l,int r,int ql,int qr);

int main()
{
	ios::sync_with_stdio(false);
	mem(Head,-1);

	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>Col[i];
	for (int i=1;i<n;i++)
	{
		int u,v;cin>>u>>v;
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Depth[1]=1;
	dfs1(1,1);dfs2(1,1);
	//cout<<"TC over!:"<<endl;
	Build(1,1,n);

	while (m--)
	{
		char opt;cin>>opt;
		if (opt=='C')
		{
			int u,v,col;cin>>u>>v>>col;
			Modify_TC(u,v,col);
		}
		if (opt=='Q')
		{
			int u,v;cin>>u>>v;
			cout<<Query_TC(u,v)<<endl;
		}
	}
	return 0;
}

Data operator + (Data A,Data B)
{
	Data Ret;
	Ret.left=A.left;Ret.right=B.right;
	Ret.cnt=A.cnt+B.cnt-(A.right==B.left);
	return Ret;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa)
{
	Size[u]=1;Hson[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[V[i]]=u;Depth[V[i]]=Depth[u]+1;
			dfs1(V[i],u);
			Size[u]+=Size[V[i]];
			if (Size[Hson[u]]<Size[V[i]]) Hson[u]=V[i];
		}
	return;
}

void dfs2(int u,int top)
{
	Top[u]=top;Id[u]=++idcnt;Di[idcnt]=u;
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i],V[i]);
	return;
}

void Build(int now,int l,int r)
{
	if (l==r)
	{
		S[now].cnt=1;S[now].left=S[now].right=Col[Di[l]];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now]=S[lson]+S[rson];
	return;
}

void Modify_TC(int u,int v,int key)
{
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		Modify_Seg(1,1,n,Id[Top[u]],Id[u],key);
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	Modify_Seg(1,1,n,Id[u],Id[v],key);
	return;
}

int Query_TC(int u,int v)
{
	int Ret=0,lastcolu=-1,lastcolv=-1;
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v),swap(lastcolu,lastcolv);
		Data G=Query_Seg(1,1,n,Id[Top[u]],Id[u]);
		Ret+=G.cnt-(G.right==lastcolu);
		lastcolu=G.left;
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v),swap(lastcolu,lastcolv);
	Data G=Query_Seg(1,1,n,Id[u],Id[v]);
	Ret+=G.cnt-(G.left==lastcolu)-(G.right==lastcolv);
	return Ret;
}

void PushDown(int now)
{
	if (S[now].cover!=-1)
	{
		int col=S[now].cover;
		S[lson].cnt=1;S[lson].left=S[lson].right=col;S[lson].cover=col;
		S[rson].cnt=1;S[rson].left=S[rson].right=col;S[rson].cover=col;
		S[now].cover=-1;
	}
	return;
}

void Modify_Seg(int now,int l,int r,int ql,int qr,int key)
{
	if ((l==ql)&&(r==qr))
	{
		S[now].cover=S[now].left=S[now].right=key;
		S[now].cnt=1;S[now].cover=key;
		return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify_Seg(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify_Seg(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify_Seg(lson,l,mid,ql,mid,key);
		Modify_Seg(rson,mid+1,r,mid+1,qr,key);
	}
	S[now]=S[lson]+S[rson];
	return;
}

Data Query_Seg(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now];
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_Seg(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_Seg(rson,mid+1,r,ql,qr);
	else return Query_Seg(lson,l,mid,ql,mid)+Query_Seg(rson,mid+1,r,mid+1,qr);
}
