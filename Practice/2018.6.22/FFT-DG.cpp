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

const int maxN=10000;
const int N=maxN;
const ld Pi=acos(-1);
const int inf=2147483647;

int A[maxN],B[maxN];
complex<ld> P1[maxN],P2[maxN];

void FFT(complex<ld> *P,int len,int opt);
//void fft(complex<ld>  *a, int n, bool inv);

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d",&A[i]);
	for (int i=0;i<m;i++) scanf("%d",&B[i]);
	for (int i=0;i<n;i++) P1[i]=A[i];
	for (int i=0;i<m;i++) P2[i]=B[i];
	int N;
	for (N=1;N<n+m;N<<=1);
	cout<<"N:"<<N<<endl;
	cout<<"Before:"<<endl;
	for (int i=0;i<N;i++) cout<<P1[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) cout<<P2[i]<<" ";cout<<endl;
	
	FFT(P1,N,1);FFT(P2,N,1);
	
	//fft(P1,N,0);fft(P2,N,0);
	cout<<"After DFT:"<<endl;
	for (int i=0;i<N;i++) cout<<P1[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) cout<<P2[i]<<" ";cout<<endl;
	for (int i=0;i<N;i++) P1[i]=P1[i]*P2[i];
	
	FFT(P1,N,-1);
	
	//fft(P1,N,1);
	cout<<"After IDFT:"<<endl;
	for (int i=0;i<N;i++) cout<<P1[i]<<" ";cout<<endl;
	for (int i=0;i<n+m;i++) cout<<(int)(P1[i].real()/N+0.5)<<" ";cout<<endl;
	
	return 0;
}

void FFT(complex<ld> *P,int len,int opt)
{
	if (len==1) return;
	complex<ld> Bp[maxN];
	int mid=len/2;
	for (int i=0;i<mid;i++){
		Bp[i]=P[i*2];Bp[i+mid]=P[i*2+1];
	}
	for (int i=0;i<len;i++) P[i]=Bp[i];
	FFT(P,mid,opt);FFT(P+mid,mid,opt);
	complex<ld> dw(cos(2*Pi/len),sin(2*Pi/len)*opt),w(1,0);
	for (int i=0;i<mid;i++,w*=dw)
	{
		Bp[i]=P[i]+w*P[i+mid];
		Bp[i+mid]=P[i]-w*P[i+mid];
	}
	for (int i=0;i<len;i++) P[i]=Bp[i];
	return;
}
//*/
/*
void fft(complex<ld>  *a, int n, bool inv){
    if(n == 1) return;
    static complex<ld> buf[N];
    int m = n / 2;
    for(int i = 0; i < m; i++){
        buf[i] = a[2 * i];
        buf[i + m] = a[2 * i + 1];
    }
    for(int i = 0; i < n; i++)
        a[i] = buf[i];
    fft(a, m, inv); 
    fft(a + m, m, inv);
    for(int i = 0; i < m; i++){
        complex<ld> x = omega(n, i);
        if(inv) x = conj(x);
        buf[i] = a[i] + x * a[i + m]; 
        buf[i + m] = a[i] - x * a[i + m];
    }
    for(int i = 0; i < n; i++)
        a[i] = buf[i];
}
//*/
