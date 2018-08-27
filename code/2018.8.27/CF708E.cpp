#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=1501;
const int maxNum=10000010;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,K;
int Fac[maxNum],Inv[maxNum];
int P[maxN],SP[maxN];
int F[maxN][maxN],G[maxN][maxN],S1[maxN][maxN],S2[maxN][maxN];

int QPow(int x,int cnt);
int GetC(int n,int m);
IL void Plus(RG int &x,RG int y);

int main(){
	RG int i,j,l,r;
	scanf("%d%d",&n,&m);
	int a,b;scanf("%d%d",&a,&b);scanf("%d",&K);
	int p=1ll*a*QPow(b,Mod-2)%Mod,np=(1-p+Mod)%Mod;
	Fac[0]=Inv[0]=1;for (i=1;i<maxNum;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxNum-1]=QPow(Fac[maxNum-1],Mod-2);for (i=maxNum-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;

	for (i=0;i<=min(m,K);i++) P[i]=1ll*QPow(p,i)*QPow(np,K-i)%Mod*GetC(K,i)%Mod;
	SP[0]=P[0];for (i=1;i<maxN;i++) SP[i]=(SP[i-1]+P[i])%Mod;

	//for (int i=0;i<=K;i++) cout<<P[i]<<" "<<SP[i]<<endl;

	for (l=1;l<=m;l++)
		for (r=l;r<=m;r++){
			Plus(F[1][r],1ll*P[l-1]*P[m-r]%Mod);Plus(G[1][l],1ll*P[l-1]*P[m-r]%Mod);
		}
	for (i=1;i<=m;i++) Plus(F[1][i],F[1][i-1]),Plus(S1[1][i],1ll*F[1][i]*P[i]%Mod);
	for (i=m;i>=1;i--) Plus(G[1][i],G[1][i+1]),Plus(S2[1][i],1ll*G[1][i]*P[m-i+1]%Mod);
	for (i=1;i<=m;i++) Plus(S1[1][i],S1[1][i-1]);
	for (i=m;i>=1;i--) Plus(S2[1][i],S2[1][i+1]);
	//for (int i=1;i<=m;i++) cout<<F[1][i]<<" ";cout<<endl;
	//for (int i=1;i<=m;i++) cout<<G[1][i]<<" ";cout<<endl;

	for (i=2;i<=n;i++){
		//cout<<i<<endl;
		RG int sum=F[i-1][m];
		for (j=1;j<=m;j++){
			Plus(F[i][j],1ll*(1ll*(sum-G[i-1][j+1])*SP[j-1]%Mod-S1[i-1][j-1])%Mod*P[m-j]%Mod);
			Plus(G[i][j],1ll*(1ll*(sum-F[i-1][j-1])*SP[m-j]%Mod-S2[i-1][j+1])%Mod*P[j-1]%Mod);
			
		}
		for (j=1;j<=m;j++) Plus(F[i][j],F[i][j-1]),Plus(S1[i][j],1ll*F[i][j]*P[j]%Mod);
		for (j=m;j>=1;j--) Plus(G[i][j],G[i][j+1]),Plus(S2[i][j],1ll*G[i][j]*P[m-j+1]%Mod);
		for (j=1;j<=m;j++) Plus(S1[i][j],S1[i][j-1]);
		for (j=m;j>=1;j--) Plus(S2[i][j],S2[i][j+1]);
	}

	printf("%d\n",F[n][m]);

	return 0;
}

int QPow(RG int x,RG int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int GetC(RG int n,RG int m){
	if (n<m) return 0;
	//cout<<"GetC:"<<n<<" "<<m<<":"<<1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod<<endl;
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}

IL void Plus(RG int &x,RG int y){
	x=((x+y)%Mod+Mod)%Mod;return;
}

