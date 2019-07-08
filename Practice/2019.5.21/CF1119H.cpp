#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define pw(x) (1<<(x))
const int maxN=101000;
const int maxS=150000;
const int Mod=998244353;
const int inv2=499122177;
const int inv4=748683265;

int n,K,N,X,Y,Z;
int A[maxS],B[maxS],C[maxS],F[maxS];

void FWT(int *P,int N,int opt);
int QPow(int x,int cnt);
int main()
{
	scanf("%d%d",&n,&K);
	N=pw(K);
	scanf("%d%d%d",&X,&Y,&Z);
	int suma=0;
	for (int i=1; i<=n; i++) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		suma^=a;
		++A[a^b];
		++B[a^c];
		++C[b^c];
	}
	FWT(A,N,1);
	FWT(B,N,1);
	FWT(C,N,1);
	int S1=((X+Y)%Mod+Z)%Mod,S2=((X+Y)%Mod-Z+Mod)%Mod,S3=((X+Z)%Mod-Y+Mod),S4=(X-(Y+Z)%Mod+Mod)%Mod;
	for (int i=0; i<N; i++) {
		int a,b,c,d;
		a=((n+A[i])%Mod+(B[i]+C[i])%Mod)%Mod;
		a=1ll*a*inv4%Mod;
		b=((n+A[i])%Mod-(B[i]+C[i])%Mod+Mod)%Mod;
		b=1ll*b*inv4%Mod;
		c=((n+B[i])%Mod-(A[i]+C[i])%Mod+Mod)%Mod;
		c=1ll*c*inv4%Mod;
		d=((n+C[i])%Mod-(A[i]+B[i])%Mod+Mod)%Mod;
		d=1ll*d*inv4%Mod;
		F[i]=1ll*QPow(S1,a)*QPow(S2,b)%Mod*QPow(S3,c)%Mod*QPow(S4,d)%Mod;
	}
	FWT(F,N,-1);
	for (int i=0; i<N; i++) printf("%d ",F[i^suma]);
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
void FWT(int *P,int N,int opt)
{
	for (int i=1; i<N; i<<=1)
		for (int j=0; j<N; j+=(i<<1))
			for (int k=0; k<i; k++) {
				int X=P[j+k],Y=P[j+k+i];
				P[j+k]=(X+Y)%Mod;
				P[j+k+i]=(X-Y+Mod)%Mod;
				if (opt==-1) P[j+k]=1ll*P[j+k]*inv2%Mod,P[j+k+i]=1ll*P[j+k+i]*inv2%Mod;
			}
	return;
}
