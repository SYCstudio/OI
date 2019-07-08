#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define Inv(x) QPow(x,Mod-2)
const int maxN=202000;
const int Mod=998244353;
const int inv2=499122177;
const int inf=2000000000;
class Matrix
{
public:
	int M[3][3];
	Matrix()
	{
		memset(M,0,sizeof(M));
		return;
	}
};
class ZeroData
{
public:
	int real,zero;
	ZeroData()
	{
		real=zero=1;
		return;
	}
	ZeroData(int x)
	{
		if (x==0) real=1,zero=1;
		else real=x,zero=0;
		return;
	}
	int r()
	{
		if (zero) return 0;
		return real;
	}
};

int n,LEAF,W,L,R;
vector<int> V[maxN];
vector<pair<int,int> >Lkey;
Matrix S[maxN<<2];
int dfncnt,dfn[maxN],idfn[maxN],rht[maxN];
int Fa[maxN],Top[maxN],Sz[maxN],Mx[maxN],Dep[maxN];
int Ans[maxN];
ZeroData F[maxN],G[maxN];

void dfs_init(int u);
void dfs_build(int u,int top);
void Mul(int &x,int y);
int QPow(int x,int cnt);
Matrix operator * (const Matrix A,const Matrix B);
ZeroData operator * (ZeroData A,int B);
ZeroData operator / (ZeroData A,int B);
void Modify(int x,int l,int r,int p);
Matrix Query(int x,int l,int r,int ql,int qr);
void Skip(int u);
int main()
{
	scanf("%d%d%d",&n,&L,&R);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		V[u].pb(v);
		V[v].pb(u);
	}
	Dep[1]=1;
	dfs_init(1);
	W=Top[1];
	dfs_build(1,1);
	for (int i=0; i<LEAF; i++) Lkey[i].ft=abs(W-Lkey[i].sd);
	sort(Lkey.begin(),Lkey.end());

	for (int C=0,i=1; C<=n; C++) {
		while (i<LEAF&&Lkey[i].ft<C) Skip(Lkey[i].sd),++i;
		Matrix K=Query(1,1,n,1,rht[1]);
		Ans[C]=(1-1ll*(1-K.M[1][0]+Mod)%Mod*K.M[2][0]%Mod+Mod)%Mod;
		Ans[C]=1ll*Ans[C]*QPow(2,LEAF-1)%Mod;
	}
	Ans[n]=QPow(2,LEAF-1)-1;
	for (int i=L; i<=R; i++) {
		int c=(Ans[i]-Ans[i-1]+Mod)%Mod;
		if (i==1) c=(c+QPow(2,LEAF-1))%Mod;
		printf("%d ",c);
	}
	printf("\n");
	return 0;
}
void dfs_init(int u)
{
	if (Dep[u]&1) Top[u]=-inf;
	else Top[u]=inf;
	Sz[u]=1;
	Mx[u]=0;
	for (int i=0,sz=V[u].size(); i<sz; i++)
		if (V[u][i]!=Fa[u]) {
			Fa[V[u][i]]=u;
			Dep[V[u][i]]=Dep[u]+1;
			dfs_init(V[u][i]);
			Sz[u]+=Sz[V[u][i]];
			if (Dep[u]&1) Top[u]=max(Top[u],Top[V[u][i]]);
			else Top[u]=min(Top[u],Top[V[u][i]]);
			if (Sz[V[u][i]]>Sz[Mx[u]]) Mx[u]=V[u][i];
		}
	if (Top[u]==inf||Top[u]==-inf) Top[u]=u,++LEAF,Lkey.pb(mp(0,u));
	return;
}
void dfs_build(int u,int top)
{
	Top[u]=top;
	idfn[dfn[u]=++dfncnt]=u;
	if (Mx[u]) {
		dfs_build(Mx[u],top);
		F[u]=G[u]=ZeroData(1);
		for (int i=0,sz=V[u].size(); i<sz; i++)
			if (V[u][i]!=Fa[u]&&V[u][i]!=Mx[u]) {
				dfs_build(V[u][i],V[u][i]);
				Matrix K=Query(1,1,n,dfn[V[u][i]],rht[V[u][i]]);
				F[u]=F[u]*K.M[1][0];
				G[u]=G[u]*K.M[2][0];
			}
	} else {
		if (u>W) F[u]=ZeroData(1);
		if (u<W) G[u]=ZeroData(1);
		rht[Top[u]]=dfncnt;
		if (Dep[u]&1) G[u]=ZeroData((1-G[u].r())%Mod);
		else F[u]=ZeroData((1-F[u].r())%Mod);
	}
	Modify(1,1,n,dfn[u]);
	return;
}
void Mul(int &x,int y)
{
	x=1ll*x*y%Mod;
	return;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) Mul(ret,x);
		Mul(x,x);
		cnt>>=1;
	}
	return ret;
}
ZeroData operator * (ZeroData A,int B)
{
	if (B==0) ++A.zero;
	else Mul(A.real,B);
	return A;
}
ZeroData operator / (ZeroData A,int B)
{
	if (B==0) --A.zero;
	else Mul(A.real,Inv(B));
	return A;
}
Matrix operator * (const Matrix A,const Matrix B)
{
	Matrix C;
	memset(C.M,0,sizeof(C.M));
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++) {
			unsigned long long mul=0;
			for (int k=0; k<3; k++)
				mul+=1ll*A.M[i][k]*B.M[k][j];
			C.M[i][j]=mul%Mod;
		}
	return C;
}
#define ls (x<<1)
#define rs (ls|1)
void Modify(int x,int l,int r,int p)
{
	if (l==r) {
		p=idfn[p];
		memset(S[x].M,0,sizeof(S[x].M));
		if (Mx[p]) {
			S[x].M[0][0]=S[x].M[1][0]=S[x].M[2][0]=1;
			S[x].M[1][1]=(Mod-F[p].r());
			S[x].M[2][2]=(Mod-G[p].r());
		} else {
			S[x].M[0][0]=1;
			S[x].M[1][0]=F[p].r();
			S[x].M[2][0]=G[p].r();
		}
		return;
	}
	int mid=(l+r)>>1;
	if (p<=mid) Modify(ls,l,mid,p);
	else Modify(rs,mid+1,r,p);
	S[x]=S[ls]*S[rs];
	return;
}
Matrix Query(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return S[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return Query(ls,l,mid,ql,mid)*Query(rs,mid+1,r,mid+1,qr);
}
void Skip(int u)
{
	if (u<W) F[u]=ZeroData(inv2);
	else G[u]=ZeroData(inv2);
	while (u) {
		int top=Top[u],fa=Fa[top];
		Matrix K=Query(1,1,n,dfn[top],rht[top]);
		if (fa) {
			F[fa]=F[fa]/K.M[1][0];
			G[fa]=G[fa]/K.M[2][0];
		}
		Modify(1,1,n,dfn[u]);
		K=Query(1,1,n,dfn[top],rht[top]);
		if (fa) {
			F[fa]=F[fa]*K.M[1][0];
			G[fa]=G[fa]*K.M[2][0];
		}
		u=fa;
	}
	return;
}
