#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long

const int maxN=20010;
const int Mod=998244353;

int Fac[maxN],Ifc[maxN];

int QPow(int x,int cnt);
int C(int n,int m);

int main(){
	int n,K;
	Fac[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	scanf("%d%d",&K,&n);
	for (int i=2;i<=K+K;i++){
		int sum=0,mm=(min(i-1,K)-max(i-K,1)+2)/2;
		for (int j=0;j+j<=n;j++) sum=((1ll*((j&1)?(-1):(1))*C(mm,j)%Mod*C(n-2*j+K-1,K-1)%Mod+sum)%Mod+Mod)%Mod;
		printf("%d\n",sum);
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

int C(int n,int m){
	if (n<m) return 0;
	//cout<<n<<" "<<m<<endl;
	return 1ll*Fac[n]*Ifc[n-m]%Mod*Ifc[m]%Mod;
}
