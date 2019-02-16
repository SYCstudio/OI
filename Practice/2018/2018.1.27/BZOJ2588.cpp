#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200010;
const int maxM=maxN*2;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs;
	int sum;
};

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int NodeW[maxN],Num[maxN];
int Fa[maxN][25],Depth[maxN];
int nodecnt=0,root[maxN];
SegmentData S[maxN*30];

void dfs1(int u,int fa);
void dfs2(int u);
int LCA(int u,int v);
void Build(int &now,int l,int r);
void Update(int &now,int l,int r,int num);
int Query(int n1,int n2,int n3,int n4,int l,int r,int kth);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&NodeW[i]),Num[i]=NodeW[i];
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	}
	Depth[1]=1;
	dfs1(1,0);
	for (int j=1;j<25;j++)
		for (int i=1;i<=n;i++)
			if (Fa[i][j-1]!=0) Fa[i][j]=Fa[Fa[i][j-1]][j-1];
	sort(&Num[1],&Num[n+1]);
	for (int i=1;i<=n;i++) NodeW[i]=lower_bound(&Num[1],&Num[n+1],NodeW[i])-Num;
	//for (int i=1;i<=n;i++) cout<<NodeW[i]<<" ";cout<<endl;
	Build(root[0],1,n);
	dfs2(1);
	int ans=0;
	for (int ti=1;ti<=m;ti++)
	{
		int u,v,kth;scanf("%d%d%d",&u,&v,&kth);u^=ans;
		int lca=LCA(u,v);
		//cout<<u<<" "<<v<<" "<<lca<<" "<<Fa[lca][0]<<endl;
		ans=Num[Query(root[u],root[v],root[lca],root[Fa[lca][0]],1,n,kth)];
		printf("%d",ans);
		if (ti!=m) printf("\n");
	}
	return 0;
}

void dfs1(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Depth[V[i]]=Depth[u]+1;
			Fa[V[i]][0]=u;
			dfs1(V[i],u);
		}
	return;
}

void dfs2(int u)
{
	root[u]=root[Fa[u][0]];
	Update(root[u],1,n,NodeW[u]);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Fa[u][0])
			dfs2(V[i]);
	return;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);
	Build(S[now].rs,mid+1,r);
	return;
}

void Update(int &now,int l,int r,int num)
{
	S[++nodecnt]=S[now];
	now=nodecnt;S[now].sum++;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (num<=mid) Update(S[now].ls,l,mid,num);
	else Update(S[now].rs,mid+1,r,num);
	return;
}

int Query(int n1,int n2,int n3,int n4,int l,int r,int kth)
{
	if (l==r) return l;
	int lsize=S[S[n1].ls].sum+S[S[n2].ls].sum-S[S[n3].ls].sum-S[S[n4].ls].sum;
	//cout<<'['<<l<<','<<r<<"] "<<kth<<" "<<lsize<<endl;
	int mid=(l+r)>>1;
	if (lsize>=kth) return Query(S[n1].ls,S[n2].ls,S[n3].ls,S[n4].ls,l,mid,kth);
	else return Query(S[n1].rs,S[n2].rs,S[n3].rs,S[n4].rs,mid+1,r,kth-lsize);
}

int LCA(int u,int v)
{
	if ((u==1)||(v==1)) return 1;
	if (Depth[v]>Depth[u]) swap(u,v);
	for (int i=24;i>=0;i--) if ((Fa[u][i])&&(Depth[Fa[u][i]]>=Depth[v])) u=Fa[u][i];
	if (u==v) return u;
	for (int i=24;i>=0;i--) if ((Fa[u][i])&&(Fa[v][i])&&(Fa[u][i]!=Fa[v][i])) u=Fa[u][i],v=Fa[v][i];
	return Fa[u][0];
}
