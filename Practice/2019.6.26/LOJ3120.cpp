#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=101000*8;
const int Mod=998244353;
const int g=3;

int Fc[maxN],Ifc[maxN],Ra[maxN];
int n,m,D;
int F[maxN],G[maxN];

int QPow(int x,int cnt);
int Binom(int n,int m);
void NTT(int *P,int N,int opt);
int main()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%d%d",&D,&n,&m);
	if (n<m+m) {
		puts("0");
		return 0;
	} else if (D<=n-m-m) {
		printf("%d\n",QPow(D,n));
		return 0;
	}

	for (int i=0; i<=D; i++) {
		F[i]=1ll*QPow((D-i-i+Mod)%Mod,n)*Ifc[i]%Mod;
		G[i]=Ifc[i];
		if (i&1) F[i]=(Mod-F[i])%Mod;
	}

	int N=1;
	while (N<=D+D) N<<=1;
	NTT(F,N,1);
	NTT(G,N,1);
	for (int i=0; i<N; i++) F[i]=1ll*F[i]*G[i]%Mod;
	NTT(F,N,-1);
	memset(G,0,sizeof(G));
	for (int i=0; i<=D; i++) F[i]=1ll*F[i]*Inv(1ll*QPow(2,i)*Fc[D-i]%Mod*Ifc[D]%Mod)%Mod;

	for (int i=D+1; i<N; i++) F[i]=0;
	for (int i=0; i<=D; i++) {
		F[i]=1ll*F[i]*Fc[i]%Mod;
		G[i]=Ifc[i];
		if (i&1) G[i]=(Mod-G[i])%Mod;
	}
	reverse(&G[0],&G[D+1]);
	NTT(F,N,1);
	NTT(G,N,1);
	for (int i=0; i<N; i++) F[i]=1ll*F[i]*G[i]%Mod;
	NTT(F,N,-1);
	for (int i=0; i<=D; i++) F[i]=1ll*F[D+i]*Ifc[i]%Mod;

	int Ans=0;
	for (int i=0; i<=n-m-m; i++) Ans=(Ans+F[i])%Mod;
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
void NTT(int *P,int N,int opt)
{
	int _N=1,l=-1;
	while (_N<N) ++l,_N<<=1;
	for (int i=0; i<N; i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
	for (int i=0; i<N; i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(g,(Mod-1)/(i<<1));
		if (opt==-1) dw=Inv(dw);
		for (int j=0; j<N; j+=(i<<1))
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
