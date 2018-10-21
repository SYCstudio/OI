#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxK=110;
const int maxBit=16;
const int Mod=1e9+7;
const int inf=2147483647;

int n,K,D;
int C[maxN][maxK];
int F[maxBit][maxN];

void Init();
int GetC(int n,int m);
void Plus(int &x,int y);

int main(){
	Init();
	scanf("%d%d%d",&n,&K,&D);

	F[0][0]=1;
	for (int i=0;i<maxBit-1;i++){
		int nowd=1<<i;
		for (int j=0;j<=n-K;j++)
			for (int k=0;(k*nowd+j<=n-K)&&(k<=K/2);k+=D+1)
				Plus(F[i+1][j+k*nowd],1ll*F[i][j]*GetC(K/2,k)%Mod);
	}

	/*
	for (int i=0;i<maxBit;i++){
		for (int j=0;j<=n;j++)
			cout<<F[i][j]<<" ";
		cout<<endl;
	}
	//*/

	int Ans=0;
	for (int i=0;i<=n-K;i++)
		Plus(Ans,1ll*F[maxBit-1][i]*GetC(n-i-K/2,K/2)%Mod);
	//cout<<Ans<<endl;
	Ans=(GetC(n,K)-Ans+Mod)%Mod;
	printf("%d\n",Ans);return 0;
}

void Init(){
	for (int i=0;i<maxN;i++){
		C[i][0]=1;
		for (int j=1;j<=min(i,maxK-1);j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}
	return;
}

int GetC(int n,int m){
	if (m>n-m) m=n-m;
	//cout<<"GetC:"<<n<<","<<m<<":"<<C[n][m]<<endl;
	return C[n][m];
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}
