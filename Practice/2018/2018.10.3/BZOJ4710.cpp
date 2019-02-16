#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5010;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m;
int Num[maxN];
int Fac[maxN],Inv[maxN];

int QPow(int x,int cnt);
int C(int n,int m);

int main(){
	Inv[0]=Fac[0]=1;
	for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxN-1]=QPow(Fac[maxN-1],Mod-2);
	for (int i=maxN-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d",&Num[i]);

	int Ans=0;
	for (int i=0;i<=n;i++){
		int tmp=C(n,i);
		for (int j=1;j<=m;j++) tmp=1ll*tmp*C(Num[j]+(n-i)-1,(n-i)-1)%Mod;
		if (i&1) Ans=(Ans+Mod-tmp)%Mod;
		else Ans=(Ans+tmp)%Mod;
	}
	printf("%d\n",Ans);return 0;
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
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
/*
5 4
1 3 3 5
//*/
