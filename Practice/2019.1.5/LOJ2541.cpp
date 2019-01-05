#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*4;
const int Mod=998244353;
const int G=3;
const int maxBit=20;

int n;
int W[maxN];
int F[maxBit][maxN],Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
int Divide(int d,int l,int r);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&W[i]);
	int sum=0,Ans=0;for (int i=2;i<=n;i++) sum=(sum+W[i])%Mod;
	Divide(1,2,n);
	//for (int i=0;i<=sum;i++) cout<<F[1][i]<<" ";cout<<endl;
	for (int i=0;i<=sum;i++) Ans=(Ans+1ll*W[1]%Mod*F[1][i]%Mod*QPow(i+W[1],Mod-2)%Mod)%Mod;
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
void NTT(int *P,int N,int opt){
	int l=1,L=0;while (l<N) l<<=1,++L;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
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
int Divide(int d,int l,int r){
	if (l==r){
		F[d][0]=1;F[d][W[l]]=Mod-1;
		return W[l];
	}
	int lsz,rsz,mid=(l+r)>>1;
	lsz=Divide(d+1,l,mid);
	for (int i=0;i<=lsz;i++) F[d][i]=F[d+1][i],F[d+1][i]=0;
	rsz=Divide(d+1,mid+1,r);
	int N=1;while (N<=lsz+rsz+1) N<<=1;
	//for (int i=0;i<N;i++) cout<<F[d][i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<F[d+1][i]<<" ";cout<<endl;
	NTT(F[d],N,1);NTT(F[d+1],N,1);
	for (int i=0;i<N;i++) F[d][i]=1ll*F[d][i]*F[d+1][i]%Mod;
	NTT(F[d],N,-1);
	//for (int i=0;i<N;i++) cout<<F[d][i]<<" ";cout<<endl;
	for (int i=lsz+rsz+1;i<N;i++) F[d][i]=0;
	for (int i=0;i<N;i++) F[d+1][i]=0;
	return lsz+rsz;
}
