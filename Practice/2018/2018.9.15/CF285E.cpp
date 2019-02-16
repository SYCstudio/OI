#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m;
int F[maxN][maxN][2][2];
int G[maxN],Fac[maxN];
int C[maxN][maxN],Ans[maxN];

void Plus(int &x,int y);

int main(){
	scanf("%d%d",&n,&m);
	F[0][0][1][0]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<=i;j++)
			for (int k=0;k<=1;k++)
				for (int l=0;l<=1;l++){
					int key=F[i][j][k][l];
					Plus(F[i+1][j][l][0],key);
					if (k==0) Plus(F[i+1][j+1][l][0],key);
					if (i+1!=n) Plus(F[i+1][j+1][l][1],key);
				}
	Fac[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;

	for (int i=0;i<=n;i++){
		for (int k=0;k<=1;k++)
			for (int l=0;l<=1;l++)
				Plus(G[i],F[n][i][k][l]);
		G[i]=1ll*G[i]*Fac[n-i]%Mod;
	}

	//for (int i=0;i<=n;i++) cout<<G[i]<<" ";cout<<endl;

	for (int i=0;i<=n;i++){
		C[i][0]=1;
		for (int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}

	Ans[n]=G[n];
	for (int i=n-1;i>=m;i--){
		Ans[i]=G[i];
		for (int j=i+1;j<=n;j++)
			Ans[i]=(Ans[i]-1ll*C[j][i]*Ans[j]%Mod+Mod)%Mod;
	}

	printf("%d\n",Ans[m]);

	return 0;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}
