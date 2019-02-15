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

int n,N,L;
int A[maxN],B[maxN],Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int opt);

int main(){
	scanf("%d",&n);
	for (N=1;N<=n+n;N<<=1) ++L;for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	//Inv[1]=1;for (int i=2;i<maxN;i++) Inv[i]=(Mod-1ll*(Mod/i)*Inv[Mod%i]%Mod)%Mod;
	A[0]=1;B[0]=1;B[1]=n+1;
	for (int i=1,mul=1,opt=-1;i<=n;i++,mul=1ll*mul*i%Mod,opt*=-1){
		A[i]=(opt*QPow(mul,Mod-2)+Mod)%Mod;
	}
	for (int i=2,mul=2;i<=n;i++,mul=1ll*mul*i%Mod){
		B[i]=(QPow(i,n+1)-1+Mod)%Mod;
		B[i]=1ll*B[i]*QPow(mul,Mod-2)%Mod*QPow(i-1,Mod-2)%Mod;
	}
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	NTT(A,1);NTT(B,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,-1);
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	int Ans=0;
	for (int i=0,mul1=1,mul2=1;i<=n;i++,mul1=2ll*mul1%Mod,mul2=1ll*mul2*i%Mod)
		Ans=(Ans+1ll*mul1*mul2%Mod*A[i]%Mod)%Mod;
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
