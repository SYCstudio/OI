#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int Mod=1000000007;
const int maxN=505000;

int n,A[maxN],B[maxN];

int QPow(int x,int cnt);
int main()
{
	scanf("%d",&n);
	int inv100=Inv(100);
	for (int i=1; i<=n; i++) scanf("%d%d",&A[i],&B[i]),A[i]=1ll*A[i]*inv100%Mod,B[i]=1ll*B[i]*inv100%Mod;
	for (int i=n; i>=2; i--) {
		int fc=1ll*B[i]*B[i-1]%Mod;
		fc=(Mod+1-fc)%Mod;
		fc=Inv(fc);
		int a=1ll*A[i]*A[i-1]%Mod*fc%Mod;
		int b=1ll*A[i-1]*A[i-1]%Mod*B[i]%Mod*fc%Mod;
		b=(B[i-1]+b)%Mod;
		A[i-1]=a;
		B[i-1]=b;
	}
	printf("%d\n",A[1]);
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
