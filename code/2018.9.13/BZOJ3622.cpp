#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2020;
const int Mod=1e9+9;
const int inf=2147483647;

int n,K;
int X[maxN],Y[maxN];
int F[maxN][maxN];

int main(){
	scanf("%d%d",&n,&K);
	if (((n+K)%2!=0)||((n+K)/2>n)){
		printf("0\n");return 0;
	}

	K=(n+K)/2;
	for (int i=1;i<=n;i++) scanf("%d",&X[i]);
	for (int i=1;i<=n;i++) scanf("%d",&Y[i]);
	sort(&X[1],&X[n+1]);sort(&Y[1],&Y[n+1]);

	F[0][0]=1;
	for (int i=1;i<=n;i++)
		if (X[i]>Y[i]){
			int t=0;
			for (int j=i;j>=1;j--) if (X[j]>Y[i]) t++;
			for (int j=1;j<=i;j++){
				if (j>=1) F[i][j]=(F[i][j]+1ll*F[i-1][j-1]*t%Mod)%Mod;
				if (j>=1) F[i][j]=(F[i][j]+1ll*F[i-1][j-1]*(i-j)%Mod)%Mod;
				if (j-(t-1)>=0) F[i][j]=(F[i][j]+1ll*F[i-1][j]*(j-(t-1))%Mod)%Mod;
			}
		}
		else{
			int t=0;
			for (int j=i;j>=1;j--) if (Y[j]>=X[i]) t++;
			for (int j=0;j<=i;j++){
				F[i][j]=(F[i][j]+1ll*F[i-1][j]*t%Mod)%Mod;
				F[i][j]=(F[i][j]+1ll*F[i-1][j]*j%Mod)%Mod;
				if (j>=1) F[i][j]=(F[i][j]+1ll*F[i-1][j-1]*(i-(j-1)-t)%Mod)%Mod;
			}
		}

	printf("%d\n",F[n][K]);

	return 0;
}
