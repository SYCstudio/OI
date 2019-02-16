#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=101000*8;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n;
int Fac[maxN],IFac[maxN];
int B1[maxN],B2[maxN],IB[maxN],I1[maxN],I2[maxN],Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int len);

int main(){
	Fac[0]=IFac[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	IFac[maxN-1]=QPow(Fac[maxN-1],Mod-2);for (int i=maxN-2;i>=1;i--) IFac[i]=1ll*IFac[i+1]*(i+1)%Mod;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) B1[i]=1ll*QPow(2,(1ll*i*(i-1)/2)%(Mod-1))*IFac[i]%Mod,B2[i]=B1[i];
	B2[0]=1;int N=1;while (N<=n) N<<=1;

	//for (int i=0;i<N;i++) cout<<B1[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B2[i]<<" ";cout<<endl;
	
	PolyInv(B2,IB,N);while (N<=n+n) N<<=1;

	//for (int i=0;i<N;i++) cout<<IB[i]<<" ";cout<<endl;
	
	NTT(B1,N,1);NTT(IB,N,1);
	for (int i=0;i<N;i++) B1[i]=1ll*B1[i]*IB[i]%Mod;
	NTT(B1,N,-1);
	if (n>=1) printf("1\n");
	if (n>=2) printf("-1\n");
	for (int i=3;i<=n;i++){
		int sum=1ll*Fac[i]*QPow(i,Mod-2)%Mod*QPow(2,(1ll*i*(i-1)/2-i)%(Mod-1))%Mod;
		//cout<<i<<" "<<sum<<" "<<1ll*B1[i]*Fac[i]%Mod<<endl;
		printf("%lld\n",1ll*sum*QPow(1ll*B1[i]*Fac[i]%Mod,Mod-2)%Mod);
	}
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
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<len<<1;i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=(2ll*B[i]%Mod-I1[i]%Mod+Mod)%Mod;
	for (int i=0;i<len<<1;i++) I1[i]=I2[i]=0;
	return;
}
