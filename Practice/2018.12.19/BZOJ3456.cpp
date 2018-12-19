#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=130000*8;
const int Mod=1004535809;
const int G=3;
const int inf=2147483647;

int n;
int Rader[maxN],A[maxN],B[maxN],IB[maxN],I1[maxN],I2[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int len);

int main(){
	scanf("%d",&n);
	for (int i=1,mul=1;i<=n;mul=1ll*mul*i%Mod,i++) A[i]=1ll*QPow(2,1ll*i*(i-1)/2%(Mod-1))*QPow(mul,Mod-2)%Mod;
	for (int i=0,mul=1;i<=n;i++,mul=1ll*mul*i%Mod) B[i]=1ll*QPow(2,1ll*i*(i-1)/2%(Mod-1))*QPow(mul,Mod-2)%Mod;
	int N=1;while (N<=n) N<<=1;
	for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	PolyInv(B,IB,N);
	
	N=1;while (N<=(n+n)) N<<=1;
	//for (int i=0;i<N;i++) cout<<IB[i]<<" ";cout<<endl;
	
	NTT(A,N,1);NTT(IB,N,1);for (int i=0;i<N;i++) A[i]=1ll*A[i]*IB[i]%Mod;NTT(A,N,-1);
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	int fac=1;for (int i=1;i<n;i++) fac=1ll*fac*i%Mod;
	printf("%lld\n",1ll*A[n]*fac%Mod);
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
		int dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2);for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

void PolyInv(int *A,int *B,int len){
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	//cout<<"PolyInv:"<<len<<endl;
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	//for (int i=0;i<len<<1;i++) cout<<I1[i]<<" ";cout<<endl;
	//for (int i=0;i<len<<1;i++) cout<<I2[i]<<" ";cout<<endl;
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<len<<1;i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	//for (int i=0;i<len;i++) cout<<I1[i]<<" ";cout<<endl;
	for (int i=0;i<len;i++) B[i]=(2ll*B[i]%Mod-I1[i]%Mod+Mod)%Mod;
	for (int i=0;i<len<<1;i++) I1[i]=I2[i]=0;
	return;
}
//*/
