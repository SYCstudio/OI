#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=1010000;
const int Mod=1e9+7;

int n,K,F[maxN],G[maxN],Cc[25],Ans[maxN];
char Input[maxN];
int notp[maxN],pcnt,Pri[maxN],Pw[maxN],Pc[maxN];

int QPow(int x,int cnt);
int main(){
    scanf("%d%s",&n,Input);for (int i=1;i<=n;i++) scanf("%d",&F[i]);
    int len=strlen(Input);
    for (int i=0;i<len;i++) K=(10ll*K%Mod+Input[i]-'0')%Mod;

    for (int i=1;i<=20;i++){
	int mul=1;for (int j=K;j<=K+i-1;j++) mul=1ll*mul*j%Mod;
	int inv=1;for (int j=1;j<=i;j++) inv=1ll*inv*j%Mod;
	inv=Inv(inv);
	Cc[i]=1ll*mul*inv%Mod;
    }

    //for (int i=1;i<=20;i++) cout<<Cc[i]<<" ";cout<<endl;

    G[1]=1;
    for (int i=2;i<=n;i++){
	if (notp[i]==0) Pri[++pcnt]=i,G[i]=Cc[1],Pw[i]=i,Pc[i]=1;
	for (int j=1;j<=pcnt&&1ll*i*Pri[j]<=n;j++){
	    notp[i*Pri[j]]=1;
	    if (i%Pri[j]==0){
		if (Pw[i]==i){
		    Pw[i*Pri[j]]=Pw[i]*Pri[j];Pc[i*Pri[j]]=Pc[i]+1;G[i*Pri[j]]=Cc[Pc[i]+1];
		}
		else{
		    Pw[i*Pri[j]]=Pw[i]*Pri[j];
		    G[i*Pri[j]]=1ll*G[i/Pw[i]]*G[Pri[j]*Pw[i]]%Mod;
		}
		break;
	    }
	    Pw[i*Pri[j]]=Pri[j];
	    G[i*Pri[j]]=1ll*G[i]*G[Pri[j]]%Mod;
	}
    }

    //for (int i=1;i<=n;i++) cout<<G[i]<<" ";cout<<endl;

    for (int i=1;i<=n;i++) for (int j=i;j<=n;j=j+i) Ans[j]=(Ans[j]+1ll*F[i]*G[j/i]%Mod)%Mod;
    for (int i=1;i<=n;i++) printf("%d ",Ans[i]);puts("");
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
