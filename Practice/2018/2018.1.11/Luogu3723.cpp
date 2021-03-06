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

const int maxN=270000;
const ld Pi=acos(-1);
const int inf=2147483647;

int n,m,N,M,L;
int A[maxN],B[maxN];
int Rev[maxN];
int maxxy;
complex<ld> F1[maxN],F2[maxN];

void GetXY();
void FFT(complex<ld> *P,int opt);

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&A[i]);
    for (int i=1;i<=n;i++) scanf("%d",&B[i]);
    int sx=0,sy=0,sx2=0,sy2=0;
    for (int i=1;i<=n;i++) sx+=A[i],sy+=B[i],sx2+=A[i]*A[i],sy2+=B[i]*B[i];
    GetXY();
    int Ans=inf;
    for (int c=-m;c<=m;c++)
		Ans=min(Ans,sx2+sy2+2*c*(sx-sy)+n*c*c-2*maxxy);
    printf("%d\n",Ans);
    return 0;
}

void GetXY()
{
    for (int i=0;i<n;i++) F1[i]=A[i+1];
    for (int i=0;i<n;i++) F2[i]=B[n-i];
    for (int i=n;i<2*n;i++) F2[i]=F2[i-n];
    M=n*3+1;
    for (N=1;N<=M;N=N<<1) L++;
    for (int i=1;i<N;i++) Rev[i]=(Rev[i>>1]>>1)|(i&1)<<(L-1);
    FFT(F1,1);FFT(F2,1);
    for (int i=0;i<N;i++) F1[i]=F1[i]*F2[i];
    FFT(F1,-1);
    //for (int i=n-1;i<2*n-1;i++) cout<<(ld)F1[i].real()/N<<" ";cout<<endl;
    maxxy=-inf;
    for (int i=n-1;i<2*n-1;i++) maxxy=max((ld)maxxy,(ld)F1[i].real()/N+0.5);
    //cout<<maxxy<<endl;
    //for (int i=1;i<=n;i++) cout<<Pxy[i]<<" ";cout<<endl;
    return;
}

void FFT(complex<ld> *P,int opt)
{
    for (int i=0;i<N;i++) if (i<Rev[i]) swap(P[i],P[Rev[i]]);
    for (int i=1;i<N;i=i<<1)
    {
		int dl=i<<1;
		complex<ld> dw(cos(Pi/i),opt*sin(Pi/i));
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
    return;
}
