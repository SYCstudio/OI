#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cassert>
using namespace std;

#define double long double
#define ft first
#define sd second
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
		return sqrt(x*x+y*y);
	}
	double angle()
	{
		return atan2(y,x);
	}
};

const int maxN=310;
const double INF=1e18;
const double eps=1e-10;
const Point FAR(141*10,937*10);
const Point O(0,0);

int n,S;
Point P[maxN],T[4];
pair<double,double> Dst[maxN][maxN],G[10][10];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,double B);
ostream & operator << (ostream & os,Point A);
double Cross(Point A,Point B);
double Dot(Point A,Point B);
bool same(double x,double y);
bool check(Point A,Point B);
bool Intersection(Point A,Point B,Point C,Point D);
Point Near(Point A,Point L1,Point L2);
void Path(int u,int v,Point S,Point T,Point A,Point B);
pair<double,double> Calc(int u,int v);
int main()
{
	scanf("%d%d",&n,&S);
	for (int i=1; i<=n; i++) scanf("%LF%LF%LF%LF",&P[i].x,&P[i].y,&P[n+i].x,&P[n+i].y);
	T[0]=((Point) {
		S,S
	});
	T[1]=((Point) {
		-S,S
	});
	T[2]=((Point) {
		-S,-S
	});
	T[3]=((Point) {
		S,-S
	});

	for (int i=1; i<=n; i++) for (int j=i; j<=n; j++) Dst[i][j]=Dst[j][i]=Calc(i,j);

	for (int k=1; k<=n; k++)
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++) {
				Dst[i][j].ft=min(Dst[i][j].ft,Dst[i][k].ft+Dst[k][j].sd);
				Dst[i][j].ft=min(Dst[i][j].ft,Dst[i][k].sd+Dst[k][j].ft);
				Dst[i][j].sd=min(Dst[i][j].sd,Dst[i][k].ft+Dst[k][j].ft);
				Dst[i][j].sd=min(Dst[i][j].sd,Dst[i][k].sd+Dst[k][j].sd);
			}

	double Ans=S*8;
	for (int i=1; i<=n; i++) Ans=min(Ans,Dst[i][i].ft+Dst[i][i].sd);
	printf("%.10LF\n",Ans);
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
Point operator * (Point A,double B)
{
	return ((Point) {
		A.x*B,A.y*B
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
double Dot(Point A,Point B)
{
	return A.x*B.x+A.y*B.y;
}
bool same(double x,double y)
{
	return fabs(x-y)<eps;
}
bool check(Point A,Point B)
{
	for (int i=0; i<=3; i++) for (int j=i+1; j<=3; j++) if (Intersection(A,B,T[i],T[j])) return 0;
	return 1;
}
bool Intersection(Point A,Point B,Point C,Point D)
{
	return (Cross(B-C,D-C)*Cross(A-C,D-C)<0)&&(Cross(C-A,B-A)*Cross(D-A,B-A)<0);
}
Point Near(Point A,Point L1,Point L2)
{
	double l=(L2-L1).len(),t=Dot(L2-L1,A-L1)/l;
	if (t<-eps) return L1;
	if (t>l) return L2;
	return L1+(L2-L1)*(t/l);
}
void Path(int u,int v,Point S,Point T,Point A,Point B)
{
	if (!check(A,B)) return;
	double len=(A-B).len();
	if (Intersection(O,FAR,S,A)^Intersection(O,FAR,A,B)^Intersection(O,FAR,B,T))
		G[u][v].ft=G[v][u].ft=min(G[u][v].ft,len);
	else G[u][v].sd=G[v][u].sd=min(G[u][v].sd,len);
	return;
}
pair<double,double> Calc(int u,int v)
{
	for (int i=1; i<=6; i++) for (int j=1; j<=6; j++) G[i][j]=make_pair(INF,INF);
	for (int i=0; i<=1; i++) for (int j=0; j<=1; j++) Path(1,2,P[u],P[v],P[u+i*n],P[v+j*n]);
	Path(1,2,P[u],P[v],P[u],Near(P[u],P[v],P[v+n]));
	Path(1,2,P[u],P[v],P[u+n],Near(P[u+n],P[v],P[v+n]));
	Path(1,2,P[u],P[v],Near(P[v],P[u],P[u+n]),P[v]);
	Path(1,2,P[u],P[v],Near(P[v+n],P[u],P[u+n]),P[v+n]);
	for (int i=0; i<=3; i++) {
		Path(1,i+3,P[u],T[i],P[u],T[i]);
		Path(1,i+3,P[u],T[i],P[u+n],T[i]);
		Path(1,i+3,P[u],T[i],Near(T[i],P[u],P[u+n]),T[i]);
	}

	for (int i=0; i<=3; i++) {
		Path(2,i+3,P[v],T[i],P[v],T[i]);
		Path(2,i+3,P[v],T[i],P[v+n],T[i]);
		Path(2,i+3,P[v],T[i],Near(T[i],P[v],P[v+n]),T[i]);
	}
	Path(3,4,T[0],T[1],T[0],T[1]);
	Path(4,5,T[1],T[2],T[1],T[2]);
	Path(5,6,T[2],T[3],T[2],T[3]);
	Path(6,3,T[3],T[0],T[3],T[0]);
	for (int k=1; k<=6; k++)
		for (int i=1; i<=6; i++)
			for (int j=1; j<=6; j++) {
				G[i][j].ft=min(G[i][j].ft,G[i][k].ft+G[k][j].sd);
				G[i][j].ft=min(G[i][j].ft,G[i][k].sd+G[k][j].ft);
				G[i][j].sd=min(G[i][j].sd,G[i][k].ft+G[k][j].ft);
				G[i][j].sd=min(G[i][j].sd,G[i][k].sd+G[k][j].sd);
			}
	return G[1][2];
}
