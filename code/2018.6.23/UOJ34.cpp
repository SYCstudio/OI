#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*10;
const ld Pi=acos(-1);
const int inf=2147483647;

int Rader[maxN];
complex<ld> P1[maxN],P2[maxN];
complex<ld> Wn[maxN],Iwn[maxN];

void FFT(complex<ld> *P,int N,const int opt);

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++)
	{
		int key;scanf("%d",&key);
		P1[i]=key;
	}
	for (int i=0;i<=m;i++)
	{
		int key;scanf("%d",&key);
		P2[i]=key;
	}

	int N,L=0;
	for (N=1;N<=(n+m+1);N<<=1) L++;
	for (int i=1;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) Wn[i]=complex<ld>(cos(2*Pi*i/N),sin(2*Pi*i/N)),Iwn[i]=conj(Wn[i]);

	for (int i=0;i<N;i++) cout<<Wn[i]<<" ";cout<<endl;
	FFT(P1,N,1);FFT(P2,N,1);
	for (int i=0;i<N;i++) P1[i]=P1[i]*P2[i];
	FFT(P1,N,-1);
	
	for (int i=0;i<=n+m;i++) printf("%d ",(int)(P1[i].real()/N+0.5));printf("\n");
	return 0;
}
void FFT(complex<ld> *P,int N,const int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int l=i<<1;
		complex<ld> dw(cos(Pi/i),sin(Pi/i)*opt);
		for (int j=0;j<N;j+=l)
		{
			complex<ld> w(1,0);
			for (int k=0;k<i;k++,w*=dw)
			{
				complex<ld> X=P[j+k],Y=w*P[j+k+i];
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
		}
	}
	return;
}
