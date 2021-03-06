#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*5;
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
int A[maxN],B[maxN],Rader[maxN];
Complex P1[maxN],P2[maxN],Wn[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
void FFT(Complex *P,int N,int opt);

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d%d",&A[i],&B[i]);
	reverse(&B[0],&B[n]);

	
	for (int i=0;i<n;i++) P1[i].x=A[i],P2[i].x=B[i];
	int N,L=0;
	for (N=1;N<=n+n;N<<=1) L++;
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) Wn[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));
	FFT(P1,N,1);FFT(P2,N,1);
	for (int i=0;i<N;i++) P1[i]=P1[i]*P2[i];
	FFT(P1,N,-1);
	//for (int i=0;i<N;i++) cout<<P1[i].x<<" ";cout<<endl;
	for (int i=0;i<n;i++) printf("%lld\n",(ll)P1[n-1+i].x);
	//*/
	/*
	for (int i=0;i<n;i++)
	{
		ll sum=0;
		for (int j=0;n-i-1-j>=0;j++) sum=sum+A[j]*B[n-i-1-j];
		printf("%lld\n",sum);
	}
	//*/
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

void FFT(Complex *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
		for (int j=0;j<N;j=j+(i<<1))
			for (int k=0;k<i;k++)
			{
				Complex X=P[j+k],Y=P[j+k+i]*Complex(Wn[N/(i<<1)*k].x,Wn[N/(i<<1)*k].y*opt);
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
	if (opt==-1) for (int i=0;i<N;i++) P[i].x=(ll)(P[i].x/N+0.5);
	return;
}
