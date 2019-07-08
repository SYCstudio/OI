#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

int X,Y;

namespace brute
{
const int maxN=40400;
double F[2][maxN];
int main();
}
namespace Simpson
{
const double Pi=acos(-1);
const double eps=1e-15;
double sigma,mu;
int main();
double Calc(double p);
double Inte(double l,double r);
double Simpson(double l,double r);
}

int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d%d",&X,&Y);
		if (Y<=1600) brute::main();
		else Simpson::main();
	}
	return 0;
}

namespace brute
{
int main()
{
	mem(F,0);
	int now=1;
	for (int i=0; i<=(X-1)*Y; i++) F[now][i]=1;
	for (int i=1; i<=Y; i++) {
		now^=1;
		mem(F[now],0);
		for (int j=0; j<=i*(X-1); j++) {
			/*
			for (int k=0;k<X;k++)
			    F[now][j+k]+=F[now^1][j]/X;
			//*/

			double f=F[now^1][min(j,(i-1)*(X-1))];
			if (j>=(int)X) f-=F[now^1][min(j-X,(i-1)*(X-1))];
			f=f/X;
			F[now][j]=f+((j>0)?(F[now][j-1]):0);
			//*/
		}
		//for (int j=0;j<=i*(X-1);j++) cout<<F[now][j]<<" ";cout<<endl;
	}
	//for (int i=1;i<=(X-1)*Y;i++) F[now][i]+=F[now][i-1];
	for (int ti=1; ti<=10; ti++) {
		int A,B;
		scanf("%d%d",&A,&B);
		printf("%.12lf\n",F[now][B]-((A>=1)?F[now][A-1]:0));
	}
	return 0;
}
}
namespace Simpson
{
int main()
{
	mu=(double)(X-1)/2.0*Y;
	sigma=sqrt((double)(sqr(X)-1)/12.0*Y);
	for (int ti=1; ti<=10; ti++) {
		int A,B;
		scanf("%d%d",&A,&B);
		double l=max((double)A,mu-sigma*3),r=min((double)B,mu+sigma*3);
		if (l<=r) printf("%.12lf\n",Simpson(l,r));
		else printf("%.12lf\n",0.0);
	}
	return 0;
}
double Calc(double x)
{
	return exp(-sqr(x-mu)/2/sqr(sigma))/sigma/sqrt(Pi*2.0);
}
double Inte(double l,double r)
{
	return (r-l)*(Calc(l)+Calc(r)+Calc((l+r)/2)*4)/6;
}
double Simpson(double l,double r)
{
	double mid=(l+r)/2,k=Inte(l,r),kl=Inte(l,mid),kr=Inte(mid,r);
	if (fabs(kl+kr-k)<eps) return kl+kr;
	return Simpson(l,mid)+Simpson(mid,r);
}
}