#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=5050000;
const int Mod=998244353;

int Fc[maxN],Ifc[maxN];
int n,m,L,K;
int A[maxN],B[maxN],F[maxN];
int MulA[maxN],Inva[maxN];

int QPow(int x,int cnt);
int Binom(int n,int m);
int main()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d%d%d%d",&n,&m,&L,&K);
		int mn=min(min(n,m),L),N=1ll*n*m%Mod*L%Mod;
		for (int i=1; i<=mn; i++) A[i]=(N-1ll*(n-i)%Mod*(m-i)%Mod*(L-i)%Mod+Mod)%Mod;
		for (int i=1; i<=mn; i++) B[i]=1ll*Ifc[i]*Fc[n]%Mod*Ifc[n-i]%Mod*Fc[m]%Mod*Ifc[m-i]%Mod*Fc[L]%Mod*Ifc[L-i]%Mod;
		MulA[0]=1;
		for (int i=1; i<=mn; i++) MulA[i]=1ll*MulA[i-1]*A[i]%Mod;
		Inva[mn]=Inv(MulA[mn]);
		for (int i=mn-1; i>=1; i--) Inva[i]=1ll*Inva[i+1]*A[i+1]%Mod;

		for (int i=1; i<=mn; i++) F[i]=1ll*Fc[i]*B[i]%Mod*Inva[i]%Mod;

		int Ans=0;
		for (int i=K; i<=mn; i++) {
			int mul=1ll*Binom(i,K)*F[i]%Mod;
			if ((i-K)&1) Ans=(Ans-mul+Mod)%Mod;
			else Ans=(Ans+mul)%Mod;
		}
		printf("%d\n",Ans);
	}
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
