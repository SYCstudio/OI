#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*10;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m;
ll A[maxN],B[maxN];
int Rader[maxN];

void NTT(ll *P,int N,int opt);
ll QPow(ll x,ll cnt);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++) scanf("%lld",&A[i]);
	for (int i=0;i<=m;i++) scanf("%lld",&B[i]);

	int N=1,L=0;
	for (N=1;N<=(n+m);N<<=1) L++;
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));

	NTT(A,N,1);NTT(B,N,1);
	for (int i=0;i<N;i++) A[i]=A[i]*B[i]%Mod;
	NTT(A,N,-1);

	for (int i=0;i<=(n+m);i++) printf("%lld ",A[i]);
	printf("\n");
	return 0;
}

void NTT(ll *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int l=i<<1;
		ll dw=QPow(G,(Mod-1)/l);
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=l)
		{
			ll w=1;
			for (int k=0;k<i;k++,w=w*dw%Mod)
			{
				ll X=P[j+k],Y=w*P[j+k+i]%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
		}
	}
	if (opt==-1)
	{
		ll inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=P[i]*inv%Mod;
	}
	return;
}

ll QPow(ll x,ll cnt)
{
	ll Ret=1;
	while (cnt)
	{
		if (cnt&1) Ret=Ret*x%Mod;
		x=x*x%Mod;cnt>>=1;
	}
	return Ret;
}
