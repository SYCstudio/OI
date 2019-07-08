#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;

typedef long long ll;
const int maxN=101000;
const int Mod=998244353;

class StackData
{
public:
	int l,r;
	void Init(int a,int b)
	{
		l=a;
		r=b;
		return;
	}
};

int n,m,Seq[maxN];
int Om[maxN],revtop,top;
vector<int> Qm[maxN];
StackData Srev[maxN],Sn[maxN];
vector<StackData> Undo[maxN];
int Ans[maxN];
ll Sml[maxN];
int Sm[maxN],Sm2[maxN],Pre[maxN],Suf[maxN];

int Inv(int x);
int QPow(int x,int cnt);
bool cmp(StackData A,StackData B);
bool cmp(int l1,ll s1,int l2,ll s2);
bool cmp(int l1,ll s1,StackData B);
bool cmp(StackData A,int l2,ll s2);
StackData operator + (StackData A,StackData B);
int Calc(int l,int r);
int BinaryLeft(int x,int key,int pr);
int BinaryRight(int x,int key);
double C(StackData A);
int brute(int l,int r);
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&Seq[i]);
	for (int i=1; i<=n; i++) Sml[i]=Sml[i-1]+Seq[i],Sm[i]=(Sm[i-1]+Seq[i])%Mod,Sm2[i]=(Sm2[i-1]+1ll*Seq[i]*Seq[i]%Mod)%Mod;
	for (int i=1; i<=m; i++) {
		int x;
		scanf("%d%d",&x,&Om[i]);
		Qm[x].push_back(i);
	}
	Sn[0]=Srev[0]=((StackData) {
		1,0
	});
	revtop=top=0;
	for (int i=n; i>=1; i--) {
		StackData now;
		now.Init(i,i);
		while (revtop&&cmp(Srev[revtop],now)) {
			now=now+Srev[revtop];
			Undo[i].push_back(Srev[revtop]);
			--revtop;
		}
		Srev[++revtop]=now;
		Suf[i]=(Suf[now.r+1]+Calc(now.l,now.r))%Mod;
	}
	for (int i=1; i<=n; i++) {
		--revtop;
		while (Undo[i].size()) Srev[++revtop]=Undo[i].back(),Undo[i].pop_back();

		for (int j=0,sz=Qm[i].size(); j<sz; j++) {
			int id=Qm[i][j],key=Om[id],R=BinaryRight(i,key-Seq[i]),L=BinaryLeft(i,key-Seq[i],R);
			Ans[id]=(Pre[L-1]+Suf[R+1])%Mod;
			int ae=((Sm[R]-Sm[L-1]+key)%Mod-Seq[i])%Mod;
			ae=(ae+Mod)%Mod;
			int sm=ae;
			ae=1ll*ae*Inv(R-L+1)%Mod;
			int sm2=(Sm2[R]-Sm2[L-1]+Mod)%Mod;
			sm2=(sm2-1ll*Seq[i]*Seq[i]%Mod+Mod)%Mod;
			sm2=(sm2+1ll*key*key%Mod)%Mod;
			Ans[id]=(Ans[id]+sm2)%Mod;
			Ans[id]=(Ans[id]-2ll*ae*sm%Mod+Mod)%Mod;
			Ans[id]=(Ans[id]+1ll*ae*ae%Mod*(R-L+1)%Mod)%Mod;
		}

		StackData now;
		now.Init(i,i);
		while (top&&cmp(now,Sn[top])) {
			now=now+Sn[top];
			--top;
		}
		Sn[++top]=now;
		Pre[i]=(Pre[now.l-1]+Calc(now.l,now.r))%Mod;
	}
	printf("%d\n",Pre[n]);
	for (int i=1; i<=m; i++) printf("%d\n",Ans[i]);
	return 0;
}
int Inv(int x)
{
	return QPow(x,Mod-2);
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
bool cmp(StackData A,StackData B)
{
	return cmp(A.r-A.l+1,Sml[A.r]-Sml[A.l-1],B.r-B.l+1,Sml[B.r]-Sml[B.l-1]);
}
bool cmp(int l1,ll s1,StackData B)
{
	return cmp(l1,s1,B.r-B.l+1,Sml[B.r]-Sml[B.l-1]);
}
bool cmp(StackData A,int l2,ll s2)
{
	return cmp(A.r-A.l+1,Sml[A.r]-Sml[A.l-1],l2,s2);
}
bool cmp(int l1,ll s1,int l2,ll s2)
{
	if (l1<=0||l2<=0) return 1;
	assert(l1>=0);
	assert(s1>=0);
	assert(l2>=0);
	assert(s2>=0);
	return s1*l2<=s2*l1;
}
StackData operator + (StackData A,StackData B)
{
	A.l=min(A.l,B.l);
	A.r=max(A.r,B.r);
	return A;
}
int Calc(int l,int r)
{
	int p=1ll*(Sm[r]-Sm[l-1]+Mod)%Mod*Inv(r-l+1)%Mod;
	int s=((Sm2[r]-Sm2[l-1]+Mod)%Mod+1ll*p*p%Mod*(r-l+1)%Mod)%Mod;
	s=(s-2ll*p*(Sm[r]-Sm[l-1]+Mod)%Mod+Mod)%Mod;
	return s;
}
int BinaryLeft(int x,int key,int pr)
{
	if (x==1) return 1;
	if (cmp(Sn[top],pr-x+1,Sml[pr]-Sml[x-1]+key)) return x;
	int l=1,r=top,L=1;
	while (l<=r) {
		int mid=(l+r)>>1,pl=Sn[mid].l;
		if (cmp(Sn[mid-1],pr-pl+1,Sml[pr]-Sml[pl-1]+key)) L=pl,l=mid+1;
		else r=mid-1;
	}
	return L;
}
int BinaryRight(int x,int key)
{
	if (x==n) return x;
	int pl=BinaryLeft(x,key,x);
	if (cmp(x-pl+1,Sml[x]-Sml[pl-1]+key,Srev[revtop])) return x;
	int l=1,r=revtop,R=Srev[revtop].r;
	while (l<=r) {
		int mid=(l+r)>>1,pr=Srev[mid].r;
		pl=BinaryLeft(x,key,pr);
		if (cmp(pr-pl+1,Sml[pr]-Sml[pl-1]+key,Srev[mid-1])) R=pr,l=mid+1;
		else r=mid-1;
	}
	return R;
}
double C(StackData A)
{
	return (double)(Sml[A.r]-Sml[A.l-1])/(double)(A.r-A.l+1);
}
int brute(int l,int r)
{
	int sum=0;
	for (int i=l; i<=r; i++) sum=(sum+Seq[i])%Mod;
	cout<<(double)sum/(double)(r-l+1)<<endl;
	sum=1ll*sum*Inv(r-l+1)%Mod;
	int ret=0;
	for (int i=l; i<=r; i++) {
		int mul=Seq[i]-sum;
		ret=(ret+1ll*mul*mul%Mod)%Mod;
	}
	return ret;
}
