#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*6;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n;
int A[maxN],B[maxN],C[maxN];
int Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int len);

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&A[i]);

	PolyInv(A,B,n);

	for (int i=0;i<n;i++) printf("%d ",B[i]);printf("\n");
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

void PolyInv(int *A,int *B,int len)
{
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,(len+1)/2);
	int N=0,L=0;
	for (N=1;N<=len*2;N<<=1) L++;
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<len;i++) C[i]=A[i];
	for (int i=len;i<N;i++) C[i]=0;
	for (int i=(len+1)/2;i<N;i++) B[i]=0;

	NTT(B,N,1);NTT(C,N,1);
	for (int i=0;i<N;i++) B[i]=((2ll*B[i]-1ll*C[i]*B[i]%Mod*B[i]%Mod)%Mod+Mod)%Mod;
	NTT(B,N,-1);
	return;
}
