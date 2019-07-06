#include<bits/stdc++.h>
using namespace std;

const int maxN=1010000;
const int Mod=1e9+7;

int notp[maxN],pcnt,P[maxN];
int Sigma[maxN],Mu[maxN],SSigma[maxN],Lw[maxN],Sigma2[maxN];
int Ans[maxN];

void Init();
int main(){
    Init();
    int Case;scanf("%d",&Case);
    for (int ci=1;ci<=Case;ci++){
	int n;scanf("%d",&n);
	printf("Case #%d: %d\n",ci,Ans[n]);
    }
    return 0;
}
void Init(){
    notp[1]=1;Sigma[1]=Mu[1]=1;
    for (int i=2;i<maxN;i++){
	if (notp[i]==0) Sigma[i]=i+1,Mu[i]=Mod-1,P[++pcnt]=i,Lw[i]=i;
	for (int j=1;j<=pcnt&&1ll*i*P[j]<maxN;j++){
	    notp[i*P[j]]=1;
	    if (i%P[j]==0){
		Lw[i*P[j]]=Lw[i]*P[j];
		if (Lw[i]==i) Sigma[i*P[j]]=(Sigma[i]+1ll*i*P[j]%Mod)%Mod;
		else Sigma[i*P[j]]=1ll*Sigma[i/Lw[i]]*Sigma[P[j]*Lw[i]]%Mod;
		break;
	    }
	    Mu[i*P[j]]=(Mod-Mu[i])%Mod;Lw[i*P[j]]=P[j];
	    Sigma[i*P[j]]=1ll*Sigma[i]*Sigma[P[j]]%Mod;
	}
    }
    for (int i=1;i<maxN;i++) SSigma[i]=(SSigma[i-1]+Sigma[i])%Mod;
    for (int i=1;i<maxN;i++)
	for (int j=i;j<maxN;j+=i)
	    Sigma2[j]=(Sigma2[j]+1ll*Mu[i]*i%Mod*Sigma[j/i]%Mod*Sigma[j/i]%Mod)%Mod;
    for (int i=1;i<maxN;i++) Sigma2[i]=(1ll*Sigma2[i]*i%Mod+Sigma2[i-1])%Mod;
    
    for (int i=1;i<maxN;i++)
	for (int j=i;j<maxN;j+=i)
	    Ans[j]=(Ans[j]+1ll*Mu[i]*i%Mod*Sigma[j/i]%Mod*SSigma[j/i]%Mod)%Mod;
    for (int i=1;i<maxN;i++) Ans[i]=1ll*Ans[i]%Mod*i%Mod;
    for (int i=2;i<maxN;i++) Ans[i]=(Ans[i]+Ans[i-1])%Mod;
    
    for (int i=1;i<maxN;i++) Ans[i]=(2ll*Ans[i]%Mod-Sigma2[i]+Mod)%Mod;
    return;
}
