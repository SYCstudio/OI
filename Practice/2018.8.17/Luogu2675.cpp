#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10007;
const int Mod=10007;
const int inf=2147483647;

int n;
int Fac[maxN],Inv[maxN];

int QPow(int x,int cnt);
int C(int n,int m);

int main(){
	Fac[0]=Inv[0]=1;
	for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxN-1]=QPow(Fac[maxN-1],Mod-2);
	for (int i=maxN-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;
	
	scanf("%d",&n);
	int Ans=0;
	if ((n&1)==0){
		Ans=1ll*n*C(n-1,n/2)%Mod;
		for (int i=n/2-1,j=n/2+1,k=n-1;(i>=0)&&(j<=n);i--,j++){
			Ans=(Ans+1ll*(k--)*C(n-1,i)%Mod)%Mod;
			Ans=(Ans+1ll*(k--)*C(n-1,j)%Mod)%Mod;
		}
		printf("%d\n",Ans);
	}
	else{
		for (int i=n/2,j=n/2+1,k=n;(i>=0)&&(j<=n);i--,j++){
			Ans=(Ans+1ll*(k--)*C(n-1,i)%Mod)%Mod;
			Ans=(Ans+1ll*(k--)*C(n-1,j)%Mod)%Mod;
		}
		printf("%d\n",Ans);
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

int C(int n,int m){
	if (n<m) return 0;
	if (n<maxN) return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
	return 1ll*C(n%Mod,m%Mod)*C(n/Mod,m/Mod)%Mod;
}
