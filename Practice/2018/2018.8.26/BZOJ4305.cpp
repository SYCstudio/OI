#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "number"

const int maxN=501000;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,K;
int Cnt[maxN],Sum[maxN];
int Ans[maxN];
int Fac[maxN],Inv[maxN];

int QPow(int x,int cnt);
int GetC(int n,int m);

int main(){
	Fac[0]=Inv[0]=1;
	for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxN-1]=QPow(Fac[maxN-1],Mod-2);
	for (int i=maxN-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;
	mem(Cnt,0);mem(Sum,0);mem(Ans,0);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++){
		int key;scanf("%d",&key);Cnt[key]++;
	}
	for (int i=1;i<=m;i++)
		for (int j=i;j<=m;j+=i)
			Sum[i]+=Cnt[j];
	for (int i=m;i>=1;i--){
		if (n-Sum[i]<=K) Ans[i]=1ll*GetC(Sum[i],K-(n-Sum[i]))*QPow(m/i-1,K-(n-Sum[i]))%Mod*QPow(m/i,n-Sum[i])%Mod;
		else Ans[i]=0;
		for (int j=i+i;j<=m;j+=i) Ans[i]=(Ans[i]-Ans[j]+Mod)%Mod;
	}

	for (int i=1;i<=m;i++) printf("%d ",Ans[i]);printf("\n");

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

int GetC(int n,int m){
	//cerr<<"GetC:"<<n<<" "<<m<<" "<<1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod<<endl;
	if (n<m) return 0;
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}

