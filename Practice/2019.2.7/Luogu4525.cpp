#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const double eps=1e-8;

double a,b,c,d;

double Calc(double x);
double Inte(double l,double r);
double Simpson(double l,double r);

int main()
{
	double L,R;
	scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&L,&R);
	printf("%.6lf\n",Simpson(L,R));
	return 0;
}

double Calc(double x)
{
	return (c*x+d)/(a*x+b);
}
double Inte(double l,double r)
{
	return (r-l)*(Calc(l)+Calc(r)+4*Calc((l+r)/2))/6;
}
double Simpson(double l,double r)
{
	double mid=(l+r)/2,k=Inte(l,r),kl=Inte(l,mid),kr=Inte(mid,r);
	if (fabs(kl+kr-k)<eps) return kl+kr;
	return Simpson(l,mid)+Simpson(mid,r);
}