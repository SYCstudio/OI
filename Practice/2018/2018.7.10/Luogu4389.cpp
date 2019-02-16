#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*12;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m;
int P1[maxN],P2[maxN],Rader[maxN],Tot[maxN];
int Inv[maxN],I1[maxN],I2[maxN],L1[maxN],L2[maxN],E1[maxN],E2[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int len);
void PolyInte(int *A,int *B,int len);
void PolyDery(int *A,int *B,int len);
void PolyLn(int *A,int *B,int len);
void PolyExp(int *A,int *B,int len);

int main()
{
	Inv[0]=Inv[1]=1;for (int i=2;i<maxN;i++) Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;

	scanf("%d%d",&n,&m);
	int N;
	for (N=1;N<=m+m;N<<=1) ;
	for (int i=1;i<=n;i++)
	{
		int v;scanf("%d",&v);
		Tot[v]++;
	}
	for (int i=1;i<=m;i++)
		if (Tot[i])
		{
			int k=1ll*i*Tot[i]%Mod;
			for (int j=i;j<=m;j+=i)
				P1[j]=(P1[j]+k)%Mod;
		}
	for (int i=0;i<=m;i++) P1[i]=1ll*P1[i]*Inv[i]%Mod;
	//for (int i=0;i<N;i++) cout<<P1[i]<<" ";cout<<endl;
	PolyExp(P1,P2,N);
	for (int i=1;i<=m;i++) printf("%d\n",P2[i]);
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
	int L=0;
	for (int i=1;i<N;i<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
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

void PolyInv(int *A,int *B,int len)
{
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<(len<<1);i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=((B[i]+B[i])%Mod+Mod-I1[i])%Mod;
	for (int i=0;i<(len<<1);i++) I1[i]=I2[i]=0;
	return;
}

void PolyInte(int *A,int *B,int len)
{
	for (int i=0;i<len;i++) B[i+1]=1ll*A[i]*Inv[i+1]%Mod;
	B[0]=0;return;
}

void PolyDery(int *A,int *B,int len)
{
	for (int i=1;i<len;i++) B[i-1]=1ll*A[i]*i%Mod;
	return;
}

void PolyLn(int *A,int *B,int len)
{
	PolyDery(A,L1,len);PolyInv(A,L2,len);
	NTT(L1,len<<1,1);NTT(L2,len<<1,1);
	for (int i=0;i<(len<<1);i++) L1[i]=1ll*L1[i]*L2[i]%Mod;
	NTT(L1,len<<1,-1);
	PolyInte(L1,B,len);
	for (int i=0;i<(len<<1);i++) L1[i]=L2[i]=0;
	return;
}

void PolyExp(int *A,int *B,int len)
{
	if (len==1){
		B[0]=1;return;
	}
	PolyExp(A,B,len>>1);
	//cout<<"PolyExp:"<<len<<endl;
	PolyLn(B,E1,len);
	for (int i=0;i<len;i++) E1[i]=(A[i]-E1[i]+Mod)%Mod,E2[i]=B[i];
	E1[0]=(E1[0]+1)%Mod;

	//cout<<"Before:"<<endl;
	//for (int i=0;i<len;i++) cout<<E1[i]<<" ";cout<<endl;
	//for (int i=0;i<len;i++) cout<<E2[i]<<" ";cout<<endl;
	
	NTT(E1,len<<1,1);NTT(E2,len<<1,1);
	for (int i=0;i<(len<<1);i++) E1[i]=1ll*E1[i]*E2[i]%Mod;
	NTT(E1,len<<1,-1);

	//cout<<"After:"<<endl;
	//for (int i=0;i<(len<<1);i++) cout<<E1[i]<<" ";cout<<endl;
	
	for (int i=0;i<len;i++) B[i]=E1[i];
	for (int i=0;i<(len<<1);i++) E1[i]=E2[i]=0;
	return;
}
