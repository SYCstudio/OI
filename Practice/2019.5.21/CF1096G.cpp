#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=3010000;
const int Mod=998244353;
const int G=3;

int n,K;
int P[maxN],R[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
int main()
{
	scanf("%d%d",&n,&K);
	for (int i=1; i<=K; i++) {
		int x;
		scanf("%d",&x);
		P[x]=1;
	}
	int N=1;
	while (N<=(n*10)) N<<=1;
	NTT(P,N,1);
	for (int i=0; i<N; i++) P[i]=QPow(P[i],n/2);
	NTT(P,N,-1);
	int Ans=0;
	for (int i=0; i<N; i++) Ans=(Ans+1ll*P[i]*P[i]%Mod)%Mod;
	printf("%d\n",Ans);
	return 0;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		cnt>>=1;
		x=1ll*x*x%Mod;
	}
	return ret;
}
void NTT(int *P,int N,int opt)
{
	int _N=N,l=-1;
	while (_N) _N>>=1,++l;
	for (int i=0; i<N; i++) R[i]=(R[i>>1]>>1)|((i&1)<<(l-1));
	for (int i=0; i<N; i++) if (i<R[i]) swap(P[i],P[R[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0; j<N; j+=(i<<1))
			for (int k=0,w=1; k<i; k++,w=1ll*w*dw%Mod) {
				int X=P[j+k],Y=1ll*w*P[j+k+i]%Mod;
				P[j+k]=(X+Y)%Mod;
				P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1) {
		int inv=QPow(N,Mod-2);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
