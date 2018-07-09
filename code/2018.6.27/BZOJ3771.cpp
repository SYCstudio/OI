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

const int maxN=40010*4;
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
int Val[maxN],Rader[maxN];
ll Ans[maxN],Cnt[maxN];
Complex Wn[maxN],A[maxN],B1[maxN],B2[maxN],B3[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
void FFT(Complex *P,int N,int opt);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]),Ans[Val[i]]++,Cnt[Val[i]]++;
	sort(&Val[1],&Val[n+1]);

	//两组合
	for (int i=1;i<=Val[n];i++) A[i]=Complex(Cnt[i],0);
	int N=1,L=0;
	for (N=1;N<=Val[n]+Val[n];N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) Wn[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));
	FFT(A,N,1);
	for (int i=0;i<N;i++) A[i]=A[i]*A[i];
	FFT(A,N,-1);
	for (int i=1;i<=n;i++) A[Val[i]+Val[i]].x-=1.0;
	for (int i=1;i<=Val[n]+Val[n];i++) A[i].x/=2;
	//cout<<"2:"<<endl;for (int i=0;i<N;i++) cout<<A[i].x<<" ";cout<<endl;
	for (int i=0;i<N;i++) Ans[i]=Ans[i]+(ll)A[i].x;

	//三组合
	for (int i=1;i<=n;i++) B1[Val[i]].x+=1.0,B2[Val[i]+Val[i]].x+=1.0;
	L=0;
	for (N=1;N<=Val[n]+Val[n]+Val[n];N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) Wn[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));
	FFT(B1,N,1);FFT(B2,N,1);
	for (int i=0;i<N;i++) B2[i]=B2[i]*B1[i];
	for (int i=0;i<N;i++) B1[i]=B1[i]*B1[i]*B1[i];
	FFT(B1,N,-1);FFT(B2,N,-1);
	//cout<<"After FFT:[B2]"<<endl;for (int i=0;i<N;i++) cout<<B2[i].x<<" ";cout<<endl;
	for (int i=1;i<=n;i++) B2[Val[i]+Val[i]+Val[i]].x-=1.0;
	//cout<<"After FFT:[B1]"<<endl;for (int i=0;i<N;i++) cout<<B1[i].x<<" ";cout<<endl;
	for (int i=1;i<=n;i++) B1[Val[i]+Val[i]+Val[i]].x-=1.0;
	//cout<<"After -Val[i]*3:[B1]"<<endl;for (int i=0;i<N;i++) cout<<B1[i].x<<" ";cout<<endl;
	for (int i=0;i<N;i++) B1[i].x-=B2[i].x*3.0;
	//cout<<"After -B2*3.0:[B1]"<<endl;for (int i=0;i<N;i++) cout<<B1[i].x<<" ";cout<<endl;
	for (int i=0;i<N;i++) B1[i].x/=6;
	//cout<<"After /6:[B1]"<<endl;for (int i=0;i<N;i++) cout<<B1[i].x<<" ";cout<<endl;
	for (int i=0;i<N;i++) Ans[i]=Ans[i]+(ll)B1[i].x;

	for (int i=0;i<N;i++) if (Ans[i]!=0) printf("%d %lld\n",i,Ans[i]);
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
