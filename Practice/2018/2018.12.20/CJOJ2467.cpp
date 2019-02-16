#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000*10;
const int Mod=998244353;
const int G=3;
const int sqrt2=116195171;
const int inf=2147483647;

int n;
int Fac[maxN],Inv[maxN],Rader[maxN];
int A[maxN],IA[maxN],I1[maxN],I2[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int len,int opt);
void PolyInv(int *A,int *B,int len);

int main(){
	Fac[0]=Inv[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) A[i]=(1ll*((i&1)?(-1):(1))*Inv[i]%Mod*QPow(QPow(sqrt2,1ll*i*i%(Mod-1)),Mod-2)%Mod+Mod)%Mod;
	A[0]=1;int N=1;while (N<=n) N<<=1;
	PolyInv(A,IA,N);
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<IA[i]<<" ";cout<<endl;
	printf("%lld\n",1ll*IA[n]*Fac[n]%Mod*QPow(sqrt2,1ll*n*n%(Mod-1))%Mod);
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int len,int opt){
	int L=0,l;for (l=1;l<len;l<<=1) ++L;for (int i=0;i<len;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<len;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<len;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<len;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(len,Mod-2);
		for (int i=0;i<len;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

void PolyInv(int *A,int *B,int len){
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<len<<1;i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=(2ll*B[i]%Mod-I1[i]+Mod)%Mod;
	for (int i=0;i<len<<1;i++) I1[i]=I2[i]=0;
	return;
}
