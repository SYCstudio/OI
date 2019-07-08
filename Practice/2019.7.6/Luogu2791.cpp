#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int Mod=998244353;
const int maxN=20200000;
const int maxB=202000*8;

int n,m,S,L,K;
int Fc[maxN],Ifc[maxN];
int A[maxB],B[maxB],Stl[maxB],Ra[maxB];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
int Binom(int n,int m);
int main()
{
	//freopen("input","r",stdin);
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%d%d%d",&n,&m,&S,&L);

	for (int i=0; i<=L; i++) {
		A[i]=Ifc[i];
		B[i]=1ll*QPow(i,L)*Ifc[i]%Mod;
		if (i&1) A[i]=(Mod-A[i]+Mod)%Mod;
	}

	int len=1;
	while (len<=L+L) len<<=1;
	NTT(A,len,1);
	NTT(B,len,1);
	for (int i=0; i<len; i++) Stl[i]=1ll*A[i]*B[i]%Mod;
	NTT(Stl,len,-1);

	for (int i=L+1; i<len; i++) Stl[i]=0;
	//for (int i=1;i<=L;i++) cout<<Stl[i]<<" ";cout<<endl;

	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));

	while (S--) {
		scanf("%d%d%d",&n,&m,&K);
		int up=min(K,L),Ans=0;
		up=min(up,min(n,m));
		for (int i=1; i<=up; i++)
			Ans=(Ans+1ll*Stl[i]*Fc[n-i]%Mod*Ifc[m-i]%Mod*Ifc[K-i]%Mod)%Mod;
		Ans=1ll*Ans*Fc[m]%Mod*Ifc[n-K]%Mod;
		Ans=1ll*Ans*Inv(Binom(n,K))%Mod;
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
void NTT(int *P,int N,int opt)
{
	int _N=1,l=-1;
	while (_N<N) _N<<=1,++l;
	for (int i=0; i<N; i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
	for (int i=0; i<N; i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(3,(Mod-1)/(i<<1));
		if (opt==-1) dw=Inv(dw);
		for (int j=0; j<N; j+=i+i)
			for (int k=0,w=1; k<i; k++,w=1ll*w*dw%Mod) {
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;
				P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1) {
		int inv=Inv(N);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
int Binom(int n,int m)
{
	if (n<0||m<0||n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
