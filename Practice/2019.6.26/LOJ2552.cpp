#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=210;
const int maxM=110;
const int Mod=998244353;
const int inf=2000000000;

int n,Q;
int Mlim[maxN],Fm[maxN][maxM],Gm[maxM];
int dppre[maxN][maxN];
int dpsuf[maxN][maxN];

int QPow(int x,int cnt);
int main(){
    freopen("4.in","r",stdin);freopen("out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
	scanf("%d",&Mlim[i]);Fm[i][Mlim[i]]=1;
    }
    scanf("%d",&Q);
    while (Q--){
	int type;scanf("%d",&type);
	if (type==0){
	    int id,u,v;scanf("%d%d%d",&id,&u,&v);
	    u=1ll*u*Inv(v)%Mod;
	    for (int i=0;i<=Mlim[id];i++){
		Gm[i]=1ll*Fm[id][i]*(1-u+Mod)%Mod;
		Gm[max(0,i-1)]=(Gm[max(0,i-1)]+1ll*Fm[id][i]*u%Mod)%Mod;
	    }
	    for (int i=0;i<=Mlim[id];i++) Fm[id][i]=Gm[i],Gm[i]=0;
	}
	else{
	    int K;scanf("%d",&K);vector<int> P(K+1);
	    
	    P[0]=-inf;
	    for (int i=1;i<=K;i++) scanf("%d",&P[i]);
	    
	    dppre[0][0]=1;
	    for (int i=1;i<=K;i++){
		for (int j=0;j<=i;j++) dppre[i][j]=1ll*dppre[i-1][j]*Fm[P[i]][0]%Mod;
		for (int j=1;j<=i;j++) dppre[i][j]=(dppre[i][j]+1ll*(1-Fm[P[i]][0]+Mod)%Mod*dppre[i-1][j-1]%Mod)%Mod;
	    }
	    dpsuf[K+1][0]=1;
	    for (int i=K;i>=1;i--){
		for (int j=0;j<=K-i+1;j++) dpsuf[i][j]=1ll*dpsuf[i+1][j]*Fm[P[i]][0]%Mod;
		for (int j=1;j<=K-i+1;j++) dpsuf[i][j]=(dpsuf[i][j]+1ll*(1-Fm[P[i]][0]+Mod)%Mod*dpsuf[i+1][j-1]%Mod)%Mod;
	    }

	    /*
	    for (int i=1;i<=K;i++){
		for (int j=0;j<=K;j++) cout<<dppre[i][j]<<" ";cout<<endl;
	    }cout<<endl;
	    for (int i=1;i<=K;i++){
		for (int j=0;j<=K;j++) cout<<dpsuf[i][j]<<" ";cout<<endl;
	    }cout<<endl;
	    //*/
	    
	    for (int i=1;i<=K;i++){
		int suv=(1-Fm[P[i]][0]+Mod)%Mod,Ans=0;
		for (int a=0;a<=K-1;a++){
		    int sum=0;
		    for (int b=0;b<=a&&b<i;b++)
			sum=(sum+1ll*dppre[i-1][b]*dpsuf[i+1][a-b]%Mod)%Mod;
		    Ans=(Ans+1ll*sum*Inv(a+1)%Mod)%Mod;
		}
		Ans=1ll*Ans*suv%Mod;
		printf("%d ",Ans);
	    }
	    for (int i=0;i<=K+1;i++) for (int j=0;j<=K;j++) dppre[i][j]=dpsuf[i][j]=0;
	    puts("");
	}
	/*
	cout<<"After:"<<Q<<endl;
	for (int i=1;i<=n;i++){
	    for (int j=0;j<=Mlim[i];j++) cout<<Fm[i][j]<<" ";cout<<endl;
	}
	//*/
    }
    for (int i=1;i<=n;i++){
	int sum=0;
	for (int j=0;j<=Mlim[i];j++) sum=(sum+1ll*j*Fm[i][j]%Mod)%Mod;
	printf("%d ",sum);
    }
    puts("");
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
