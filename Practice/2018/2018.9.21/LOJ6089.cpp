#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxSN=320;
const int Mod=23333333;
const int inf=2147483647;

int n,m;
int F[2][maxN],SF[2][maxN],G[2][maxN],I[maxN];

int main(){
	scanf("%d",&n);m=sqrt(n);//cout<<"m:"<<m<<endl;
	F[0][0]=SF[0][0]=1;for (int i=1;i<=n;i++) SF[0][i]=1;
	for (int i=1;i<=m;i++){
		int now=i&1;
		F[now][0]=SF[now][0]=1;
		for (int j=1;j<=n;j++){
			//cout<<"("<<i<<","<<j<<") <- ("<<i-1<<","<<max(0,j-i*(i+1))<<")"<<endl;
			if (j-i*(i+1)<0) F[now][j]=SF[now^1][j];
			else F[now][j]=(SF[now^1][j]-SF[now^1][max(0,j-i*(i+1))]+Mod)%Mod;
			if (j-(i+1)<0) SF[now][j]=F[now][j];
			else SF[now][j]=(SF[now][j-(i+1)]+F[now][j])%Mod;
		}
	}
	/*
	for (int i=m;i<=m;i++){
		for (int j=1;j<=n;j++) cout<<F[i&1][j]<<" ";cout<<endl;
		for (int j=1;j<=n;j++) cout<<SF[i&1][j]<<" ";cout<<endl<<endl;
	}
	//*/

	G[0][0]=I[0]=1;
	for (int i=1;i<=m;i++){
		int now=i&1;
		mem(G[now],0);
		for (int j=0;j<=n;j++){
			if (j-m-1>=0) G[now][j]=(G[now][j]+G[now^1][j-m-1])%Mod;
			if (j-i>=0) G[now][j]=(G[now][j]+G[now][j-i])%Mod;
			I[j]=(I[j]+G[now][j])%Mod;
		}

		//for (int j=1;j<=n;j++) cout<<G[now][j]<<" ";cout<<endl;
	}

	int Ans=0;
	for (int i=0;i<=n;i++) Ans=(Ans+1ll*F[m&1][i]*I[n-i]%Mod)%Mod;

	printf("%d\n",Ans);return 0;
}
