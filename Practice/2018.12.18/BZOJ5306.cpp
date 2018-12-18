#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*8;
const int maxF=10100000;
const int Mod=1004535809;
const int G=3;
const int inf=2147483647;

int n,m,s,N,L;
int A[maxN],B[maxN],W[maxN],Rader[maxN];
int Fac[maxF],InvF[maxF];

int QPow(int x,int cnt);
int C(int n,int m);
void NTT(int *P,int opt);

int main(){
	scanf("%d%d%d",&n,&m,&s);for (int i=0;i<=m;i++) scanf("%d",&W[i]);
	Fac[0]=InvF[0]=1;int mxn=max(n,m);for (int i=1;i<=mxn;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	InvF[mxn]=QPow(Fac[mxn],Mod-2);for (int i=mxn-1;i>=1;i--) InvF[i]=1ll*InvF[i+1]*(i+1)%Mod;
	int mx=min(m,n/s);
	for (N=1;N<=mx+mx;N<<=1) ++L;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<=mx;i++)
		A[i]=1ll*C(m,i)*Fac[i*s]%Mod*QPow(QPow(Fac[s],i),Mod-2)%Mod*C(n,i*s)%Mod*QPow(m-i,n-i*s)%Mod*Fac[i]%Mod,B[i]=(InvF[i]*((i&1)?(-1):(1))+Mod)%Mod;
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	
	reverse(&B[0],&B[mx+1]);
	NTT(A,1);NTT(B,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,-1);
	int Ans=0;for (int i=0;i<=mx;i++) Ans=(Ans+1ll*A[i+mx]*W[i]%Mod*InvF[i]%Mod)%Mod;
	printf("%d\n",Ans);return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int C(int n,int m){
	return 1ll*Fac[n]*InvF[n-m]%Mod*InvF[m]%Mod;
}

void NTT(int *P,int opt){
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
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
