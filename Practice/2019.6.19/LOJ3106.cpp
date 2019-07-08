#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=1110;
const int Mod=998244353;

int n,A,B,C,D;
int Fc[maxN],Ifc[maxN],Mic[maxN];
int Pa[maxN],Pb[maxN],Pc[maxN],Pd[maxN];
int M1[maxN],M2[maxN];

int QPow(int x,int cnt);
int Binom(int n,int m);
int main()
{
	Fc[0]=Ifc[0]=Mic[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%d%d%d%d",&n,&A,&B,&C,&D);
	int up=min(min(n/4,min(A,B)),min(C,D));

	for (int i=0; i<=A; i++) Pa[i]=Ifc[i];
	for (int i=0; i<=B; i++) Pb[i]=Ifc[i];
	for (int i=0; i<=C; i++) Pc[i]=Ifc[i];
	for (int i=0; i<=D; i++) Pd[i]=Ifc[i];
	for (int i=0; i<=A; i++) for (int j=0; j<=B; j++) M1[i+j]=(M1[i+j]+1ll*Pa[i]*Pb[j]%Mod)%Mod;
	for (int i=0; i<=C; i++) for (int j=0; j<=D; j++) M2[i+j]=(M2[i+j]+1ll*Pc[i]*Pd[j]%Mod)%Mod;

	int Ans=0;
	for (int i=0; i<=up; i++) {
		int f=0;
		for (int j=0; j<=n-i*4; j++) f=(f+1ll*M1[j]*M2[n-i*4-j]%Mod)%Mod;
		f=1ll*f*Fc[n-i*4]%Mod*Binom(n-3*i,i)%Mod;
		if (i&1) Ans=(Ans-f+Mod)%Mod;
		else Ans=(Ans+f)%Mod;
		for (int j=0; j<=B; j++) M1[j+A]=(M1[j+A]-1ll*Pa[A]*Pb[j]%Mod+Mod)%Mod;
		--A;
		for (int j=0; j<=A; j++) M1[j+B]=(M1[j+B]-1ll*Pa[j]*Pb[B]%Mod+Mod)%Mod;
		--B;
		for (int j=0; j<=D; j++) M2[j+C]=(M2[j+C]-1ll*Pc[C]*Pd[j]%Mod+Mod)%Mod;
		--C;
		for (int j=0; j<=C; j++) M2[j+D]=(M2[j+D]-1ll*Pc[j]*Pd[D]%Mod+Mod)%Mod;
		--D;
	}

	printf("%d\n",Ans);
	return 0;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
int Binom(int n,int m)
{
	if (n<0||m<0||n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
