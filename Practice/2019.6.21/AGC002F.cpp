#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2);

const int maxN=2005;
const int maxM=maxN*maxN;
const int Mod=1e9+7;

int n,K;
int Fc[maxM],Ifc[maxM];
int F[maxN][maxN];

int QPow(int x,int cnt);
int C(int n,int m);
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxM;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxM-1]=Inv(Fc[maxM-1]);for (int i=maxM-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
    
    scanf("%d%d",&n,&K);
    if (K==1){
	puts("1");return 0;
    }

    F[0][0]=1;
    for (int i=1;i<=n;i++)
	for (int j=n;j>=0;j--){
	    if (j<=i&&j>=0) F[i][j]=1ll*F[i-1][j-1]*C(i*K-j-1,K-2)%Mod;
	    F[i][j]=(F[i][j]+F[i][j+1])%Mod;
	}
    /*
    for (int i=0;i<=n;i++){
	for (int j=0;j<=n;j++) cout<<F[i][j]<<" ";
	cout<<endl;
    }//*/
    int Ans=1ll*F[n][0]*Fc[n]%Mod;
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
int C(int n,int m){
    if (n<0||m<0||n<m) return 0;
    return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
