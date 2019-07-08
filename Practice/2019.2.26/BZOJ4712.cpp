#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=201000;
const int maxM=maxN<<1;
const int inf=1000000000;
const ll INF=1e18;

class Matrix
{
public:
	ll a00,a01,a10,a11;
};
const Matrix M0=((Matrix)
{
	0,0,0,0
});

int n;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
ll Val[maxN],F[maxN];
int Sz[maxN],Mx[maxN],dfncnt,dfn[maxN],idfn[maxN],rht[maxN],Fa[maxN],Top[maxN],Dep[maxN];
Matrix Ms[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
Matrix operator * (Matrix A,Matrix B);
void Modify(int x,int l,int r,int p);
Matrix Query(int x,int l,int r,int ql,int qr);
int main()
{
	//freopen("2.in","r",stdin);freopen("out","w",stdout);
	scanf("%d",&n);
	memset(Head,-1,sizeof(Head));
	for (int i=1; i<=n; i++) scanf("%lld",&Val[i]);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<F[i]<<endl;
	int Q;
	scanf("%d",&Q);
	while (Q--) {
		char ipt;
		int u;
		scanf(" %c%d",&ipt,&u);
		if (ipt=='Q') {
			Matrix R=Query(1,1,n,dfn[u],rht[Top[u]])*M0;
			//cout<<"("<<R.a00<<" "<<R.a01<<" "<<R.a10<<" "<<R.a11<<")"<<endl;
			printf("%lld\n",R.a00);
		}
		if (ipt=='C') {
			ll key;
			scanf("%lld",&key);
			Val[u]+=key;
			while (Top[u]!=1) {
				int t=Top[u],f=Fa[t];
				Matrix R=Query(1,1,n,dfn[t],rht[t])*M0;
				F[f]-=R.a00;
				Modify(1,1,n,dfn[u]);
				R=Query(1,1,n,dfn[t],rht[t])*M0;
				F[f]+=R.a00;
				u=f;
			}
			Modify(1,1,n,dfn[u]);
		}
		/*
		for (int i=1;i<=n;i++) cout<<"("<<F[i]<<","<<Val[i]<<") ";cout<<endl;
		for (int i=1;i<=n;i++){
		    Matrix R=Query(1,1,n,dfn[i],dfn[i]);
		    cout<<"("<<R.a00<<" "<<R.a01<<" "<<R.a10<<" "<<R.a11<<")"<<endl;
		}
		//*/
	}
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs1(int u,int fa)
{
	Fa[u]=fa;
	Dep[u]=Dep[fa]+1;
	Sz[u]=1;
	Mx[u]=0;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			dfs1(V[i],u);
			Sz[u]+=Sz[V[i]];
			if (Sz[V[i]]>Sz[Mx[u]]) Mx[u]=V[i];
		}
	return;
}
void dfs2(int u,int top)
{
	idfn[dfn[u]=++dfncnt]=u;
	Top[u]=top;
	if (Mx[u]) dfs2(Mx[u],top);
	else rht[Top[u]]=dfncnt,F[u]=INF;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=Fa[u]&&V[i]!=Mx[u]) {
			dfs2(V[i],V[i]);
			Matrix R=Query(1,1,n,dfn[V[i]],rht[V[i]])*M0;
			F[u]+=R.a00;
		}
	Modify(1,1,n,dfn[u]);
	return;
}
Matrix operator * (Matrix A,Matrix B)
{
	Matrix R;
	R.a00=min(A.a00+B.a00,A.a01+B.a10);
	R.a01=min(A.a00+B.a01,A.a01+B.a11);
	R.a10=min(A.a10+B.a00,A.a11+B.a10);
	R.a11=min(A.a10+B.a01,A.a11+B.a11);
	return R;
}
#define ls (x<<1)
#define rs (ls|1)
void Modify(int x,int l,int r,int p)
{
	if (l==r) {
		int u=idfn[l];
		Ms[x]=((Matrix) {
			F[u],Val[u],0,0
		});
		return;
	}
	int mid=(l+r)>>1;
	p<=mid?Modify(ls,l,mid,p):Modify(rs,mid+1,r,p);
	Ms[x]=Ms[ls]*Ms[rs];
	return;
}
Matrix Query(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return Ms[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return Query(ls,l,mid,ql,mid)*Query(rs,mid+1,r,mid+1,qr);
}