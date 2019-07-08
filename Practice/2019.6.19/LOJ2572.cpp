#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
#define pb push_back

const int maxN=202000;
const int SQRT=310;
const ull base=20020729;
const int Mod=1e9+7;

int n,Q,S[maxN];
vector<int> P[maxN<<2];

int Lcp(int a,int b);
int getmid(int l,int r);
void Update(int x,int l,int r);
void Build(int x,int l,int r);
void Modify(int x,int l,int r,int ql,int qr);
void Query(int x,int l,int r,int ql,int qr,int limit,int &q);
int equal(int a,int b,int limit);
void Outp(int x,int l,int r);
namespace HASH
{
ull pwb[maxN],Hs[maxN],bplus[maxN],bsuf[maxN],pws[maxN];
int Num[maxN],numplus[maxN];
int Bl[maxN],Br[maxN],Be[maxN];
void Init();
void Modify(int x,int l,int r);
void brute_modify(int x,int l,int r,ull right=0);
ull Query(int l,int r);
ull Sm(int x);
int GetNum(int x);
}

int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=1; i<=n; i++) scanf("%d",&S[i]);
	HASH::Init();
	Build(1,1,n);
	while (Q--) {
		int type,l,r,d;
		scanf("%d%d%d",&type,&l,&r);
		if (type==1) {
			scanf("%d",&d);
			HASH::Modify(d,l,r);
			Modify(1,1,n,l,r);
		} else {
			int q=-1;
			Query(1,1,n,l,r,r,q);
			printf("%d\n",q);
		}
	}
	return 0;
}
int Lcp(int a,int b)
{
	int l=1,r=min(n-a+1,n-b+1),ret=0;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (HASH::Query(a,a+mid-1)==HASH::Query(b,b+mid-1)) ret=mid,l=mid+1;
		else r=mid-1;
	}
	return ret;
}
int getmid(int l,int r)
{
	return (l+r)>>1;
}
#define ls (x<<1)
#define rs (ls|1)
void Update(int x,int l,int r)
{
	int id=P[ls][0];
	for (int i=1; i<P[ls].size(); i++) {
		int e=equal(id,P[ls][i],r);
		if (e==1) id=P[ls][i];
		else if (e==0&&P[ls][i]<id) id=P[ls][i];
	}
	P[x].clear();
	for (int i=0; i<P[rs].size(); i++)
		if (equal(id,P[rs][i],r)>=0) P[x].pb(P[rs][i]);
	P[x].pb(id);
	return;
}
void Build(int x,int l,int r)
{
	if (l==r) {
		P[x].pb(l);
		return;
	}
	int mid=getmid(l,r);
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	Update(x,l,r);
	return;
}
void Modify(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return;
	int mid=getmid(l,r);
	if (qr<=mid) Modify(ls,l,mid,ql,qr);
	else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr);
	else Modify(ls,l,mid,ql,mid),Modify(rs,mid+1,r,mid+1,qr);
	Update(x,l,r);
	return;
}
void Query(int x,int l,int r,int ql,int qr,int limit,int &q)
{
	if (l==ql&&r==qr) {
		for (int i=0; i<P[x].size(); i++)
			if (q==-1) q=P[x][i];
			else {
				int e=equal(q,P[x][i],limit);
				if (e==1) q=P[x][i];
				else if (e==0&&q<P[x][i]) q=P[x][i];
			}
		return;
	}
	int mid=getmid(l,r);
	if (qr<=mid) Query(ls,l,mid,ql,qr,limit,q);
	else if (ql>=mid+1) Query(rs,mid+1,r,ql,qr,limit,q);
	else Query(ls,l,mid,ql,mid,limit,q),Query(rs,mid+1,r,mid+1,qr,limit,q);
	return;
}
int equal(int a,int b,int limit)
{
	int mx=max(a,b),lcp=min(Lcp(a,b),limit-mx+1);
	if (mx+lcp-1==limit) return 0;
	else if (HASH::GetNum(a+lcp)<HASH::GetNum(b+lcp)) return -1;
	else return 1;
}
void Outp(int x,int l,int r)
{
	cout<<x<<"["<<l<<" "<<r<<"]:";
	for (int i=0; i<P[x].size(); i++) cout<<P[x][i]<<" ";
	cout<<endl;
	if (l==r) return;
	int mid=getmid(l,r);
	Outp(ls,l,mid);
	Outp(rs,mid+1,r);
	return;
}
#undef ls
#undef rs

namespace HASH
{
void Init()
{
	pwb[0]=1;
	for (int i=1; i<maxN; i++) pwb[i]=pwb[i-1]*base%Mod;
	pws[1]=pwb[0];
	for (int i=2; i<maxN; i++) pws[i]=(pws[i-1]+pwb[i-1])%Mod;
	for (int i=1; i<=n; i++) {
		Be[i]=i/SQRT+1;
		Br[Be[i]]=i;
		if (Bl[Be[i]]==0) Bl[Be[i]]=i;
	}
	for (int i=n; i>=1; i--) Hs[i]=(Hs[i+1]*base%Mod+(S[i]+Mod)%Mod)%Mod;
	for (int i=1; i<=n; i++) Num[i]=S[i];
	return;
}
void Modify(int x,int l,int r)
{
	int X=(x+Mod)%Mod;
	if (Be[l]==Be[r]) {
		brute_modify(x,l,r);
		ull right=pws[r-l+1]*X%Mod*pwb[l-Bl[Be[l]]]%Mod;
		for (int i=Be[l]-1; i>=1; i--) {
			(bsuf[i]+=right)%=Mod;
			right=right*pwb[Br[i]-Bl[i]+1]%Mod;
		}
	} else {
		brute_modify(x,Bl[Be[r]],r);
		ull right=pws[r-Bl[Be[r]]+1]*X%Mod;
		for (int i=Be[r]-1; i>Be[l]; i--) {
			(bplus[i]+=X)%=Mod;
			(bsuf[i]+=right)%=Mod;
			numplus[i]+=x;
			right=(right*pwb[Br[i]-Bl[i]+1]%Mod+pws[Br[i]-Bl[i]+1]*X%Mod)%Mod;
		}
		brute_modify(x,l,Br[Be[l]],right);
		right=(right*pwb[Br[Be[l]]-l+1]%Mod+pws[Br[Be[l]]-l+1]*X%Mod)%Mod;
		right=right*pwb[l-Bl[Be[l]]]%Mod;
		for (int i=Be[l]-1; i>=1; i--) {
			(bsuf[i]+=right)%=Mod;
			right=right*pwb[Br[i]-Bl[i]+1]%Mod;
		}
	}
	return;
}
void brute_modify(int x,int l,int r,ull right)
{
	int B=Be[l];
	int X=(x+Mod)%Mod;
	for (int i=Bl[B]; i<=Br[B]; i++) Hs[i]=(Hs[i]+bplus[B]*pws[Br[B]-i+1]%Mod+bsuf[B]*pwb[Br[B]-i+1]%Mod)%Mod;
	bplus[B]=bsuf[B]=0;
	for (int i=l; i<=r; i++) Hs[i]=(Hs[i]+pws[r-i+1]*X%Mod+right*pwb[r-i+1]%Mod)%Mod;
	right=(right*pwb[r-l+1]%Mod+pws[r-l+1]*X)%Mod;
	for (int i=l-1; i>=Bl[B]; i--) right=right*base%Mod,Hs[i]=(Hs[i]+right)%Mod;

	for (int i=Bl[B]; i<=Br[B]; i++) Num[i]+=numplus[B];
	numplus[B]=0;
	for (int i=l; i<=r; i++) Num[i]+=x;
	return;
}
ull Query(int l,int r)
{
	return (Sm(l)-Sm(r+1)*pwb[r-l+1]%Mod+Mod)%Mod;
}
ull Sm(int x)
{
	int B=Be[x];
	return (Hs[x]+bplus[B]*pws[Br[B]-x+1]%Mod+bsuf[B]*pwb[Br[B]-x+1]%Mod)%Mod;
}
int GetNum(int x)
{
	return Num[x]+numplus[Be[x]];
}
}
