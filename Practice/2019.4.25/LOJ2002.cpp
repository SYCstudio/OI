#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxT=100;
const int maxP=20000100;
const int Mod=20170408;

int n,m,P;
int M1[maxT][maxT],M2[maxT][maxT],Bp[maxT][maxT];
int pcnt,Pri[maxP],notp[maxP],Cnt[maxP];

void Mul1();
void Mul2();
int main()
{
	scanf("%d%d%d",&n,&m,&P);
	for (int i=1; i<=m; i++) ++Cnt[i%P];
	M1[0][0]=1;
	for (int i=0; i<P; i++) for (int j=0; j<P; j++) M2[i][(i+j)%P]=Cnt[j];

	int N=n;
	while (N) {
		if (N&1) Mul1();
		Mul2();
		N>>=1;
	}
	int Ans=M1[0][0];
	memset(M1,0,sizeof(M1));
	memset(M2,0,sizeof(M2));
	notp[1]=1;
	for (int i=2; i<=m; i++) {
		if (!notp[i]) Pri[++pcnt]=i;
		for (int j=1; j<=pcnt&&1ll*i*Pri[j]<=m; j++) {
			notp[i*Pri[j]]=1;
			if (i%Pri[j]==0) break;
		}
	}
	M1[0][0]=1;
	for (int i=1; i<=pcnt; i++) --Cnt[Pri[i]%P];
	for (int i=0; i<P; i++) for (int j=0; j<P; j++) M2[i][(i+j)%P]=Cnt[j];

	N=n;
	while (N) {
		if (N&1) Mul1();
		Mul2();
		N>>=1;
	}

	Ans=(Ans-M1[0][0]+Mod)%Mod;
	printf("%d\n",Ans);
	return 0;
}
void Mul1()
{
	for (int i=0; i<P; i++) Bp[0][i]=M1[0][i],M1[0][i]=0;
	for (int i=0; i<1; i++) for (int j=0; j<P; j++) for (int k=0; k<P; k++) M1[i][j]=(M1[i][j]+1ll*Bp[i][k]*M2[k][j]%Mod)%Mod;
	return;
}
void Mul2()
{
	for (int i=0; i<P; i++) for (int j=0; j<P; j++) Bp[i][j]=M2[i][j],M2[i][j]=0;
	for (int i=0; i<P; i++) for (int j=0; j<P; j++) for (int k=0; k<P; k++) M2[i][j]=(M2[i][j]+1ll*Bp[i][k]*Bp[k][j]%Mod)%Mod;
	return;
}
