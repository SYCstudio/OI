#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int inf=2147483647;

class SegData
{
public:
	int ls,rs;
	ll sum,mx;
};

int n,Q,nodecnt;
int Color[maxN],root[maxN],Val[maxN];
SegData S[maxN*100];
int Fa[maxN],Depth[maxN],Top[maxN],Hson[maxN],Size[maxN];
int idcnt=0,Id[maxN];
int edgecnt=-1,Head[maxN],Next[maxN*2],V[maxN*2];

void dfs1(int u,int fa);
void dfs2(int u,int top);
void Update(int now);
void Modify(int &now,int l,int r,int pos,int val);
ll QSum(int u,int v);
ll QMax(int u,int v);
ll SSum(int now,int l,int r,int ql,int qr);
ll SMax(int now,int l,int r,int ql,int qr);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%d%d",&Val[i],&Color[i]);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	}
	Depth[1]=1;
	dfs1(1,1);
	dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) Modify(root[Color[i]],1,n,Id[i],Val[i]);
	char opt[10];
	while (Q--)
	{
		scanf("%s",opt);
		if ((opt[0]=='C')&&(opt[1]=='C'))
		{
			int city,col;scanf("%d%d",&city,&col);
			Modify(root[Color[city]],1,n,Id[city],0);
			Modify(root[col],1,n,Id[city],Val[city]);
			Color[city]=col;
		}
		if ((opt[0]=='C')&&(opt[1]=='W'))
		{
			int city,val;scanf("%d%d",&city,&val);
			Val[city]=val;
			Modify(root[Color[city]],1,n,Id[city],val);
		}
		if ((opt[0]=='Q')&&(opt[1]=='S'))
		{
			int u,v;scanf("%d%d",&u,&v);
			printf("%lld\n",QSum(u,v));
		}
		if ((opt[0]=='Q')&&(opt[1]=='M'))
		{
			int u,v;scanf("%d%d",&u,&v);
			printf("%lld\n",QMax(u,v));
		}
	}
	return 0;
}

void dfs1(int u,int fa)
{
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[V[i]]=u;Depth[V[i]]=Depth[u]+1;
			dfs1(V[i],u);
			if (Size[V[i]]>Size[Hson[u]]) Hson[u]=V[i];
			Size[u]+=Size[V[i]];
		}
	return;
}

void dfs2(int u,int top)
{
	Top[u]=top;
	Id[u]=++idcnt;
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i],V[i]);
	return;
}

void Update(int now)
{
	int ls=S[now].ls,rs=S[now].rs;
	S[now].sum=S[ls].sum+S[rs].sum;
	S[now].mx=max(S[ls].mx,S[rs].mx);
	return;
}

void Modify(int &now,int l,int r,int pos,int val)
{
	if (now==0) now=++nodecnt;
	if (l==r)
	{
		S[now].sum=S[now].mx=val;
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,val);
	else Modify(S[now].rs,mid+1,r,pos,val);
	Update(now);
	return;
}

ll QSum(int u,int v)
{
	ll ret=0,col=Color[v];
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		ret=ret+SSum(root[col],1,n,Id[Top[u]],Id[u]);
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	ret=ret+SSum(root[col],1,n,Id[u],Id[v]);
	return ret;
}

ll QMax(int u,int v)
{
	ll ret=0,col=Color[v];
	while (Top[u]!=Top[v])
	{
		if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
		ret=max(ret,SMax(root[col],1,n,Id[Top[u]],Id[u]));
		u=Fa[Top[u]];
	}
	if (Depth[u]>Depth[v]) swap(u,v);
	ret=max(ret,SMax(root[col],1,n,Id[u],Id[v]));
	return ret;
}

ll SSum(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return SSum(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return SSum(S[now].rs,mid+1,r,ql,qr);
	else return SSum(S[now].ls,l,mid,ql,mid)+SSum(S[now].rs,mid+1,r,mid+1,qr);
}

ll SMax(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].mx;
	int mid=(l+r)>>1;
	if (qr<=mid) return SMax(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return SMax(S[now].rs,mid+1,r,ql,qr);
	else return max(SMax(S[now].ls,l,mid,ql,mid),SMax(S[now].rs,mid+1,r,mid+1,qr));
}
