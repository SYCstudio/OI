#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=410;
const int Mod=998244353;
const int inf=2147483647;

int n,K;
int W[maxN],F[maxN][maxN],Pw[maxN];

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&W[i]);
	for (int i=0;i<=n;i++) F[i][0]=1;
	for (int i=1;i<=n;i++){
		Pw[0]=1;for (int j=1;j<=n;j++) Pw[j]=1ll*Pw[j-1]*W[i]%Mod;
		for (int j=1;j<=n;j++){
			F[i][j]=F[i-1][j];
			for (int p=1;p<=j;p++)
				F[i][j]=(F[i][j]+1ll*F[i-1][p-1]*Pw[max(0,min(p,j-K+1)-max(1,p-K+1)+1)]%Mod*F[i][j-p]%Mod)%Mod;
		}
	}
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) cout<<F[i][j]<<" ";
		cout<<endl;
	}
	//*/
	printf("%d\n",F[n][n]);
	return 0;
}
