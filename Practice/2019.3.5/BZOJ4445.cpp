#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define sqr(x) ((x)*(x))
#define double long double
const int maxN=101000<<1;
const double eps=1e-15;

class Point
{
public:
	double x,y;
	Point() {}
	Point(double _x,double _y)
	{
		x=_x;
		y=_y;
		return;
	}
	double len()
	{
		return sqrt(sqr(x)+sqr(y));
	}
};
class Line
{
public:
	Point p,f;
	double agl;
	void I()
	{
		agl=atan2(f.y,f.x);
	}
};

int n;
Point I[maxN],Q2[maxN];
Line L[maxN],Q1[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (double a,Point A);
ostream & operator << (ostream & os,Point A);
double Cross(Point A,Point B);
bool lcmp(Line A,Line B);
Point Intersection(Line A,Line B);
bool Isleft(Line A,Point B);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%LF%LF",&I[i].x,&I[i].y);
	double Area=0;
	for (int i=2; i<n; i++) Area+=fabs(Cross(I[i]-I[1],I[i+1]-I[1]));
	Area/=2.0;
	I[n+1]=I[1];
	for (int i=1; i<=n; i++) L[i]=((Line) {
		I[i],I[i+1]-I[i]
	});
	int lcnt=n;
	for (int i=2; i<=n; i++) {
		double kx=I[1].y-I[2].y-I[i].y+I[i+1].y;
		double b=I[1].x*I[2].y-I[2].x*I[1].y-I[i].x*I[i+1].y+I[i+1].x*I[i].y;
		double ky=I[i+1].x-I[i].x-I[2].x+I[1].x;
		//printf("%.15LF %.15LF %.15LF\n",kx,b,ky);
		if (fabs(ky)<eps) L[++lcnt]=((Line) {
			((Point) {
				-b/kx,0
			}),((Point) {
				0,kx
			})
		});
		else L[++lcnt]=((Line) {
			((Point) {
				0,b/ky
			}),((Point) {
				ky,kx
			})
		});
	}
	for (int i=1; i<=lcnt; i++) L[i].I();
	sort(&L[1],&L[lcnt+1],lcmp);
	int ql=1,qr=1;
	Q1[1]=L[1];
	for (int i=2; i<=lcnt; i++) {
		while (ql<qr&&!Isleft(L[i],Q2[qr-1])) --qr;
		while (ql<qr&&!Isleft(L[i],Q2[ql])) ++ql;
		Q1[++qr]=L[i];
		if (fabs(Cross(Q1[qr].f,Q1[qr-1].f))<0) {
			--qr;
			if (Isleft(L[i],Q1[qr].p)) Q1[qr]=L[i];
		}
		if (ql<qr) Q2[qr-1]=Intersection(Q1[qr],Q1[qr-1]);
		//cout<<"After Insert:"<<L[i].p<<" "<<L[i].f<<endl;
		//for (int j=ql;j<qr;j++) cout<<Q2[j]<<" ";cout<<endl;
	}
	while (ql<qr&&!Isleft(Q1[ql],Q2[qr-1])) --qr;
	Q2[qr]=Intersection(Q1[ql],Q1[qr]);
	double sum=0;
	for (int i=ql+1; i<qr; i++) sum+=fabs(Cross(Q2[i]-Q2[ql],Q2[i+1]-Q2[ql]));
	sum/=2.0;
	//cout<<Area<<" "<<sum<<endl;
	//for (int i=1;i<=n;i++) cout<<I[i]<<" ";cout<<endl;
	//for (int i=ql;i<=qr;i++) cout<<Q2[i]<<" ";cout<<endl;
	printf("%.4LF\n",sum/Area);
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
Point operator * (double a,Point A)
{
	return ((Point) {
		A.x*a,A.y*a
	});
}
ostream & operator << (ostream & os,Point A)
{
	os<<"("<<A.x<<","<<A.y<<")";
	return os;
}
double Cross(Point A,Point B)
{
	return A.x*B.y-A.y*B.x;
}
bool lcmp(Line A,Line B)
{
	return A.agl<B.agl;
}
Point Intersection(Line A,Line B)
{
	return A.p+Cross(B.f,A.p-B.p)/Cross(A.f,B.f)*A.f;
}
bool Isleft(Line A,Point B)
{
	return Cross(A.f,B-A.p)>0;
}