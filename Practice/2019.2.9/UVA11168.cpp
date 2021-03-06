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
	double x,y;
	double len()
	{
		return sqrt(sqr(x)+sqr(y));
	}
};

const int maxN=10100;
const double eps=1e-10;
const double inf=1e18;

int n;
Point P[maxN],Bp[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream &os,Point A);
bool cmpc(Point A,Point B);
double Cross(Point A,Point B);

int main()
{
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	int Case;
	scanf("%d",&Case);
	for (int ci=1; ci<=Case; ci++) {
		scanf("%d",&n);
		double sumx=0,sumy=0;
		for (int i=1; i<=n; i++) scanf("%lf%lf",&P[i].x,&P[i].y),sumx+=P[i].x,sumy+=P[i].y;
		Point base=P[1];
		for (int i=2; i<=n; i++) if (P[i].y<base.y||(fabs(P[i].y-base.y)<eps&&P[i].x<base.x)) base=P[i];
		for (int i=1; i<=n; i++) P[i]=P[i]-base;
		sort(&P[1],&P[n+1],cmpc);
		int top=0;
		for (int i=1; i<=n; i++) {
			while (top>=2&&Cross(P[i]-Bp[top-1],Bp[top]-Bp[top-1])+eps>=0) --top;
			Bp[++top]=P[i];
			//cout<<"after:"<<i<<endl;for (int j=1;j<=top;j++) cout<<Bp[j]<<" ";cout<<endl;
		}
		for (int i=1; i<=top; i++) Bp[i]=Bp[i]+base;

		//for (int i=1;i<=top;i++) cout<<Bp[i]<<" ";cout<<endl;

		Bp[top+1]=Bp[1];
		double Ans=inf;
		for (int i=1; i<=top; i++) {
			double A,B,C;
			if (fabs(Bp[i].x-Bp[i+1].x)<eps) {
				A=1;
				B=0;
				C=-Bp[i].x;
			} else {
				A=(Bp[i].y-Bp[i+1].y)/(Bp[i].x-Bp[i+1].x);
				B=-1;
				C=Bp[i].y-A*Bp[i].x;
			}
			//cout<<Bp[i]<<" "<<Bp[i+1]<<" "<<A<<"x+"<<B<<"y+"<<C<<"=0"<<endl;
			Ans=min(Ans,fabs(A*sumx+B*sumy+C*n)/sqrt(sqr(A)+sqr(B)));
		}
		Ans=Ans/n;
		printf("Case #%d: %.3lf\n",ci,Ans);
	}
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
ostream & operator << (ostream &os,Point A)
{
	os<<"("<<A.x<<","<<A.y<<")";
	return os;
}
bool cmpc(Point A,Point B)
{
	return Cross(A,B)>0||(fabs(Cross(A,B))<eps&&A.len()<B.len());
}
double Cross(Point A,Point B)
{
	return A.x*B.y-A.y*B.x;
}
/*
4
4
0 0
0 1
1 0
1 1
2
15035 39572
34582 39535
3
0 0
0 1
1 0
5
0 0
0 2
2 0
2 2
1 1
//*/
