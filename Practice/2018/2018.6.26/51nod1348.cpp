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

const int maxN=70100;
const int maxDepth=17;
const int Mod=100003;
const int M=(sqrt(Mod)+10);
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

int n,Q;
int Num[maxN];
ll PA[maxN],PB[maxN],DP[maxDepth][maxN];
Complex A[maxN],B[maxN],C[maxN],D[maxN],E[maxN],F[maxN],G[maxN],W[maxN];
int Rader[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
void Divide(int l,int r,int depth);
void FFT(Complex *P,int N,int opt);

int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=0;i<n;i++) scanf("%d",&Num[i]);
	Divide(0,n-1,0);
	//for (int i=0;i<=n;i++) cout<<DP[0][i]<<" ";cout<<endl;
	while (Q--)
	{
		int k;scanf("%d",&k);
		printf("%lld\n",DP[0][k]);
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

void Divide(int l,int r,int depth)
{
	if (l==r){
		DP[depth][1]=Num[l];DP[depth][0]=1;return;
	}
	int mid=(l+r)>>1,sz=r-l+1,lsz=mid-l+1,rsz=r-mid;
	for (int i=0;i<=sz;i++) DP[depth][i]=DP[depth+1][i]=0;
	Divide(l,mid,depth+1);
	for (int i=0;i<=lsz;i++) DP[depth][i]=DP[depth+1][i],DP[depth+1][i]=0;
	Divide(mid+1,r,depth+1);
	
	int N=1,L=0;
	for (N=1;N<=sz+1;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) W[i]=Complex(cos(2*Pi*i/N),sin(2*Pi*i/N));
	for (int i=0;i<N;i++) A[i]=B[i]=C[i]=D[i]=E[i]=F[i]=G[i]=Complex(0,0),PA[i]=PB[i]=0;
	
	int acnt=0;PA[0]=1;for (int i=1,j=l;j<=mid;i++,j++) PA[++acnt]=DP[depth][i];
	int bcnt=0;PB[0]=1;for (int i=1,j=mid+1;j<=r;i++,j++) PB[++bcnt]=DP[depth+1][i];
	for (int i=0;i<=acnt;i++) A[i].x=PA[i]/M,B[i].x=PA[i]%M;
	for (int i=0;i<=bcnt;i++) C[i].x=PB[i]/M,D[i].x=PB[i]%M;

	/*
	cout<<"Divide: ["<<l<<","<<r<<"] mid:"<<mid<<" N:"<<N<<" "<<lsz<<" "<<rsz<<endl;
	cout<<"PA:["<<acnt<<"] ";for (int i=0;i<N;i++) cout<<PA[i]<<" ";cout<<endl;
	cout<<"PB:["<<bcnt<<"] ";for (int i=0;i<N;i++) cout<<PB[i]<<" ";cout<<endl;
	cout<<"A:";for (int i=0;i<N;i++) cout<<A[i].x<<" ";cout<<endl;
	cout<<"B:";for (int i=0;i<N;i++) cout<<B[i].x<<" ";cout<<endl;
	cout<<"C:";for (int i=0;i<N;i++) cout<<C[i].x<<" ";cout<<endl;
	cout<<"D:";for (int i=0;i<N;i++) cout<<D[i].x<<" ";cout<<endl;
	//*/
	
	FFT(A,N,1);FFT(B,N,1);FFT(C,N,1);FFT(D,N,1);
	for (int i=0;i<N;i++)
	{
		E[i]=A[i]*C[i];
		F[i]=A[i]*D[i]+B[i]*C[i];
		G[i]=B[i]*D[i];
	}
	FFT(E,N,-1);FFT(F,N,-1);FFT(G,N,-1);
	//cout<<"E:";for (int i=0;i<N;i++) cout<<E[i].x<<" ";cout<<endl;
	//cout<<"F:";for (int i=0;i<N;i++) cout<<F[i].x<<" ";cout<<endl;
	//cout<<"G:";for (int i=0;i<N;i++) cout<<G[i].x<<" ";cout<<endl;
	for (int i=lsz+1;i<N;i++) DP[depth][i]=0;
	//for (int i=1;i<=lsz;i++) DP[depth][i]+=DP[depth+1][i];
	for (int i=1;i<N;i++)
	{
		DP[depth][i]=1ll*(ll)E[i].x*M%Mod*M%Mod;
		DP[depth][i]=1ll*(ll)(DP[depth][i]+1ll*(ll)F[i].x*M%Mod)%Mod;
		DP[depth][i]=1ll*(ll)(DP[depth][i]+G[i].x)%Mod;
	}
	//for (int i=0;i<=sz;i++) cout<<DP[depth][i]<<" ";cout<<endl;
	return;
}

void FFT(Complex *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
		for (int l=i<<1,j=0;j<N;j+=l)
			for (int k=0;k<i;k++)
			{
				Complex X=P[j+k],Y=P[j+k+i]*Complex(W[N/l*k].x,opt*W[N/l*k].y);
				P[j+k]=X+Y;P[j+k+i]=X-Y;
			}
	if (opt==-1) for (int i=0;i<N;i++) P[i].x=(ll)(P[i].x/N+0.5);
	return;
}
