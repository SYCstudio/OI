#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

const int maxN=101000;
const int Mod=1e9+7;

int Fc[maxN],Ifc[maxN];

int Inv(int x);
int QPow(int x,int cnt);
int Calc(int n,int K);
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxN-1]=Inv(Fc[maxN-1]);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

    int n,K;scanf("%d%d",&n,&K);
    printf("%d\n",(Calc(n,K)-Calc(n,K-1)+Mod)%Mod);return 0;
}
int Inv(int x){
    return QPow(x,Mod-2);
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;
	cnt>>=1;x=1ll*x*x%Mod;
    }
    return ret;
}
int Calc(int n,int K){
    int ret=0;
    for (int i=0;i<=K;i++)
	if (i&1) ret=(ret-1ll*QPow(K-i,n)*Fc[n]%Mod*Ifc[i]%Mod*Ifc[n-i]%Mod+Mod)%Mod;
	else ret=(ret+1ll*QPow(K-i,n)*Fc[n]%Mod*Ifc[i]%Mod*Ifc[n-i]%Mod)%Mod;
    return ret;
}
