#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000000+3;
const int Mod=maxN;
const int inf=2147483647;

int Fac[maxN],Ifc[maxN];

int QPow(int x,int cnt);
int Lucas(int n,int m);

int main(){
	Fac[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	int Case;scanf("%d",&Case);
	while (Case--){
		int n,l,r;scanf("%d%d%d",&n,&l,&r);
		int m=r-l;
		printf("%d\n",(Lucas(n+m+1,n)-1+Mod)%Mod);
	}
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int Lucas(int n,int m){
	//cout<<"Lucas:"<<n<<" "<<m<<endl;
	if (n<m) return 0;
	if ((n<Mod)&&(m<Mod)) return 1ll*Fac[n]*Ifc[n-m]%Mod*Ifc[m]%Mod;
	return 1ll*Lucas(n%Mod,m%Mod)*Lucas(n/Mod,m/Mod)%Mod;
}
/*
2
1 4 5
2 4 5
//*/
