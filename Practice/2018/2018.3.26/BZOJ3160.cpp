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

const int maxN=200100*4;
const ld Pi=acos(-1);
const int Mod=1e9+7;
const int inf=2147483647;

int N,L;
char str[maxN],str2[maxN];
complex<ld> A[maxN],B[maxN];
ll F[maxN],Rev[maxN],Bin[maxN],H[maxN];

void FFT(complex<ld> *P,int opt);
ll Manacher();

int main()
{
	ios::sync_with_stdio(false);
	cin>>str;
	int len=strlen(str);
	
	for (N=1;N<=len*2+1;N=N<<1) L++;
	for (int i=0;i<N;i++) Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(L-1));//Rader排序
	
	for (int i=0;i<len;i++) A[i]=str[i]=='a',B[i]=str[i]=='b';
	//for (int i=0;i<len;i++) cout<<A[i];cout<<endl;
	//for (int i=0;i<len;i++) cout<<B[i];cout<<endl;
	FFT(A,1);FFT(B,1);
	for (int i=0;i<N;i++) A[i]=A[i]*A[i],B[i]=B[i]*B[i];
	for (int i=0;i<N;i++) A[i]=A[i]+B[i];
	FFT(A,-1);//FFT(B,-1);
	//cout<<"A:"<<endl;
	//for (int i=0;i<N;i++) cout<<(ll)((A[i].real()+0.5)/N);cout<<endl;
	//for (int i=0;i<N;i++) cout<<(ll)((B[i].real()+0.5)/N);cout<<endl;
	//for (int i=0;i<N;i++) A[i]=A[i]+B[i];
	for (int i=2;i<2*len+1;i++) F[i]=(ll)((A[i-2].real()+0.5)/N+1)>>1;
	//cout<<"F:"<<endl;
	//for (int i=0;i<2*len+1;i++) cout<<F[i];cout<<endl;

	ll Ans=0;
	Bin[0]=1;for (int i=1;i<2*len+1;i++) Bin[i]=(Bin[i-1]<<1)%Mod;
	for (int i=0;i<2*len+1;i++) Ans=(Ans+Bin[F[i]]-1)%Mod;
	//cout<<"Ans:"<<Ans<<endl;

	printf("%lld\n",(Ans+Mod-Manacher())%Mod);
}

void FFT(complex<ld> *P,int opt)
{
	for (int i=0;i<N;i++) if (i<Rev[i]) swap(P[i],P[Rev[i]]);
	for (int i=1;i<N;i=i<<1)
	{
		int dl=i<<1;
		complex<ld> dw(cos((ld)Pi/(ld)i),(ld)opt*sin(Pi/(ld)i));
		for (int j=0;j<N;j=j+dl)
		{
			complex<ld> w(1,0);
			for (int k=0;k<i;k++,w=w*dw)
			{
				complex<ld> X=P[j+k],Y=w*P[j+k+i];
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
		}
	}
	return;
}

ll Manacher()
{
	int l=1;str2[0]='$';str2[1]='#';
	int len=strlen(str);
	for (int i=0;i<len;i++){
		str2[++l]=str[i];str2[++l]='#';
	}
	ll id=0,mx=0;
	for (int i=0;i<=l;i++)
	{
		if (i<=mx) H[i]=min(H[id*2-i],mx-i);
		else H[i]=1;
		while (str2[i+H[i]]==str2[i-H[i]]) H[i]++;
		if (i+H[i]>mx){
			mx=i+H[i];id=i;
		}
	}
	//for (int i=0;i<=l;i++) cout<<str2[i];cout<<endl;
	//for (int i=0;i<=l;i++) cout<<H[i];cout<<endl;
	ll sum=0;
	for (int i=0;i<=l;i++) sum=(sum+(ll)H[i]/2)%Mod;
	//cout<<sum<<endl;
	return sum;
}
