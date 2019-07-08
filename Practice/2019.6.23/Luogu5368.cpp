#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)

const int maxN=101000;
const int maxKey=1000000000;
const int Mod=998244353;

class SegmentData
{
public:
	int cnt,ls,rs;
};

int n,K,scnt,rt,A[maxN];
SegmentData S[maxN*30];
int Fc[maxN],Ifc[maxN];

int QPow(int x,int cnt);
int Binom(int n,int m);
void Modify(int &x,int l,int r,int p);
int Query(int x,int l,int r,int ql,int qr);
int main()
{
	//freopen("03.in","r",stdin);freopen("out","w",stdout);
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%d",&n,&K);
	for (int i=1; i<=n; i++) scanf("%d",&A[i]);
	for (int i=1; i<=n; i++) Modify(rt,0,maxKey,A[i]);

	for (int i=1; i<=n; i++)
		if (A[i]==0) printf("%d\n",Binom(n,K));
		else {
			int low=(A[i]-1)/2,Ans=0,up=min(A[i]+A[i],maxKey);
			int cnt=Query(rt,0,maxKey,0,low)+Query(rt,0,maxKey,A[i],maxKey)-1;
			Ans=Binom(cnt,K);
			//cout<<"A:"<<Ans<<" "<<cnt<<endl;
			cnt=Query(rt,0,maxKey,A[i],up-1);
			if (cnt<=K) {
				int c=Query(rt,0,maxKey,up,maxKey)+Query(rt,0,maxKey,0,A[i]-1);
				//cout<<"C:"<<cnt<<" "<<c<<endl;
				Ans=(Ans+Binom(c,K-cnt))%Mod;
			}
			printf("%d\n",Ans);
		}
	return 0;
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
int Binom(int n,int m)
{
	if (n<0||m<0||n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
void Modify(int &x,int l,int r,int p)
{
	if (x==0) x=++scnt;
	++S[x].cnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Modify(S[x].ls,l,mid,p);
	else Modify(S[x].rs,mid+1,r,p);
	return;
}
int Query(int x,int l,int r,int ql,int qr)
{
	if (ql>qr) return 0;
	if (!x) return 0;
	if (l==ql&&r==qr) return S[x].cnt;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[x].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(S[x].rs,mid+1,r,ql,qr);
	else return Query(S[x].ls,l,mid,ql,mid)+Query(S[x].rs,mid+1,r,mid+1,qr);
}
