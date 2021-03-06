#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

int QPow(int x,int cnt,int Mod);
int GetFac(ll n,int p,int P);
int Lucas(ll n,ll m,int p);
int GetC(ll n,ll m,int Mod);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		ll n,m,P;scanf("%lld%lld%lld",&n,&m,&P);
		printf("%d\n",Lucas(n+m,n,P));
	}

	return 0;
}

int QPow(int x,int cnt,int Mod){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int GetFac(ll n,int p,int P){
	if (n==0) return 1;
	int ret=1;
	for (int i=1;i<=P;i++) if (i%p) ret=1ll*ret*i%P;
	ret=QPow(ret,n/P,P);
	for (int i=(ll)(n/P)*P;i<=n;i++) if (i%p) ret=1ll*ret*i%P;
	return 1ll*ret*GetFac(n/p,p,P)%P;
}

int Lucas(ll n,ll m,int Mod){
	if (m==0) return 1;
	return 1ll*GetC(n%Mod,m%Mod,Mod)*Lucas(n/Mod,m/Mod,Mod)%Mod;
}

int GetC(ll n,ll m,int Mod){
	if (m>n) return 0;
	int a=1,b=1;
	while (m) a=1ll*a*(n--)%Mod,b=1ll*b*(m--)%Mod;
	return 1ll*a*QPow(b,Mod-2,Mod)%Mod;
	/*
	for (int i=n;i!=0;i=i/Mod) modcnt+=i/Mod;
	for (int i=m;i!=0;i=i/Mod) modcnt-=i/Mod;
	for (int i=n-m;i!=0;i=i/Mod) modcnt+=i/Mod;
	return 1ll*QPow(Mod,modcnt,Mod)*GetFac(n,Mod,Mod)%Mod*QPow(GetFac(m,Mod,Mod),Mod-2,Mod)%Mod*QPow(GetFac(n-m,Mod,Mod),Mod-2,Mod)%Mod;
	//*/
}
