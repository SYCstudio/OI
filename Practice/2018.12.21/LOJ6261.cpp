#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*4;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n;ll K;
int Rader[maxN];
int A[maxN],B[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);

int main(){
	scanf("%d%lld",&n,&K);K%=Mod;
	for (int i=0;i<n;i++) scanf("%d",&A[i]);
	B[0]=1;
	for (int i=1;i<n;i++) B[i]=1ll*B[i-1]*(i+K-1)%Mod*QPow(i,Mod-2)%Mod;
	//for (int i=0;i<n;i++) cout<<B[i]<<" ";cout<<endl;
	int N=1;while (N<=n+n) N<<=1;
	NTT(A,N,1);NTT(B,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);
	for (int i=0;i<n;i++) printf("%d\n",A[i]);
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
	int l=1,L=0;while (l<N) l<<=1,++L;for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
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
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
