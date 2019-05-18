#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=110;
const int maxP=50500;
const int Mod=998244353;

int n;
int S[maxN],P[maxN],SP;
int FF[maxP+maxP],GG[maxP+maxP],Bp[maxP+maxP],Idp[maxP],Pre[maxP],Suf[maxP];
int *F=FF+maxP,*G=GG+maxP,*B=Bp+maxP;

int QPow(int x,int cnt);
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&S[i]);for (int i=1;i<=n;i++) scanf("%d",&P[i]),SP+=P[i];

    int inv2=Inv(2);
    F[0]=G[0]=1;
    for (int i=1;i<=n;i++){
	for (int j=-SP;j<=SP;j++) B[j]=F[j],F[j]=0;
	for (int j=-SP;j+P[i]<=SP;j++) F[j+P[i]]=(F[j+P[i]]+1ll*B[j]*inv2%Mod)%Mod;
	if (S[i]) for (int j=-SP+P[i];j<=SP;j++) F[j-P[i]]=(F[j-P[i]]-1ll*B[j]*inv2%Mod+Mod)%Mod;
	else for (int j=-SP+P[i];j<=SP;j++) F[j-P[i]]=(F[j-P[i]]+1ll*B[j]*inv2%Mod)%Mod;

	for (int j=-SP;j<=SP;j++) B[j]=G[j],G[j]=0;
	for (int j=-SP;j+P[i]<=SP;j++) G[j+P[i]]=(G[j+P[i]]+1ll*B[j]*inv2%Mod)%Mod;
	for (int j=-SP+P[i];j<=SP;j++) G[j-P[i]]=(G[j-P[i]]+1ll*B[j]*inv2%Mod)%Mod;
    }
    //for (int i=-SP;i<=SP;i++) cout<<F[i]<<" ";cout<<endl;
    //for (int i=-SP;i<=SP;i++) cout<<G[i]<<" ";cout<<endl;
    int Ans=0;
    for (int i=-SP;i<SP;i++) Ans=(Ans+1ll*(G[i]-F[i]+Mod)%Mod*Inv(SP-i)%Mod)%Mod;
    Ans=1ll*Ans*QPow(2,n)%Mod*SP%Mod;
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
