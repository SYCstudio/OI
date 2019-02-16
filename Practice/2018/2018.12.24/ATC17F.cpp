#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=320;
const int Mod=1e9+7;
const int inf=2147483647;

int n,D[maxN];
int F[maxN][maxN][2];
int Fac[maxN],Ifc[maxN];

int QPow(int x,int cnt);

int main(){
	Fac[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	bool fullring=1;
	scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&D[i]),fullring&=(D[i]==2);
	if (fullring){
		printf("%lld\n",1ll*Fac[n-1]*Ifc[2]%Mod);return 0;
	}
	F[0][0][0]=1;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=i;j++)
			for (int k=0;k<=1;k++){
				F[i][j][k]=F[i-1][j][k];
				if ((D[i]>=2)&&(j>0)) F[i][j][k]=(1ll*F[i-1][j-1][k]*(D[i]-1)%Mod+F[i][j][k])%Mod;
				if ((D[i]>=3)&&(j>0)&&(k==1)) F[i][j][k]=(1ll*F[i-1][j-1][0]*(D[i]-1)%Mod*(D[i]-2)%Mod+F[i][j][k])%Mod;
			}
	int Ans=0;
	//for (int i=1;i<=n;i++) cout<<F[n][i][1]<<" ";cout<<endl;
	for (int i=3;i<=n;i++) Ans=(Ans+1ll*F[n][i][1]*Fac[i-1]%Mod*Ifc[2]%Mod*Fac[n-i-1]%Mod)%Mod;
	for (int i=1;i<=n;i++) Ans=1ll*Ans*Ifc[D[i]-1]%Mod;
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
