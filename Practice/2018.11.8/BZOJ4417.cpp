#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=51;
const int maxM=155;
const int Mod=30011;
const int inf=2147473647;

int n,m,N;
int Mt[maxM][maxM];
int Ans[maxM],Bp[maxM][maxM];

void Mul1();
void Mul2();

int main(){
	scanf("%d%d",&n,&m);m--;N=n+n+n;
	Ans[0]=1;
	for (int i=0;i<n;i++){
		for (int j=max(0,i-1);j<=min(n-1,i+1);j++) Mt[j][i]=1;
		Mt[i+n+n][i]=1;
	}
	for (int i=0;i<n;i++){
		for (int j=max(0,i-1);j<=min(n-1,i+1);j++) Mt[j][i+n]=1;
		Mt[i+n+n][i+n]=1;
	}
	for (int i=0;i<n;i++) Mt[i+n][i+n+n]=1;
	while (m){
		if (m&1) Mul1();
		Mul2();m>>=1;
	}
	printf("%d\n",Ans[n-1]);return 0;
}

void Mul1(){
	RG int i,j,k;
	for (i=0;i<N;++i) Bp[0][i]=Ans[i],Ans[i]=0;
	for (j=0;j<N;++j)
		for (k=0;k<N;++k)
			Ans[j]=(Ans[j]+1ll*Bp[0][k]*Mt[k][j]%Mod)%Mod;
	return;
}

void Mul2(){
	RG int i,j,k;
	for (i=0;i<N;++i) for (j=0;j<N;++j) Bp[i][j]=Mt[i][j],Mt[i][j]=0;
	for (i=0;i<N;++i)
		for (j=0;j<N;++j)
			for (k=0;k<N;++k)
				Mt[i][j]=(Mt[i][j]+1ll*Bp[i][k]*Bp[k][j]%Mod)%Mod;
	return;
}
