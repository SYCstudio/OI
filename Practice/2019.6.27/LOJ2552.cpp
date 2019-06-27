#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=210;
const int maxM=110;
const int Mod=998244353;
const int inf=2000000000;

int n,Q;
int Mlim[maxN],Fm[maxN][maxM],Gm[maxM];
int dp[maxN][maxN],dpg[maxN];
int Iv[maxN];

int QPow(int x,int cnt);
int main(){
    for (int i=1;i<maxN;i++) Iv[i]=Inv(i);
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
	    
	    dp[0][0]=1;int survive=0;
	    for (int i=1;i<=K;i++)
		if (Fm[P[i]][0]==0){
		    ++survive;
		    for (int j=0;j<=i;j++) dp[i][j]=dp[i-1][j];
		}
		else{
		    for (int j=0;j<=i;j++) dp[i][j]=1ll*dp[i-1][j]*Fm[P[i]][0]%Mod;
		    for (int j=1;j<=i;j++) dp[i][j]=(dp[i][j]+1ll*(1-Fm[P[i]][0]+Mod)%Mod*dp[i-1][j-1]%Mod)%Mod;
		}

	    /*
	    for (int i=1;i<=K;i++){
		for (int j=0;j<=K;j++) cout<<dp[i][j]<<" ";cout<<endl;
	    }cout<<endl;
	    //*/
	    
	    for (int i=1;i<=K;i++)
		if (Fm[P[i]][0]==0){
		    int Ans=0;
		    for (int j=0;j<=K;j++) Ans=(Ans+1ll*dp[K][j]*Iv[j+survive]%Mod)%Mod;
		    printf("%d ",Ans);
		}
		else{
		    int suv=(1-Fm[P[i]][0]+Mod)%Mod,Ans=0;
		    int inv1=Inv(Fm[P[i]][0]),mul2=(1-Fm[P[i]][0]+Mod)%Mod;
		    dpg[0]=1ll*dp[K][0]*inv1%Mod;
		    for (int j=1;j<=K;j++){
			int dpk=(dp[K][j]-1ll*dpg[j-1]*mul2%Mod+Mod)%Mod;
			dpg[j]=1ll*dpk*inv1%Mod;
		    }
		    //cout<<"Q:"<<Q<<" "<<i<<":";
		    //for (int j=0;j<K;j++) cout<<dpg[j]<<" ";cout<<endl;
		    for (int j=0;j<K;j++) Ans=(Ans+1ll*Iv[j+1+survive]*dpg[j]%Mod)%Mod;
		    Ans=1ll*Ans*suv%Mod;
		    printf("%d ",Ans);
		}
	    for (int i=0;i<=K+1;i++) for (int j=0;j<=K;j++) dp[i][j]=0;
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
