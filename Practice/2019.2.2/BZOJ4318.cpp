#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ld long double
#define f128 __float128
#define p2(x) ((x)*(x))
#define p3(x) ((x)*(x)*(x))

const int maxN=1010000;

int n;
//ld P[maxN];
//f128 F[maxN],G[maxN];
ld f1[maxN],f2[maxN],Ans[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		ld p;
		scanf("%LF",&p);
		f1[i]=(f1[i-1]+1)*p;
		f2[i]=(f2[i-1]+2*f1[i-1]+1)*p;
		Ans[i]=Ans[i-1]+(3*f1[i-1]+3*f2[i-1]+1)*p;
	}
	/*
	for (int i=1;i<=n;i++) scanf("%LF",&P[i]);
	f128 f=0,g0=1,g1=0,g2=0,g3=0;
	for (int i=1;i<=n+1;i++){
	f128 np=1-P[i];
	F[i]=np*(f+p3(i-1)*g0-p2(i-1)*3*g1+(i-1)*3.0*g2-g3);
	G[i]=np*g0;
	f=f*P[i]+F[i];
	g0=g0*P[i]+G[i];
	g1=g1*P[i]+G[i]*i;
	g2=g2*P[i]+G[i]*p2(i);
	g3=g3*P[i]+G[i]*p3(i);
	//cout<<i<<" "<<f<<" "<<g0<<" "<<g1<<" "<<g2<<" "<<g3<<endl;
	}
	//*/
	/*
	G[0]=1;
	for (int i=1;i<=n+1;i++){
	ld p=1-P[i];
	for (int j=i-1;j>=0;j--){
	    F[i]=F[i]+F[j]*p+sss(i-j-1)*G[j]*p;
	    G[i]=G[i]+G[j]*p;
	    p=p*P[j];
	}
	}
	//*/
	// for (int i=0;i<=10000;i++) cout<<F[i]<<" ";cout<<endl;
	printf("%.1LF\n",Ans[n]);
	return 0;
}
