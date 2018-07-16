#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int maxBit=17;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int ls,rs;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Val[maxN];
int root,nowsum,Size[maxN],MxSon[maxN],Fa[maxN],Pa[maxBit][maxN],Depth[maxN];
bool vis[maxN];
int nodecnt,rt1[maxN],rt2[maxN];
SegmentData S[maxN*100];

void Add_Edge(int u,int v);
void dfs_fa(int u,int fa);
void dfs_root(int u,int fa);
void Divide(int u);
void Modify_Seg(int &now,int l,int r,int pos,int key);
int Query_Seg(int now,int l,int ql,int qr);
int Dist(int u,int v);
void Modify(int u,int key);
int Query(int u,int dist);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}

	Depth[1]=1;
	dfs_fa(1,1);
	for (int i=1;i<maxBit;i++) for (int j=1;j<=n;j++) Pa[i][j]=Pa[i-1][Pa[i-1][j]];
	root=0;MxSon[0]=inf;nowsum=n;
	dfs_root(1,1);
	Divide(root);

	for (int i=1;i<=n;i++) cout<<Fa[i]<<" ";cout<<endl;

	for (int i=1;i<=n;i++) Modify(1,Val[i]);

	int lastans=0;
	while (m--)
	{
		int opt;scanf("%d",&opt);
		if (opt==0)
		{
			int x,k;scanf("%d%d",&x,&k);
			x^=lastans;k^=lastans;
			printf("%d\n",lastans=Query(x,k));
		}
		if (opt==1)
		{
			int x,k;scanf("%d%d",&x,&k);
			x^=lastans;k^=lastans;
			Modify(x,k-Val[x]);Val[x]=k;
		}
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs_fa(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Depth[V[i]]=Depth[u]+1;Pa[0][V[i]]=u;
			dfs_fa(V[i],u);
		}
	return;
}

void dfs_root(int u,int fa)
{
	Size[u]=1;MxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			dfs_root(V[i],u);
			Size[u]+=Size[V[i]];MxSon[u]=max(MxSon[u],Size[V[i]]);
		}
	MxSon[u]=max(MxSon[u],nowsum-Size[u]);
	if (MxSon[root]>MxSon[u]) root=u;
	return;
}

void Divide(int u)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			dfs_root(V[i],V[i]);
			Fa[root]=u;
			Divide(root);
		}
	return;
}

void Modify_Seg(int &now,int l,int r,int pos,int key){
	if (now==0) now=++nodecnt;
	S[now].sum+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify_Seg(S[now].ls,l,mid,pos,key);
	else Modify_Seg(S[now].rs,mid+1,r,pos,key);
	return;
}

int Query_Seg(int now,int l,int r,int ql,int qr){
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_Seg(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_Seg(S[now].rs,mid+1,r,ql,qr);
	else return Query_Seg(S[now].ls,l,mid,ql,mid)+Query_Seg(S[now].rs,mid+1,r,mid+1,qr);
}

int Dist(int u,int v)
{
	int uu=u,vv=v,lca;
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Pa[i][u])&&(Depth[Pa[i][u]]>=Depth[v])) u=Pa[i][u];
	if (u==v) lca=u;
	else{
		for (int i=maxBit-1;i>=0;i--) if ((Pa[i][u])&&(Pa[i][v])&&(Pa[i][u]!=Pa[i][v])) u=Pa[i][u],v=Pa[i][v];
		lca=Pa[0][u];
	}

	return Depth[u]+Depth[v]-2*Depth[lca];
}

void Modify(int u,int key)
{
	int now=u;
	while (now!=0)
	{
		Modify_Seg(rt1[now],0,n-1,Dist(now,u),key);
		if (Fa[now]) Modify_Seg(rt2[now],0,n-1,Dist(Fa[now],u),key);
		now=Fa[now];
	}
	return;
}

int Query(int u,int dist)
{
	dist=min(dist,n);
	int ret=0;
	int now=u;
	while (now!=0)
	{
		int d1=Dist(now,u);
		if (d1<=dist) ret+=Query_Seg(rt1[now],0,n-1,0,dist-d1);
		if (Fa[now]){
			int d2=Dist(Fa[now],u);
			ret-=Query_Seg(rt2[now],0,n-1,0,dist-d2);
		}
		now=Fa[now];
	}
	return ret;
}
/*
8 1
1 10 100 1000 10000 100000 1000000 10000000
1 2
1 3
2 4
2 5
3 6
3 7
3 8
0 3 1
//*/
