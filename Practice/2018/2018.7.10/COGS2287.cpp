#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "crazy_robot"

const int maxN=101001*10;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n;
int Fac[maxN],Inv[maxN];
int A[maxN],Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
int C(int n,int m);

int main()
{
	freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	Fac[0]=Inv[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxN-1]=QPow(Fac[maxN-1],Mod-2);
	for (int i=maxN-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;

	scanf("%d",&n);
	for (int i=0;i<=n;i++)
		if (i&1) A[i]=0;
		else A[i]=(C(i,i/2)-C(i,i/2+1)+Mod)%Mod;

	for (int i=0;i<=n;i++) A[i]=1ll*A[i]*Inv[i]%Mod;
	int N,L=0;
	for (N=1;N<=n+n;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	NTT(A,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*A[i]%Mod;
	NTT(A,N,-1);
	
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*Fac[i]%Mod;
	

	int Ans=0;
	for (int i=0;i<=n;i++) Ans=(Ans+1ll*A[i]*C(n,i)%Mod)%Mod;

	printf("%d\n",Ans);
	return 0;
}

int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod)
			{
				int x=P[j+k],y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(x+y)%Mod;P[j+k+i]=(x-y+Mod)%Mod;
			}
	}
	if (opt==-1)
	{
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

int C(int n,int m)
{
	if ((n<0)||(n<m)) return 0;
	return 1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
