#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const int Mod=30011;
const int inf=2147483647;

int n,m,N;
int Ans[maxN*3],Mt[maxN*3][maxN*3],Bp[maxN*3][maxN*3];

void Mul1();
void Mul2();

int main(){
	scanf("%d%d",&n,&m);N=n+n+n;
	Ans[0]=1;Ans[n+n]=1;
	for (int i=0;i<n;i++) Mt[i+n][i]=1;
	for (int i=n;i<n+n;i++){
		Mt[i+n][i]=1;
		for (int j=max(0,i-n-1);j<=min(n-1,i-n+1);j++) Mt[j][i]=1;
	}
	for (int i=n+n;i<n+n+n;i++) Mt[i-n][i]=1;
	/*
	for (int i=0;i<n+n+n;i++){
		for (int j=0;j<n+n+n;j++)
			cout<<Mt[i][j]<<" ";
		cout<<endl;
	}
	//*/

	while (m--){
		Mul1();
		for (int i=0;i<N;i++) cout<<Ans[i]<<" ";cout<<endl;
	}
	/*
	while (m){
		if (m&1) Mul1();
		Mul2();m>>=1;
	}
	//*/

	printf("%d\n",Ans[n-1]);return 0;
}

void Mul1(){
	for (int i=0;i<N;i++) Bp[0][i]=Ans[i],Ans[i]=0;
	for (int j=0;j<N;j++)
		for (int k=0;k<N;k++)
			Ans[j]=Ans[j]+Bp[0][k]*Mt[k][j];
	for (int i=0;i<N;i++) Ans[i]%=Mod;
	return;
}

void Mul2(){
	for (int i=0;i<N;i++) for (int j=0;j<N;j++) Bp[i][j]=Mt[i][j],Mt[i][j]=0;
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			for (int k=0;k<N;k++)
				Mt[i][j]=Mt[i][j]+Bp[i][k]*Bp[k][j];
	for (int i=0;i<N;i++) for (int j=0;j<N;j++) Mt[i][j]%=Mod;
	return;
}
