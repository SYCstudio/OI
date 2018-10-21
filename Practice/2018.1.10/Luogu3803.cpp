#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2748577*2;
const ld Pi=acos(-1);
const int inf=2147483647;

int N,M,L;
complex<ld> A[maxN],B[maxN];
int Rev[maxN];
int Num[maxN];

int read();
void FFT(complex<ld> *P,int opt);

int main()
{
    scanf("%d%d",&N,&M);
    for (int i=0;i<=N;i++) A[i]=read();
    for (int i=0;i<=M;i++) B[i]=read();
    M=N+M;
    for (N=1;N<=M;N=N<<1) L++;
    for (int i=0;i<N;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));
    FFT(A,1);FFT(B,1);
    //for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
    //for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
    for (int i=0;i<=N;i++) A[i]=A[i]*B[i];
    FFT(A,-1);
    for (int i=0;i<=M;i++) printf("%d ",(int)(A[i].real()/N+0.5));
    printf("\n");
    return 0;
}

int read()
{
    char ch=getchar();int x=0;
    while ((ch>'9')||(ch<'0')) ch=getchar();
    while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
    return x;
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
    return;
}
