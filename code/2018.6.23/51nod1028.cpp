#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<complex>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*5;
const ld Pi=acos(-1);
const int inf=2147483647;

/*
class Complex
{
public:
	ld x,y;
	Complex(){};
	Complex(ld a,ld b){
		x=a;y=b;return;
	}
};
//*/

char Input[maxN];
//Complex A[maxN],B[maxN];
complex<ld> A[maxN],B[maxN];
int Rader[maxN],Ans[maxN];
//Complex Wn[maxN],Iwn[maxN];
complex<ld> Wn[maxN],Iwn[maxN];

//void FFT(Complex *P,int N,Complex *W);
void FFT(complex<ld> *P,int N,complex<ld> *W);
//Complex operator + (const Complex A,const Complex B);
//Complex operator * (const Complex A,const Complex B);
//Complex operator - (const Complex A,const Complex B);

int main()
{
	scanf("%s",Input+1);
	int n=strlen(Input+1);
	for (int i=1;i<=n;i++) A[i-1]=Input[i]-'0';
	scanf("%s",Input+1);
	int m=strlen(Input+1);
	for (int i=1;i<=m;i++) B[i-1]=Input[i]-'0';


	reverse(&A[0],&A[n]);reverse(&B[0],&B[m]);

	int N=0,L=0;
	for (N=1;N<=(n+m);N<<=1) L++;
	
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) Wn[i]=complex<ld>(cos(2*Pi*i/N),sin(2*Pi*i/N)),Iwn[i]=conj(Wn[i]);
	//for (int i=0;i<N;i++) Iwn[i]=Wn[N-i-1];

	FFT(A,N,Wn);FFT(B,N,Wn);
	for (int i=0;i<N;i++) A[i]=A[i]*B[i];
	FFT(A,N,Iwn);
	for (int i=0;i<N;i++) Ans[i]=(int)(A[i].real()/N+0.5);

	for (int i=0;i<N;i++) Ans[i+1]+=Ans[i]/10,Ans[i]%=10;

	
	int top=N;
	while (Ans[top]==0) top--;
	for (int i=top;i>=0;i--) printf("%d",Ans[i]);
	printf("\n");
	return 0;
}

//void FFT(Complex *P,int N,Complex *W)
void FFT(complex<ld> *P,int N,complex<ld> *W)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int l=i<<1;
		for (int j=0;j<N;j+=l)
			for (int k=0;k<i;k++)
			{
				complex<ld> X=P[j+k],Y=W[N/l*k]*P[j+k+i];
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
	}
	return;
}

/*
Complex operator + (const Complex A,const Complex B){
	return Complex(A.x+B.x,A.y+B.y);
}

Complex operator - (const Complex A,const Complex B){
	return Complex(A.x-B.x,A.y-B.y);
}

Complex operator * (const Complex A,const Complex B){
	return Complex(A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x);
}

//*/
