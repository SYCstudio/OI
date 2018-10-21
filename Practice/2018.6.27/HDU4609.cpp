#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=400100*2;
const ld Pi=acos(-1);
const int inf=2147483647;

class Complex
{
public:
	ld x,y;
	Complex(){};
	Complex(ld a,ld b){
		x=a;y=b;return;
	}
};

int n;
ll Cnt[maxN],Num[maxN],Sum[maxN];
int Len[maxN],Rader[maxN];
Complex A[maxN],Wn[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
void FFT(Complex *P,int N,int opt);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		scanf("%d",&n);mem(Cnt,0);mem(Num,0);
		for (int i=0;i<n;i++)
		{
			scanf("%d",&Len[i]);
			Cnt[Len[i]]++;
		}
		sort(&Len[0],&Len[n]);
		int N=1,L=0;
		for (N=1;N<=Len[n-1]+Len[n-1];N<<=1) L++;
		for (int i=0;i<N;i++) A[i]=Complex(Cnt[i],0);
		for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
		for (int i=0;i<N;i++) Wn[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));

		//for (int i=0;i<N;i++) cout<<A[i].x<<" ";cout<<endl;

		FFT(A,N,1);
		for (int i=0;i<N;i++) A[i]=A[i]*A[i];
		FFT(A,N,-1);

		//for (int i=0;i<N;i++) cout<<A[i].x<<" ";cout<<endl;

		for (int i=0;i<N;i++) Num[i]=(ll)(A[i].x);
		for (int i=0;i<n;i++) Num[Len[i]+Len[i]]--;
		for (int i=1;i<=Len[n-1]+Len[n-1];i++) Num[i]/=2;

		//for (int i=0;i<N;i++) cout<<Num[i]<<" ";cout<<endl;
		Sum[0]=0;
		for (int i=1;i<=Len[n-1]+Len[n-1];i++) Sum[i]=Sum[i-1]+Num[i];
		//for (int i=0;i<=mxkey*2;i++) cout<<Sum[i]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<Len[i]<<" ";cout<<endl;

		ll Ans=0;
		for (int i=0;i<n;i++)
		{
			//cout<<i<<":";
			ll cnt=Sum[Len[n-1]+Len[n-1]]-Sum[Len[i]];//cout<<cnt<<" ";
			cnt=cnt-1ll*(ll)i*(ll)(n-i-1);//cout<<cnt<<" ";
			cnt=cnt-(ll)(n-1);//cout<<cnt<<" ";
			cnt=cnt-1ll*(ll)(n-i-1)*(ll)(n-i-2)/2ll;//cout<<cnt<<" ";
			//cout<<cnt<<endl;
			Ans=Ans+cnt;
		}

		//cout<<"Ans:"<<Ans<<endl;
		ll cnt=1ll*(ll)n*(ll)(n-1)*(ll)(n-2)/(ll)6;

		printf("%.7lf\n",(ld)Ans/(ld)cnt);
	}
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
		for (int l=i<<1,j=0;j<N;j+=l)
			for (int k=0;k<i;k++)
			{
				Complex X=P[j+k],Y=Complex(Wn[N/l*k].x,Wn[N/l*k].y*opt)*P[j+k+i];
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
	if (opt==-1) for (int i=0;i<N;i++) P[i].x=(ll)(P[i].x/N+0.5);
	return;
}
