#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Mod=20130427;
const int inf=2147483647;

int B;
int L[maxN],R[maxN],Two[maxN];
int Cnt[2][maxN],Tot[2][maxN],Suf[2][maxN],Sum[2][maxN];

int Calc(int len,int *M);

int main(){
	for (int i=2;i<maxN;i++) Two[i]=(Two[i-1]+i-1)%Mod;
	int n,m;
	scanf("%d",&B);
	scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&L[i]);
	scanf("%d",&m);for (int i=1;i<=m;i++) scanf("%d",&R[i]);

	int Ans=0,sum=0;
	for (int i=1;i<=n;i++){
		sum=(1ll*sum*B%Mod+1ll*L[i]*i%Mod)%Mod;
		Ans=(Ans+sum)%Mod;
	}
	//cout<<sum<<endl;

	printf("%d\n",((Ans+Calc(m,R)-Calc(n,L))%Mod+Mod)%Mod);
}

int Calc(int len,int *M){
	mem(Cnt,0);mem(Tot,0);mem(Suf,0);mem(Sum,0);
	Cnt[0][0]=1;
	for (int i=1;i<=len;i++){
		int opt=(i==1)?(0):(B);
		//cout<<i<<" "<<opt<<endl;
		Cnt[0][i]=Cnt[0][i-1];
		Cnt[1][i]=(1ll*Cnt[1][i-1]*B%Mod+1ll*Cnt[0][i-1]*M[i]%Mod+(opt-1))%Mod;
		Tot[0][i]=(Tot[0][i-1]+Cnt[0][i-1])%Mod;
		Tot[1][i]=(opt-1+1ll*(Tot[0][i-1]+Cnt[0][i-1])%Mod*M[i]%Mod+1ll*(Tot[1][i-1]+Cnt[1][i-1])%Mod*B%Mod)%Mod;
		Suf[0][i]=(1ll*Suf[0][i-1]*B%Mod+1ll*Tot[0][i]*M[i]%Mod)%Mod;
		Suf[1][i]=((1ll*Suf[0][i-1]*B%Mod*M[i]%Mod+1ll*Tot[0][i]*Two[M[i]]%Mod)%Mod+(1ll*Suf[1][i-1]*B%Mod*B%Mod+1ll*(Cnt[1][i-1]+Tot[1][i-1])%Mod*Two[B]%Mod)%Mod+Two[opt])%Mod;
		Sum[0][i]=(Sum[0][i-1]+Suf[0][i])%Mod;
		Sum[1][i]=(1ll*Sum[0][i-1]*M[i]%Mod+1ll*Sum[1][i-1]*B%Mod+Suf[1][i])%Mod;
	}
	//for (int i=1;i<=len;i++) cout<<Cnt[0][i]<<" "<<Cnt[1][i]<<" "<<Tot[0][i]<<" "<<Tot[1][i]<<" "<<Suf[0][i]<<" "<<Suf[1][i]<<" "<<Sum[0][i]<<" "<<Sum[1][i]<<endl;
	//cout<<Sum[0][len]+Sum[1][len]<<endl;
	return (Sum[0][len]+Sum[1][len])%Mod;
}
