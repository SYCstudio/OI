#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ls (x<<1)
#define rs (ls|1)

const int maxN=101000;
const int maxM=maxN<<1;
const ll inf=10000000000;

class Mat
{
public:
	ll a00,a01,a10,a11;
};

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Sz[maxN],Hs[maxN],Fa[maxN],Top[maxN],dfncnt,dfn[maxN],lst[maxN],Id[maxN];
ll F[maxN][2],G[maxN][2],Key[maxN];
Mat S[maxN<<2];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Modify(int x,int l,int r,int pos);
Mat Query(int x,int l,int r,int ql,int qr);
Mat operator * (Mat A,Mat B);
void Skip(int u,ll key);
void outp(int x,int l,int r);

int main()
{
	//freopen("in","r",stdin);
	//freopen("defense.in","r",stdin);freopen("defense.out","w",stdout);
	char opt[5];
	int Q;
	mem(Head,-1);
	scanf("%d%d%s",&n,&Q,opt);
	for (int i=1; i<=n; i++) scanf("%lld",&Key[i]);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs1(1,1);
	dfs2(1,1);
	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<lst[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
	//Mat RR=Query(1,1,n,dfn[1],lst[1]);
	//cout<<min(RR.a00,RR.a01)<<" "<<min(RR.a10,RR.a11)<<endl;
	//for (int i=1;i<=n;i++) cout<<"("<<F[i][0]<<","<<F[i][1]<<") ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<"("<<G[i][0]<<","<<G[i][1]<<") ";cout<<endl;
	//outp(1,1,n);cout<<endl;
	while (Q--) {
		int a,x,b,y;
		scanf("%d%d%d%d",&a,&x,&b,&y);
		ll k1=Key[a],k2=Key[b];
		Skip(a,x?-inf:inf);
		Skip(b,y?-inf:inf);
		ll Ans=min(F[1][0],F[1][1]);
		if (x) Ans+=inf+k1;
		if (y) Ans+=inf+k2;
		if (Ans>=inf) printf("-1\n");
		else printf("%lld\n",Ans);
		//for (int i=1;i<=n;i++) cout<<"("<<F[i][0]<<","<<F[i][1]<<") ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<"("<<G[i][0]<<","<<G[i][1]<<") ";cout<<endl;
		Skip(a,k1);
		Skip(b,k2);
		//for (int i=1;i<=n;i++) cout<<"("<<F[i][0]<<","<<F[i][1]<<") ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<"("<<G[i][0]<<","<<G[i][1]<<") ";cout<<endl;
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
	Sz[u]=1;
	Hs[u]=0;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			dfs1(V[i],u);
			Sz[u]+=Sz[V[i]];
			Fa[V[i]]=u;
			if (Sz[V[i]]>Sz[Hs[u]]) Hs[u]=V[i];
		}
	return;
}
void dfs2(int u,int top)
{
	Top[u]=top;
	Id[dfn[u]=++dfncnt]=u;
	if (Hs[u]) dfs2(Hs[u],top),lst[u]=lst[Hs[u]];
	else lst[u]=dfncnt;
	G[u][1]=Key[u];
	for (int i=Head[u]; i!=-1; i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u])) {
			dfs2(V[i],V[i]);
			G[u][0]+=F[V[i]][1];
			G[u][1]+=min(F[V[i]][0],F[V[i]][1]);
		}
	Modify(1,1,n,dfn[u]);
	F[u][0]=G[u][0]+F[Hs[u]][1];
	F[u][1]=G[u][1]+min(F[Hs[u]][0],F[Hs[u]][1]);
	return;
}
void Modify(int x,int l,int r,int pos)
{
	if (l==r) {
		S[x]=((Mat) {
			inf,G[Id[l]][0],G[Id[l]][1],G[Id[l]][1]
		});
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(ls,l,mid,pos);
	else Modify(rs,mid+1,r,pos);
	S[x]=S[ls]*S[rs];
	return;
}
Mat Query(int x,int l,int r,int ql,int qr)
{
	//cout<<"Q:"<<x<<" ["<<l<<" "<<r<<"] ["<<ql<<" "<<qr<<"] "<<S[x].a00<<" "<<S[x].a01<<" "<<S[x].a10<<" "<<S[x].a11<<endl;
	if ((l==ql)&&(r==qr)) return S[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return Query(ls,l,mid,ql,mid)*Query(rs,mid+1,r,mid+1,qr);
}
Mat operator * (Mat A,Mat B)
{
	Mat R;
	R.a00=min(A.a00+B.a00,A.a01+B.a10);
	R.a01=min(A.a00+B.a01,A.a01+B.a11);
	R.a10=min(A.a10+B.a00,A.a11+B.a10);
	R.a11=min(A.a10+B.a01,A.a11+B.a11);
	return R;
}
void Skip(int u,ll key)
{
	G[u][1]+=key-Key[u];
	Key[u]=key;
	while (u) {
		Modify(1,1,n,dfn[u]);
		u=Top[u];
		Mat R=Query(1,1,n,dfn[u],lst[u]);
		if (Fa[u]==0) {
			F[u][0]=min(R.a00,R.a01);
			F[u][1]=min(R.a10,R.a11);
			break;
		}
		G[Fa[u]][0]-=F[u][1];
		G[Fa[u]][1]-=min(F[u][0],F[u][1]);
		F[u][0]=min(R.a00,R.a01);
		F[u][1]=min(R.a10,R.a11);
		G[Fa[u]][0]+=F[u][1];
		G[Fa[u]][1]+=min(F[u][0],F[u][1]);
		u=Fa[u];
	}
	return;
}
void outp(int x,int l,int r)
{
	if (l==r) {
		cout<<"("<<l<<","<<S[x].a00<<" "<<S[x].a01<<" "<<S[x].a10<<" "<<S[x].a11<<") ";
		return;
	}
	int mid=(l+r)>>1;
	outp(ls,l,mid);
	outp(rs,mid+1,r);
	return;
}
