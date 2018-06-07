#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long
#define ld long double

const int maxN=66555*2;
const ld Pi=acos(-1);
const int inf=2147483647;

int N,M,L;
complex<ld> A[maxN],B[maxN];
int Rev[maxN];
int Num[maxN];

int readnum();
void FFT(complex<ld> *Arr,int opt);

int main()
{
    scanf("%d",&N);
    for (int i=N-1;i>=0;i--) A[i]=readnum();
    for (int i=N-1;i>=0;i--) B[i]=readnum();
    M=N+N;
    for (N=1;N<=M;N=N<<1) L++;//把数补成2^L长，即N长，但其实其中的有效位数只有M位
    for (int i=0;i<N;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));//预处理Rader排序
    //cout<<N<<" "<<M<<" "<<L<<endl;
    FFT(A,1);FFT(B,1);
    for (int i=0;i<N;i++) A[i]=A[i]*B[i];
    FFT(A,-1);
    for (int i=0;i<N;i++) Num[i]=(A[i].real()/N+0.5);
    for (int i=0;i<N;i++) Num[i+1]+=Num[i]/10,Num[i]%=10;
    while (Num[N]==0) N--;
    for (int i=N;i>=0;i--) printf("%d",Num[i]);
    printf("\n");
    return 0;
}

int readnum()
{
    char ch=getchar();
    while ((ch>'9')||(ch<'0')) ch=getchar();
    return ch-'0';
}

void FFT(complex<ld> *Arr,int opt)
{
    for (int i=0;i<N;i++) if (i<Rev[i]) swap(Arr[i],Arr[Rev[i]]);
    for (int i=1;i<N;i=i<<1)//枚举现在合并到哪一层
    {
		complex<ld> dw(cos(Pi/i),opt*sin(Pi/i));//求得每次乘上的旋转因子
		int dl=i<<1;//dl即为当前层中，一组的长度
		for (int j=0;j<N;j=j+dl)
		{
			complex<ld> w0(1,0);//起始根
			for (int k=0;k<i;k++,w0=w0*dw)
			{
				complex<ld> X=Arr[j+k],Y=w0*Arr[j+k+i];
				Arr[j+k]=X+Y;Arr[j+k+i]=X-Y;
			}
		}
    }
    return;
}
