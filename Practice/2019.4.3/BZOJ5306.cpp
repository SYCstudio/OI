#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=10100000;
const int maxM=101000<<2;
const int Mod=1004535809;
const int G=3;

int Fc[maxN],Ifc[maxN];
int A[maxM],B[maxM];
int Rader[maxM];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
int main()
{
	int n,m,S;
	scanf("%d%d%d",&n,&m,&S);
	int X=min(m,n/S);
	int mx=max(n,m);

	Fc[0]=Ifc[0]=1;
	for (int i=1; i<=mx; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[mx]=QPow(Fc[mx],Mod-2);
	for (int i=mx-1; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	for (int i=0; i<=X; i++) A[i]=1ll*Fc[m]*Ifc[m-i]%Mod*Fc[n]%Mod*QPow(QPow(Fc[S],i),Mod-2)%Mod*QPow(Fc[n-i*S],Mod-2)%Mod*QPow(m-i,n-i*S)%Mod;
	for (int i=0; i<=X; i++) if (i&1) B[i]=Mod-Ifc[i];
		else B[i]=Ifc[i];

	reverse(&B[0],&B[X+1]);
	int len=1;
	while (len<=X+X) len<<=1;

	NTT(A,len,1);
	NTT(B,len,1);
	for (int i=0; i<len; i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,len,-1);
	int Ans=0;
	for (int i=X; i<=X+X; i++) {
		int w;
		scanf("%d",&w);
		Ans=(Ans+1ll*w*A[i]%Mod*Ifc[i-X]%Mod)%Mod;
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
void NTT(int *P,int N,int opt)
{
	int _N=N,l=-1;
	while (_N) ++l,_N>>=1;
	for (int i=0; i<N; i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(l-1));
	for (int i=0; i<N; i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0; j<N; j+=(i<<1))
			for (int k=j,w=1; k<i+j; k++,w=1ll*w*dw%Mod) {
				int X=P[k],Y=1ll*w*P[k+i]%Mod;
				P[k]=X+Y;
				if (P[k]>=Mod) P[k]-=Mod;
				P[k+i]=X-Y;
				if (P[k+i]<0) P[k+i]+=Mod;
			}
	}
	if (opt==-1) {
		int inv=QPow(N,Mod-2);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}