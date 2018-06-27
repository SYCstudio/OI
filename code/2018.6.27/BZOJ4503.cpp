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

const int maxN=101000*4;
const ld Pi=acos(-1);
const ld eps=1e-6;
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

int n,m;
char A[maxN],B[maxN];
ll Rader[maxN],NA[maxN],NB[maxN],Val[maxN];
Complex P1[maxN],P2[maxN],P3[maxN],P4[maxN],P5[maxN],P6[maxN],Wn[maxN];
int Anscnt,Ans[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
void FFT(Complex *P,int N,int opt);

int main()
{
	scanf("%s",A+1);scanf("%s",B+1);
	int n=strlen(A+1),m=strlen(B+1);
	for (int i=1;i<=n;i++) NA[i-1]=A[i]-'a'+1;
	for (int i=1;i<=m;i++) NB[i-1]=(B[i]=='?')?(0):(B[i]-'a'+1);
	reverse(&NB[0],&NB[m]);

	//for (int i=0;i<n;i++) cout<<NA[i]<<" ";cout<<endl;
	//for (int i=0;i<m;i++) cout<<NB[i]<<" ";cout<<endl;

	for (int i=0;i<n;i++) P1[i].x=NA[i]*NA[i]*NA[i],P3[i].x=NA[i]*NA[i],P5[i].x=NA[i];
	for (int i=0;i<m;i++) P2[i].x=NB[i],P4[i].x=NB[i]*NB[i],P6[i].x=NB[i]*NB[i]*NB[i];

	int N,L=0;
	for (N=1;N<=n+m;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1)),Wn[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));

	FFT(P1,N,1);FFT(P2,N,1);FFT(P3,N,1);FFT(P4,N,1);FFT(P5,N,1);FFT(P6,N,1);
	for (int i=0;i<N;i++) P1[i]=P1[i]*P2[i],P3[i]=P3[i]*P4[i],P5[i]=P5[i]*P6[i];
	FFT(P1,N,-1);FFT(P3,N,-1);FFT(P5,N,-1);
	//for (int i=0;i<N;i++) cout<<P1[i].x<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<P3[i].x<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<P5[i].x<<" ";cout<<endl;
	for (int i=0;i<N;i++) Val[i]=P1[i].x-2ll*P3[i].x+P5[i].x;
	//for (int i=0;i<N;i++) cout<<Val[i]<<" ";cout<<endl;

	for (int i=m-1;i<=n-1;i++) if (Val[i]==0) Ans[++Anscnt]=i-(m-1);
	printf("%d\n",Anscnt);
	for (int i=1;i<=Anscnt;i++) printf("%d\n",Ans[i]);
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
