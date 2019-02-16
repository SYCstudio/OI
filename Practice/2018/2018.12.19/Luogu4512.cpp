#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000*8;
const int Mod=998244353;
const int MG=3;
const int inf=2147483647;

int n,m;
int F[maxN],G[maxN],GR[maxN],GI[maxN],Rader[maxN],I1[maxN],I2[maxN];
int P[maxN],Q[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void Mul(int *A,int *B,int len);
void PolyInv(int *A,int *B,int len);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++) scanf("%d",&F[i]),P[n-i]=F[i];
	for (int i=0;i<=m;i++) scanf("%d",&G[i]),GR[m-i]=G[i];
	for (int i=n-m+1;i<=n;i++) P[i]=GR[i]=0;
	int N=1;while (N<=n-m) N<<=1;
	PolyInv(GR,GI,N);
	for (int i=n-m+1;i<N;i++) GI[i]=0;
	Mul(P,GI,N<<1);
	for (int i=0;i<n-m-i;i++) swap(P[i],P[n-m-i]);
	for (int i=n-m+1;i<N<<1;i++) P[i]=0;
	for (int i=0;i<=n-m;i++) printf("%d ",P[i]);printf("\n");
	N=1;while (N<=n) N<<=1;
	//for (int i=0;i<N;i++) cout<<G[i]<<" ";cout<<endl<<endl;
	//for (int i=0;i<N;i++) cout<<P[i]<<" ";cout<<endl<<endl;
	Mul(G,P,N<<1);
	for (int i=0;i<N;i++) Q[i]=(F[i]-G[i]+Mod)%Mod;
	for (int i=0;i<m;i++) printf("%d ",Q[i]);printf("\n");
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

void NTT(int *P,int N,int opt){
	int L=0,l;for (l=1;l<N;l<<=1) ++L;for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(MG,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
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

void Mul(int *A,int *B,int len){
	NTT(A,len,1);NTT(B,len,1);
	for (int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,len,-1);return;
}

void PolyInv(int *A,int *B,int len){
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	//cout<<"Polyinv:"<<len<<endl;
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	//for (int i=0;i<len<<1;i++) cout<<I1[i]<<" ";cout<<endl;
	//for (int i=0;i<len<<1;i++) cout<<I2[i]<<" ";cout<<endl;
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<len<<2;i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	//for (int i=0;i<len<<1;i++) cout<<I1[i]<<" ";cout<<endl;
	for (int i=0;i<len;i++) B[i]=(2ll*B[i]%Mod-I1[i]+Mod)%Mod;
	for (int i=0;i<len<<1;i++) I1[i]=I2[i]=0;
	return;
}
