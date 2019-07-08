#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxN=5000000;
const int Mod=1e9+7;
const int Phi=Mod-1;

ll n;
int notp[maxN],Mu[maxN],pcnt,P[maxN],Sm[maxN];
int Rc[maxN];

void Init();
int Du(ll n);
int QPow(int x,int cnt);
int main()
{
	Init();
	scanf("%lld",&n);
	int Ans=0,lstsum=0;
	Du(n);
	for (ll l=1,r; l<=n; l=r+1) {
		r=n/(n/l);
		int sum=Du(r),pw=QPow(2,(n/l)%Phi)-1;
		Ans=(Ans+1ll*(sum-lstsum+Mod)%Mod*pw%Mod)%Mod;
		lstsum=sum;
	}
	printf("%d\n",Ans);
	return 0;
}
void Init()
{
	Mu[1]=notp[1]=1;
	for (int i=2; i<maxN; i++) {
		if (!notp[i]) P[++pcnt]=i,Mu[i]=Mod-1;
		for (int j=1; j<=pcnt&&1ll*i*P[j]<maxN; j++) {
			notp[i*P[j]]=1;
			if (i%P[j]==0) break;
			Mu[i*P[j]]=(Mod-Mu[i])%Mod;
		}
	}
	for (int i=1; i<maxN; i++) Sm[i]=(Sm[i-1]+Mu[i])%Mod;
	return;
}
int Du(ll n)
{
	if (n<maxN) return Sm[n];
	else if (Rc[::n/n]) return Rc[::n/n];
	int ret=1;
	for (ll l=2,r; l<=n; l=r+1) {
		r=n/(n/l);
		int d=(r-l+1)%Mod;
		ret=(ret-1ll*(r-l+1)%Mod*Du(n/l)%Mod+Mod)%Mod;
	}
	//cerr<<"Du:"<<n<<" "<<::n/n<<" "<<c<<endl;
	return Rc[::n/n]=ret;
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
