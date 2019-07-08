#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=101000*8;
const int G=3;
const int Mod=998244353;

int n;
ll m;
int Fc[maxN],Ifc[maxN];
int In[maxN],A[maxN],B[maxN],C[maxN],R[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);

int main()
{
	//freopen("in","r",stdin);
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fc[maxN-1],Mod-2);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%lld",&n,&m);
	int N=1;
	while (N<=n+n) N<<=1;
	m=m%(Mod-1);
	for (int i=0; i<=n; i++) scanf("%d",&In[i]),B[i]=1ll*Fc[i]*In[i]%Mod;
	for (int i=0; i<=n; i++) C[i]=Ifc[n-i];

	//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<C[i]<<" ";cout<<endl;

	NTT(B,N,1);
	NTT(C,N,1);
	for (int i=0; i<N; i++) B[i]=1ll*B[i]*C[i]%Mod;
	NTT(B,N,-1);

	for (int i=0; i<=n; i++) A[i]=1ll*B[i+n]*Ifc[i]%Mod;
	for (int i=0; i<=n; i++) A[i]=1ll*A[i]*QPow(QPow(i+1,Mod-2),m)%Mod*Fc[i]%Mod;
	mem(C,0);
	for (int i=0; i<=n; i++) C[i]=(i&1)?Mod-Ifc[i]:Ifc[i];
	reverse(&C[0],&C[n+1]);
	//for (int i=0;i<=N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<=N;i++) cout<<C[i]<<" ";cout<<endl;
	NTT(A,N,1);
	NTT(C,N,1);
	for (int i=0; i<N; i++) A[i]=1ll*A[i]*C[i]%Mod;
	NTT(A,N,-1);
	//for (int i=0;i<=N;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=0; i<=n; i++) printf("%lld ",1ll*A[i+n]*Ifc[i]%Mod);
	printf("\n");
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
	int l=-1,_n=N;
	while (_n) ++l,_n>>=1;
	for (int i=0; i<N; i++) R[i]=(R[i>>1]>>1)|((i&1)<<(l-1));
	for (int i=0; i<N; i++) if (i<R[i]) swap(P[i],P[R[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0; j<N; j+=(i<<1))
			for (int k=0,w=1; k<i; k++,w=1ll*w*dw%Mod) {
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
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