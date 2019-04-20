#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

class Point{
public:
    double x,y;
    double len(){
	return sqrt(x*x+y*y);
    }
    double angle(){
	return atan2(y,x);
    }
};

const int maxN=150;
const double INF=1e18;
const double eps=1e-8;

int n,S;
double Ds[maxN][maxN];
Point P[maxN+maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,double B);
Point operator * (double A,Point B);
double Cross(Point A,Point B);
double Dot(Point A,Point B);
bool same(double A,double B);
bool check(Point A,Point B);
double G(Point L1,Point L2,Point P);
int main(){
    scanf("%d%d",&n,&S);
    for (int i=1;i<=n;i++) scanf("%lf%lf%lf%lf",&P[i].x,&P[i].y.&P[i+n].x,&P[i+n].y);
    P[

    for (int i=1;i<=n+5;i++) Ds[i][i]=INF;
    for (int i=1;i<=n+5;i++)
	for (int j=i+1;j<=n+5;j++){
	    double d=INF;
	    if (check(A[i],A[j])) d=min(d,(A[i]-A[j]).len());
	    if (check(A[i],B[j])) d=min(d,(A[i]-B[j]).len());
	    if (check(B[i],A[j])) d=min(d,(B[i]-A[j]).len());
	    if (check(B[i],B[j])) d=min(d,(B[i]-B[j]).len());
	    d=min(d,G(A[i],B[i],A[j]));
	    d=min(d,G(A[i],B[i],B[j]));
	    d=min(d,G(A[j],B[j],A[i]));
	    d=min(d,G(A[j],B[j],B[i]));
	    Ds[i][j]=Ds[j][i]=d;
	}
    double Ans=INF;
    for (int k=1;k<=n+5;k++){
	Ans=min(Ans,Ds[1][k]+Ds[k][1]);
	for (int i=1;i<=n+5;i++) if (i!=k) for (int j=1;j<=n+5;j++) if (j!=k) Ds[i][j]=min(Ds[i][j],Ds[i][k]+Ds[k][j]);
    }
    printf("%.10lf\n",Ans);return 0;
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
Point operator * (Point A,double B){
    return ((Point){A.x*B,A.y*B});
}
Point operator * (double A,Point B){
    return ((Point){A*B.x,A*B.y});
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
double Dot(Point A,Point B){
    return A.x*B.x+A.y*B.y;
}
bool same(double A,double B){
    return fabs(A-b)<eps;
}
bool check(Point A,Point B){
    Point C[4];int cnt=0;Point d=B-A;double len=d.len();d/=len;
    if (!same(A.y,B.y)){
	Point p=A+d*(-S-A.x),q=A+d*(S-A.x);
	if (same(len,(p-A).len()+(p-B).len())&&p.y>=-S&&p.y<=S) C[++cnt]=p;
	if (same(len,(q-A).len()+(q-B).len())&&q.y>=-S&&q.y<=S) C[++cnt]=q;
    }
    if (!same(A.x,B.x)){
	Point p=A+d*(-S-A.y),q=A+d*(S-A.y);
	if (same(len,(p-A).len()+(p-B).len())&&p.x>=-S&&p.x<=S) C[++cnt]=p;
	if (same(len,(q-A).len()+(q-B).len())&&q.x>=-S&&q.x<=S) C[++cnt]=q;
    }
    for (int i=1;i<=cnt;i++) for (int j=i+1;j<=cnt;j++) if ((C[i]-C[j]).len()>eps) return 0;
    return 1;
}
double G(Point L1,Point L2,Point P){
    if ((L1-L2).len()<eps) return INF;
    double dist=fabs(Cross(P-L1,P-L2)
}
