#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

#define ll long long

const int maxN=5050000;
const int Mod=998244353;

int F[maxN];
int Fac[maxN],Ifc[maxN],Pow2[maxN];

int QPow(int x,int cnt);

int main(){
	Fac[0]=Ifc[0]=1;Pow2[0]=1;
	for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod,Pow2[i]=2ll*Pow2[i-1]%Mod;
	Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	F[0]=1;F[1]=0;
	for (int i=2;i<maxN;i++) F[i]=2ll*i*(2*i-2)%Mod*(F[i-1]+1ll*(2*i-2)*F[i-2]%Mod)%Mod;
	int Case;scanf("%d",&Case);
	while (Case--){
		int n,K;scanf("%d%d",&n,&K);
		printf("%lld\n",1ll*Fac[n]*Ifc[n-K]%Mod*Fac[n]%Mod*Ifc[n-K]%Mod*Ifc[K]%Mod*Pow2[K]%Mod*F[n-K]%Mod);
	}
	return 0;
}
int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
