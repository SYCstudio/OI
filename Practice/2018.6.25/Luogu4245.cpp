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

const int maxN=101000*10;
const ld Pi=acos(-1);
const int inf=2147483647;

class Complex
{
public:
	ld x,y;
};

int n,m;
ll Mod,M;
int P1[maxN],P2[maxN],Rader[maxN];
Complex A[maxN],B[maxN],C[maxN],D[maxN],E[maxN],F[maxN],G[maxN],H[maxN];
Complex Wn[maxN];
ll Ans[maxN];

void FFT(Complex *P,const int N,int opt);
Complex operator + (const Complex A,const Complex B);
Complex operator - (const Complex A,const Complex B);
Complex operator * (const Complex A,const Complex B);

int main()
{
	scanf("%d%d%lld",&n,&m,&Mod);M=sqrt(Mod)+10;
	for (int i=0;i<=n;i++) scanf("%d",&P1[i]),P1[i]%=Mod;
	for (int i=0;i<=m;i++) scanf("%d",&P2[i]),P2[i]%=Mod;
	for (int i=0;i<=n;i++) B[i].x=P1[i]%M,A[i].x=(int)(P1[i]/M);
	for (int i=0;i<=m;i++) D[i].x=P2[i]%M,C[i].x=(int)(P2[i]/M);

	int N,L=0;
	for (N=1;N<=(n+m);N<<=1) L++;
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=1;i<N;i<<=1)
		for (int k=0;k<i;k++) Wn[N/i*k]=((Complex){cos(Pi*k/i),sin(Pi*k/i)});
	
	FFT(A,N,1);FFT(B,N,1);FFT(C,N,1);FFT(D,N,1);
	for (int i=0;i<N;i++){
		E[i]=A[i]*C[i];F[i]=A[i]*D[i];G[i]=B[i]*C[i];H[i]=B[i]*D[i];
	}
	FFT(E,N,-1);FFT(F,N,-1);FFT(G,N,-1);FFT(H,N,-1);

	for (int i=0;i<N;i++)
	{
		Ans[i]=(ll)E[i].x*M%Mod*M%Mod;
		Ans[i]=(Ans[i]+(ll)F[i].x*M%Mod)%Mod;
		Ans[i]=(Ans[i]+(ll)G[i].x*M%Mod)%Mod;
		Ans[i]=(Ans[i]+(ll)H[i].x)%Mod;
	}

	for (int i=0;i<=n+m;i++) printf("%lld ",Ans[i]);
	printf("\n");
	return 0;
}

void FFT(Complex *P,const int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
		for (int l=i<<1,j=0;j<N;j+=l)
			for (int k=0;k<i;k++)
			{
				Complex X=P[j+k],Y=P[j+k+i]*((Complex){Wn[N/i*k].x,opt*Wn[N/i*k].y});
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
	if (opt==-1) for (int i=0;i<N;i++) P[i].x=(ll)(P[i].x/N+0.5);
	return;
}

Complex operator + (Complex A,Complex B){
	return ((Complex){A.x+B.x,A.y+B.y});
}

Complex operator - (Complex A,Complex B){
	return ((Complex){A.x-B.x,A.y-B.y});
}

Complex operator * (Complex A,Complex B){
	return ((Complex){A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x});
}
