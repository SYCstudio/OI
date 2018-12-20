#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000*10;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m,T;
int Fc[maxN],Ifc[maxN];
int a[maxN],b[maxN],R[maxN];
int I1[maxN],I2[maxN],L1[maxN],L2[maxN],Dv[18][maxN];
int A[maxN],B[maxN];

void QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int len);
void PolyInte(int *A,int *B,int len);
void PolyDery(int *A,int *B,int len);
void PolyLn(int *A,int *B,int len);
void GetPosSum(int *A,int *B,int len,int top);
void Divide(int *A,int d,int l,int r);

int main(){
	Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fc[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*IFc[i+1]*(i+1)%Mod;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) scanf("%d",&b[i]);
	scanf("%d",&T);
	GetPowSum(a,A,n,T);GetPowSum(b,B,m,T);
	for (int i=0;i<=T;i++) A[i]=1ll*A[i]*Ifc[i]%Mod,B[i]=1ll*B[i]*Ifc[i]%Mod;
	int N=1;while (N<=T+T) N<<=1;
	NTT(A,N,1);NTT(B,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);
	for (int i=1;i<=T;i++) printf("%lld\n",1ll*A[i]*Fac[i]%Mod);
	return 0;
}

void QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int N,int opt){
	int L=0,l=1;while (l<N) ++L,l<<=1;for (int i=0;i<N;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) if (i<R[i]) swap(P[i],P[R[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
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

void PolyInte(int *A,int *B,int len){
	for (int i=0;i<len;i++) B[i+1]=1ll*A[i]*QPow(i,Mod-2)%Mod;
	B[0]=B[len]=0;return;
}

void PolyDery(int *A,int *B,int len){
	for (int i=1;i<len;i++) B[i-1]=1ll*i*A[i]%Mod;
	return;
}

void GetPosSum(int *A,int *B,int len,int top){
	
}

void Divide(int *A,int d,int l,int r);
