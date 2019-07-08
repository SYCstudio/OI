#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define sqr(x) ((x)*(x))

class Point
{
public:
	double x,y,agl;
	double len()
	{
		return sqrt(sqr(x)+sqr(y));
	}
};

const int maxN=3010;
const double eps=1e-8;
const double Pi=acos(-1);

int n;
Point P[maxN];
double Agl[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
double C(double n,double m);

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%lf%lf",&P[i].x,&P[i].y);
	double cnt=0;
	for (int i=1; i<=n; i++) {
		int scnt=0;
		double sum=0;
		for (int j=1; j<=n; j++) if (i!=j) Agl[++scnt]=atan2((P[j]-P[i]).y,(P[j]-P[i]).x);
		sort(&Agl[1],&Agl[scnt+1]);
		for (int i=1; i<=scnt; i++) Agl[i+scnt]=Agl[i]+Pi*2;
		for (int i=1,j=1; i<=scnt; i++) {
			while (j+1<=scnt+scnt&&Agl[j+1]<Agl[i]+Pi) ++j;
			sum+=C(j-i,2);
		}
		cnt+=C(scnt,3)-sum;
	}
	printf("%.6lf\n",(cnt+(C(n,4)-cnt)*2)/C(n,3)+3);
	return 0;
}
Point operator + (Point A,Point B)
{
	return ((Point) {
		A.x+B.x,A.y+B.y
	});
}
Point operator - (Point A,Point B)
{
	return ((Point) {
		A.x-B.x,A.y-B.y
	});
}
double C(double n,double m)
{
	if (n<m) return 0;
	if (m==1) return n;
	if (m==2) return n*(n-1)/2;
	if (m==3) return n*(n-1)*(n-2)/6;
	if (m==4) return n*(n-1)*(n-2)*(n-3)/24;
}