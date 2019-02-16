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

const int maxN=300010;
const ld Pi=acos(-1);
const int inf=2147483647;

int n,N,M,L;
ld Q[maxN];
int Rev[maxN];
complex<ld> A1[maxN],A2[maxN],B[maxN];

void FFT(complex<ld> *P,int opt);

int main()
{
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%LF",&Q[i]);
    for (int i=0;i<n;i++) A1[i]=Q[i+1],A2[i]=Q[n-i],B[i+1]=(ld)1.0/(i+1)/(i+1);
    M=n+n+1;
    for (L=0,N=1;N<=M;N=N<<1) L++;
    for (int i=0;i<N;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));
    FFT(A1,1);FFT(A2,1);FFT(B,1);
    for (int i=0;i<N;i++) A1[i]=A1[i]*B[i],A2[i]=A2[i]*B[i];
    FFT(A1,-1);FFT(A2,-1);
    //for (int i=0;i<n;i++) printf("%LF ",(ld)A1[i].real()/N);printf("\n");
    //for (int i=0;i<n;i++) printf("%LF ",(ld)A2[i].real()/N);printf("\n");
    for (int i=0;i<n;i++) printf("%.3LF\n",(ld)A1[i].real()/N-(ld)A2[n-i-1].real()/N);
    printf("\n");
    return 0;
}

void FFT(complex<ld> *P,int opt)
{
    for (int i=0;i<N;i++) if (i<Rev[i]) swap(P[i],P[Rev[i]]);
    for (int i=1;i<N;i=i<<1)
    {
	complex<ld> dw(cos(Pi/i),opt*sin(Pi/i));
	int dl=i<<1;
	for (int j=0;j<N;j=j+dl)
	{
	    complex<ld> w0(1,0);
	    for (int k=0;k<i;k++,w0=w0*dw)
	    {
		complex<ld> X=P[j+k],Y=w0*P[j+k+i];
		P[j+k]=X+Y;P[j+k+i]=X-Y;
	    }
	}
    }
    //if (opt==-1) for (int i=0;i<N;i++) P[i]=P[i].real()/N;
    return;
}
