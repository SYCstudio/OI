#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=101000*10;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m,inv2;
int Wn[maxN],Iwn[maxN],Rader[maxN];
int P1[maxN],P2[maxN],P3[maxN],P4[maxN];
int C[maxN],D[maxN];

int read();
int QPow(RG int x,RG int cnt);
void NTT(RG int *P,RG int N,RG int opt);
void PolyInv(RG int *A,RG int *B,RG int len);
void PolySqrt(RG int *A,RG int *B,RG int len);

int main()
{
	inv2=QPow(2,Mod-2);
	for (RG int i=0;i<=30;++i) Wn[i]=QPow(G,(Mod-1)/(1<<i)),Iwn[i]=QPow(Wn[i],Mod-2);

	n=read();m=read();
	//scanf("%d%d",&n,&m);
	for (RG int i=1;i<=n;++i)
	{
		//RG int col;scanf("%d",&col);
		C[read()]++;//E[i-1]=col;
	}

	/*
	int N,L=0;
	for (N=1;N<=n+n;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	NTT(E,N,1);
	for (int i=0;i<N;i++) E[i]=1ll*E[i]*E[i]%Mod;
	NTT(E,N,-1);
	for (int i=0;i<N;i++) cout<<E[i]<<" ";cout<<endl;
	//*/

	RG int N;
	for (N=1;N<=m;N<<=1);

	for (RG int i=0;i<=N;++i) C[i]=(Mod-4ll*C[i]%Mod)%Mod;
	++C[0];
	
	PolySqrt(C,D,N);

	//cout<<"After Sqrt:"<<endl;
	//for (int i=0;i<N;i++) cout<<D[i]<<" ";cout<<endl;

	D[0]=(D[0]+1)%Mod;
	for (int i=0;i<N;++i) C[i]=0;
	PolyInv(D,C,N);
	for (RG int i=0;i<=m;++i) C[i]=1ll*C[i]*2ll%Mod;
	for (RG int i=1;i<=m;++i) printf("%d\n",C[i]);
	return 0;
}

int read()
{
	RG char ch=getchar();RG int x=0;
	while ((ch<'0')||(ch>'9')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

int QPow(RG int x,RG int cnt)
{
	RG int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(RG int *P,RG int N,RG int opt)
{
	for (RG int i=0;i<N;++i) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (RG int i=1;i<N;i<<=1)
	{
		RG int dw=QPow(G,(Mod-1)/(i<<1));
		//if (opt==-1) dw=QPow(dw,Mod-2);
		//int dw=(opt!=-1)?(Wn[t+1]):(Iwn[t+1]);
		for (RG int j=0;j<N;j+=(i<<1))
			for (RG int k=j,w=1;k<i+j;++k,w=1ll*w*dw%Mod)
			{
				RG int X=P[k],Y=1ll*P[k+i]*w%Mod;
				P[k]=(X+Y)%Mod;P[k+i]=((X-Y)%Mod+Mod)%Mod;
				//P[k]=(X+Y);P[k+i]=X-Y;
				//if (P[k]>=Mod) P[k]-=Mod;
				//if (P[k+i]<0) P[k+i]+=Mod;
			}
	}
	if (opt==-1)
	{
		RG int inv=QPow(N,Mod-2);
		for (RG int i=0;i<N;++i) P[i]=1ll*P[i]*inv%Mod;
		reverse(&P[1],&P[N]);
	}
	return;
}

void PolyInv(RG int *A,RG int *B,RG int len)
{
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}

	PolyInv(A,B,len>>1);

	RG int N,L=0;
	for (N=1;N<=len<<1;N<<=1) ++L;
	for (RG int i=0;i<N;++i) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1)),P1[i]=P2[i]=0;
	for (RG int i=0;i<len;++i) P1[i]=A[i],P2[i]=B[i];
	NTT(P1,N,1);NTT(P2,N,1);
	for (int i=0;i<N;++i) P1[i]=1ll*P1[i]*P2[i]%Mod*P2[i]%Mod;//P2[i]=((2ll*P2[i]%Mod-1ll*P1[i]*P2[i]%Mod*P2[i]%Mod)%Mod+Mod)%Mod;
	NTT(P1,N,-1);
	for (RG int i=0;i<=len<<1;++i) B[i]=((2ll*B[i]%Mod-P1[i])%Mod+Mod)%Mod;
	return;
}

void PolySqrt(RG int *A,RG int *B,RG int len)
{
	if (len==1){
		B[0]=A[0];return;
	}
	PolySqrt(A,B,len>>1);
	
	PolyInv(B,P4,len);

	/*
	cout<<"GetInv:"<<endl;
	for (int i=0;i<len;i++) cout<<P3[i]<<" ";cout<<endl;
	for (int i=0;i<len;i++) cout<<P4[i]<<" ";cout<<endl;
	//*/
	
	RG int N,L=0;
	for (N=1;N<=len<<1;N<<=1) ++L;
	for (RG int i=0;i<N;++i) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));//,P3[i]=0;
	//for (int i=len;i<N;i++) P4[i]=0;

	for (RG int i=0;i<len;++i) P3[i]=A[i];

	/*
	cout<<"Mul:"<<endl;
	for (int i=0;i<N;i++) cout<<P3[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) cout<<P4[i]<<" ";cout<<endl;
	//*/
	
	NTT(P3,N,1);NTT(P4,N,1);
	for (int i=0;i<N;++i) P3[i]=1ll*P3[i]*P4[i]%Mod;
	NTT(P3,N,-1);

	//for (int i=0;i<N;i++) cout<<P3[i]<<" ";cout<<endl;

	for (RG int i=0;i<len;++i) B[i]=1ll*(B[i]+P3[i])%Mod*inv2%Mod;
	return;
}

