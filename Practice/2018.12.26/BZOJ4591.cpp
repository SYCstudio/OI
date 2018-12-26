#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

#define ll long long

const int maxN=3000;
const int Mod=2333;

int Tr[maxN][maxN],Sr[maxN][maxN];

int Calc(ll n,ll K);
int Lucas(ll n,ll m);

int main(){
	for (int i=0;i<Mod;i++) for (int j=Tr[i][0]=1;j<=i;j++) Tr[i][j]=(Tr[i-1][j]+Tr[i-1][j-1])%Mod;
	for (int i=0;i<Mod;i++) Sr[i][0]=Tr[i][0];
	for (int i=0;i<Mod;i++) for (int j=1;j<Mod;j++) Sr[i][j]=(Sr[i][j-1]+Tr[i][j])%Mod;
	int Case;scanf("%d",&Case);
	while (Case--){
		ll n,K;scanf("%lld%lld",&n,&K);
		printf("%d\n",Calc(n,K));
	}
}

int Calc(ll n,ll K){
	if ((n<Mod)&&(K<Mod)) return Sr[n][K];
	return (1ll*Calc(n/Mod,K/Mod-1)*Calc(n%Mod,Mod-1)%Mod+1ll*Calc(n%Mod,K%Mod)*Lucas(n/Mod,K/Mod)%Mod)%Mod;
}

int Lucas(ll n,ll m){
	if (n<m) return 0;
	if ((n<Mod)&&(m<Mod)) return Tr[n][m];
	return 1ll*Lucas(n/Mod,m/Mod)*Lucas(n%Mod,m%Mod)%Mod;
}
