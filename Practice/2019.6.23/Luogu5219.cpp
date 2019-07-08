#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=50500*4;
const int Mod=998244353;
const int G=3;

int n,m;
int Fc[maxN],Ifc[maxN];
int P1[maxN],P2[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void QPow(int *P,int n,int len);
int main()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%d",&n,&m);
	for (int i=0; i<m; i++) P1[i]=Ifc[i];
	for (int i=0; i+1<m; i++) P2[i]=Ifc[i];

	QPow(P1,n,n);
	QPow(P2,n,n);

	//cout<<"P1:";for (int i=0;i<=n;i++) cout<<P1[i]<<" ";cout<<endl;
	//cout<<"P2:";for (int i=0;i<=n;i++) cout<<P2[i]<<" ";cout<<endl;

	int Ans=(P1[n-2]-P2[n-2]+Mod)%Mod;
	Ans=1ll*Ans*Fc[n-2]%Mod;
	printf("%d\n",Ans);
	return 0;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
void NTT(int *P,int N,int opt)
{
	static int Ra[maxN];
	int _N=1,l=-1;
	while (_N<N) _N<<=1,++l;
	for (int i=0; i<N; i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
	for (int i=0; i<N; i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=Inv(dw);
		for (int j=0; j<N; j+=(i<<1))
			for (int k=0,w=1; k<i; k++,w=1ll*w*dw%Mod) {
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;
				P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1) {
		int inv=Inv(N);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
void QPow(int *P,int n,int len)
{
	static int R[maxN];
	memset(R,0,sizeof(R));
	R[0]=1;
	int N=1;
	while (N<len+len) N<<=1;
	while (n) {
		if (n&1) {
			//for (int i=0;i<N;i++) cout<<P[i]<<" ";cout<<endl;
			//for (int i=0;i<N;i++) cout<<R[i]<<" ";cout<<endl;
			NTT(P,N,1);
			NTT(R,N,1);
			for (int i=0; i<N; i++) R[i]=1ll*R[i]*P[i]%Mod;
			NTT(P,N,-1);
			NTT(R,N,-1);
			for (int i=len; i<N; i++) R[i]=P[i]=0;
			//for (int i=0;i<N;i++) cout<<P[i]<<" ";cout<<endl;
			//for (int i=0;i<N;i++) cout<<R[i]<<" ";cout<<endl;
			//cout<<endl;
		}
		NTT(P,N,1);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*P[i]%Mod;
		NTT(P,N,-1);
		for (int i=len; i<N; i++) P[i]=0;
		n>>=1;
	}
	for (int i=0; i<len; i++) P[i]=R[i];
	return;
}
