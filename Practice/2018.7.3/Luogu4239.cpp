#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*5;
const int Mod=1e9+7;
const int M=sqrt(Mod);
const ld Pi=acos(-1);
const int inf=2147483647;

class Complex
{
public:
	ld x,y;
	Complex(){}
	Complex(ld a,ld b){
		x=a;y=b;return;
	}
};

int n;
int A[maxN],B[maxN],C[maxN],D[maxN],Rader[maxN];
Complex P1[maxN],P2[maxN],P3[maxN],P4[maxN],P5[maxN],P6[maxN],P7[maxN],Wn[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
int QPow(int x,int cnt);
void PolyInv(int *A,int *B,int len);
void Mul(int *A,int *B,int *C,int len);
void FFT(Complex *P,int N,int opt);

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&A[i]);

	PolyInv(A,B,n);

	for (int i=0;i<n;i++) printf("%d ",B[i]);
	printf("\n");
	return 0;
}

Complex operator + (Complex A,Complex B){
	return Complex(A.x+B.x,A.y+B.y);
}

Complex operator - (Complex A,Complex B){
	return Complex(A.x-B.x,A.y-B.y);
}

Complex operator * (Complex A,Complex B){
	return Complex(A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x);
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

void PolyInv(int *A,int *B,int len)
{
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,(len+1)/2);
	Mul(A,B,C,len);
	Mul(C,B,D,len);
	for (int i=0;i<len;i++) B[i]=(B[i]+B[i])%Mod;
	for (int i=0;i<len;i++) B[i]=(B[i]-D[i]+Mod)%Mod;
	return;
}

void Mul(int *A,int *B,int *C,int len)
{
	int N=0,L=0;
	for (N=1;N<=len*2;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1)),Wn[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));

	for (int i=0;i<N;i++) P1[i]=P2[i]=P3[i]=P4[i]=Complex(0,0),C[i]=0;
	for (int i=0;i<len;i++) P1[i]=Complex(A[i]/M,0),P2[i]=Complex(A[i]%M,0);
	for (int i=0;i<(len+1)/2;i++) P3[i]=Complex(B[i]/M,0),P4[i]=Complex(B[i]%M,0);

	FFT(P1,N,1);FFT(P2,N,1);FFT(P3,N,1);FFT(P4,N,1);
	for (int i=0;i<N;i++)
	{
		Complex a=P1[i],b=P2[i],c=P3[i],d=P4[i];
		P1[i]=a*c;P2[i]=a*d+b*c;P3[i]=b*d;
	}
	FFT(P1,N,-1);FFT(P2,N,-1);FFT(P3,N,-1);

	for (int i=0;i<len;i++)
	{
		C[i]=1ll*(ll)P1[i].x*M%Mod*M%Mod;
		C[i]=(1ll*C[i]+1ll*(ll)P2[i].x*M%Mod)%Mod;
		C[i]=(1ll*C[i]+(ll)P3[i].x)%Mod;
		C[i]=(C[i]%Mod+Mod)%Mod;
	}
	return;
}

void FFT(Complex *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0;k<i;k++)
			{
				Complex X=P[j+k],Y=P[j+k+i]*Complex(Wn[N/(i<<1)*k].x,opt*Wn[N/(i<<1)*k].y);
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
	if (opt==-1) for (int i=0;i<N;i++) P[i].x=(ll)(P[i].x/N+0.5);
	return;
}
