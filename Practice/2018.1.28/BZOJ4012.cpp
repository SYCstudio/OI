#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=150100;
const int maxM=maxN*2;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs;
	ll sum;
	ll lazy;
};

class Edge
{
public:
	ll v,w;
};

class Monster
{
public:
	int id,age;
};

bool operator < (Monster A,Monster B)
{
	return A.age<B.age;
}

int n,m,Q,A;
Monster M[maxN];
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
int Dis[maxN],Size[maxN],Hson[maxN],Fa[maxN],Top[maxN];
int idcnt=0,Id[maxN];
int nodecnt=0,Root[maxN];
ll Dissum[maxN],Edgesum[maxN];
SegmentData S[maxN*130];

void dfs1(int u,int fa);
void dfs2(int u,int top);
void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int ql,int qr);
ll Query(int n1,int n2,int l,int r,int ql,int qr,ll lazy);

int main()
{
	mem(Head,-1);
	scanf("%d%d%d",&n,&Q,&A);
	for (int i=1;i<=n;i++) scanf("%d",&M[i].age),M[i].id=i;
	sort(&M[1],&M[n+1]);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=(Edge){v,w};
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=(Edge){u,w};
	}
	Dis[1]=0;
	dfs1(1,0);
	dfs2(1,1);
	for (int i=1;i<=n;i++) Edgesum[i]+=Edgesum[i-1],Dissum[i]=Dissum[i-1]+Dis[M[i].id];
	Build(Root[0],1,n);
	for (int i=1;i<=n;i++)
	{
		int u=M[i].id;Root[i]=Root[i-1];
		while (Top[u]!=1) Modify(Root[i],1,n,Id[Top[u]],Id[u]),u=Fa[Top[u]];
		Modify(Root[i],1,n,1,Id[u]);
	}
	ll ans=0;
	while (Q--)
	{
		int u,a,b;scanf("%d%d%d",&u,&a,&b);
		int L=(a+ans)%A,R=(b+ans)%A;if (L>R) swap(L,R);
		L=lower_bound(&M[1],&M[n+1],(Monster){0,L})-M;
		R=upper_bound(&M[1],&M[n+1],(Monster){0,R})-M-1;
		ll ret=0,uu=u;
		while (Top[uu]!=1)
			ret=ret+Query(Root[L-1],Root[R],1,n,Id[Top[uu]],Id[uu],0),uu=Fa[Top[uu]];
		ret=ret+Query(Root[L-1],Root[R],1,n,1,Id[uu],0);
		ans=(ll)(R-L+1)*Dis[u]+Dissum[R]-Dissum[L-1]-2*ret;
		printf("%lld\n",ans);
	}
	return 0;
}

void dfs1(int u,int fa)
{
	Size[u]=1;Fa[u]=fa;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (E[i].v!=fa)
		{
			Dis[E[i].v]=Dis[u]+E[i].w;
			dfs1(E[i].v,u);
			Size[u]+=Size[E[i].v];
			if (Size[E[i].v]>Size[Hson[u]]) Hson[u]=E[i].v;
		}
	return;
}

void dfs2(int u,int top)
{
	Id[u]=++idcnt;Top[u]=top;
	Edgesum[idcnt]=Dis[u]-Dis[Fa[u]];
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].v!=Fa[u])&&(E[i].v!=Hson[u]))
			dfs2(E[i].v,E[i].v);
	return;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int ql,int qr)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].sum+=Edgesum[qr]-Edgesum[ql-1];
	if ((l==ql)&&(r==qr))
	{
		S[now].lazy++;
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr);
	else
	{
		Modify(S[now].ls,l,mid,ql,mid);Modify(S[now].rs,mid+1,r,mid+1,qr);
	}
	return;
}

ll Query(int n1,int n2,int l,int r,int ql,int qr,ll lazy)
{
	if ((l==ql)&&(r==qr)) return S[n2].sum-S[n1].sum+lazy*(Edgesum[r]-Edgesum[l-1]);
	int mid=(l+r)>>1;
	lazy=lazy+S[n2].lazy-S[n1].lazy;
	if (qr<=mid) return Query(S[n1].ls,S[n2].ls,l,mid,ql,qr,lazy);
	else if (ql>=mid+1) return Query(S[n1].rs,S[n2].rs,mid+1,r,ql,qr,lazy);
	else return Query(S[n1].ls,S[n2].ls,l,mid,ql,mid,lazy)+Query(S[n1].rs,S[n2].rs,mid+1,r,mid+1,qr,lazy);
}
