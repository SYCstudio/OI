#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

//#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=201000;
const int maxM=maxN<<1;
const int inf=2147483647;

class SegmentData
{
public:
	int min,lz;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,Dfn[maxN],Last[maxN];
int Size[maxN],Depth[maxN],MxSon[maxN],Top[maxN],Fa[maxN];
SegmentData S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void PushDown(int now);
void Modify(int now,int l,int r,int ql,int qr,int key);
int Query(int now,int l,int r,int ql,int qr);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	Depth[1]=1;Fa[1]=0;
	dfs1(1,0);
	dfs2(1,1);
	//cout<<"Dfn:";for (int i=1;i<=n;i++) cout<<Dfn[i]<<" ";cout<<endl;
	//cout<<"Last:";for (int i=1;i<=n;i++) cout<<Last[i]<<" ";cout<<endl;
	//cout<<"Top:";for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++)
	{
		int key;scanf("%d",&key);
		Modify(1,1,n,Dfn[i],Dfn[i],key);
	}

	int root;scanf("%d",&root);

	for (int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if (opt==1) scanf("%d",&root);
		if (opt==2)
		{
			int u,v,key;scanf("%d%d%d",&u,&v,&key);
			while (Top[u]!=Top[v])
			{
				if (Depth[Top[u]]<Depth[Top[v]]) swap(u,v);
				Modify(1,1,n,Dfn[Top[u]],Dfn[u],key);
				u=Fa[Top[u]];
			}
			if (Depth[u]>Depth[v]) swap(u,v);
			Modify(1,1,n,Dfn[u],Dfn[v],key);
		}
		if (opt==3)
		{
			int u;scanf("%d",&u);
			if (u==root) printf("%d\n",Query(1,1,n,1,n));
			else if ((Dfn[root]>=Dfn[u])&&(Dfn[root]<=Last[u]))
			{
				int v=root;
				while (Top[v]!=Top[u])
				{
					v=Top[v];
					if (Fa[v]==u) break;
					v=Fa[v];
				}

				if (Fa[v]!=u) v=MxSon[u];
				printf("%d\n",min(Query(1,1,n,1,Dfn[v]-1),Query(1,1,n,Last[v]+1,n)));
			}
			else printf("%d\n",Query(1,1,n,Dfn[u],Last[u]));
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs1(int u,int fa)
{
	Size[u]=1;MxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Fa[V[i]]=u;Depth[V[i]]=Depth[u]+1;
			dfs1(V[i],u);Size[u]+=Size[V[i]];
			if (Size[V[i]]>Size[MxSon[u]]) MxSon[u]=V[i];
		}
	return;
}

void dfs2(int u,int top)
{
	Top[u]=top;Dfn[u]=++dfncnt;
	if (MxSon[u]!=0)
	{
		dfs2(MxSon[u],top);
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((V[i]!=MxSon[u])&&(V[i]!=Fa[u]))
				dfs2(V[i],V[i]);
	}
	Last[u]=dfncnt;return;
}

void PushDown(int now)
{
	if (S[now].lz)
	{
		S[lson].lz=S[rson].lz=S[lson].min=S[rson].min=S[now].lz;
		S[now].lz=0;
	}
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
	if ((l==ql)&&(r==qr)){
		S[now].lz=S[now].min=key;return;
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
	S[now].min=min(S[lson].min,S[rson].min);
	return;
}

int Query(int now,int l,int r,int ql,int qr)
{
	if (ql>qr) return inf;
	if ((l==ql)&&(r==qr)) return S[now].min;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}
