#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*15;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n;
int X[maxN],Y[maxN],Rader[maxN],Inv[maxN];
int I1[maxN],I2[maxN],L1[maxN],L2[maxN],E1[maxN],E2[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int len,int opt);
void PolyInv(int *A,int *B,int len);
void PolyDery(int *A,int *B,int len);
void PolyInte(int *A,int *B,int len);
void PolyLn(int *A,int *B,int len);
void PolyExp(int *A,int *B,int len);

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&X[i]);

	int N=1;while (N<n) N<<=1;
	Inv[0]=Inv[1]=1;for (int i=2;i<=N<<4;i++) Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;

	PolyExp(X,Y,N);

	for (int i=0;i<n;i++) printf("%d ",Y[i]);
	printf("\n");
	return 0;
}
/*
int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int len,int opt){
	int N,L=0;
	for (N=1;N<len;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int x=P[j+k],y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(x+y)%Mod;P[j+k+i]=(x-y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

void PolyInv(int *A,int *B,int len){
	if (len==1){B[0]=QPow(A[0],Mod-2);return;}
	PolyInv(A,B,len>>1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<(len<<1);i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=((B[i]+B[i])%Mod+Mod-I1[i])%Mod;
	for (int i=0;i<(len<<1);i++) I1[i]=I2[i]=0;
	return;
}

void PolyDery(int *A,int *B,int len){
	for (int i=0;i<len;i++) B[i]=1ll*A[i+1]*(i+1)%Mod;
	B[len]=B[len-1]=0;
	return;
}

void PolyInte(int *A,int *B,int len){
	for (int i=1;i<len;i++) B[i]=1ll*A[i-1]*Inv[i]%Mod;
	B[0]=0;return;
}

void PolyLn(int *A,int *B,int len){
	mem(L1,0);mem(L2,0);
	PolyDery(A,L1,len);
	PolyInv(A,L2,len);
	NTT(L1,len<<1,1);NTT(L2,len<<1,1);
	for (int i=0;i<(len<<1);i++) L1[i]=1ll*L1[i]*L2[i]%Mod;
	NTT(L1,len<<1,-1);
	PolyInte(L1,B,len);
	for (int i=0;i<(len<<1);i++) L1[i]=L2[i]=0;
	return;
}

void PolyExp(int *A,int *B,int len)
{
	if (len==1){B[0]=1;return;}
	PolyExp(A,B,len>>1);
	PolyLn(B,E1,len);
	for (int i=0;i<len;i++) E1[i]=((Mod-E1[i]+A[i])%Mod+Mod)%Mod,E2[i]=B[i];
	E1[0]=(E1[0]+1)%Mod;
	NTT(E1,len<<1,1);NTT(E2,len<<1,1);
	for (int i=0;i<(len<<1);i++) E1[i]=1ll*E1[i]*E2[i]%Mod;
	NTT(E1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=E1[i];
	for (int i=0;i<(len<<1);i++) E1[i]=E2[i]=0;
	return;
}
//*/

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int len,int opt)
{
	int N,L=0;
	for (N=1;N<len;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod)
			{
				int x=P[j+k],y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(x+y)%Mod;P[j+k+i]=(x-y+Mod)%Mod;
			}
	}
	if (opt==-1) for (int i=0;i<N;i++) P[i]=1ll*P[i]*Inv[N]%Mod;
	return;
}

void PolyInv(int *A,int *B,int len)
{
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<(len<<1);i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=((B[i]+B[i])%Mod+Mod-I1[i])%Mod;
	for (int i=0;i<(len<<1);i++) I1[i]=I2[i]=0;
	return;
}

void PolyDery(int *A,int *B,int len)
{
	for (int i=0;i<len;i++) B[i]=1ll*A[i+1]*(i+1)%Mod;
	B[len]=B[len-1]=0;
	return;
}

void PolyInte(int *A,int *B,int len)
{
	for (int i=1;i<len;i++) B[i]=1ll*A[i-1]*Inv[i]%Mod;
	B[0]=0;return;
}

void PolyLn(int *A,int *B,int len)
{
	PolyDery(A,L1,len);
	PolyInv(A,L2,len);
	NTT(L1,len<<1,1);NTT(L2,len<<1,1);
	for (int i=0;i<(len<<1);i++) L1[i]=1ll*L1[i]*L2[i]%Mod;
	NTT(L1,len<<1,-1);
	PolyInte(L1,B,len);
	for (int i=0;i<(len<<1);i++) L1[i]=L2[i]=0;
	return;
}

void PolyExp(int *A,int *B,int len)
{
	if (len==1){
		B[0]=1;return;
	}
	PolyExp(A,B,len>>1);
	PolyLn(B,E1,len);
	for (int i=0;i<len;i++) E1[i]=(Mod-E1[i]+A[i])%Mod,E2[i]=B[i];
	E1[0]=(E1[0]+1)%Mod;
	NTT(E1,len<<1,1);NTT(E2,len<<1,1);
	for (int i=0;i<(len<<1);i++) E1[i]=1ll*E1[i]*E2[i]%Mod;
	NTT(E1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=E1[i];
	for (int i=0;i<(len<<1);i++) E1[i]=E2[i]=0;
	return;
}
//*/
