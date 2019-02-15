#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define sqr(x) ((x)*(x))
const int maxN=510;
const double inf=1e18;
const double Pi=acos(-1);

class Point{
public:
    double x,y;
    double len(){
        return sqrt(sqr(x)+sqr(y));
    }
};
class Circle{
public:
    double r;Point p;
};

int n;
double alpha,H[maxN];
Circle C[maxN];
pair<Point,Point> L[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point Rotate(Point A,double agl);
void CalcLine(Circle A,Circle B,int id);
double Calc(double x);
double Inte(double l,double r);
double Simpson(double l,double r,double eps);

int main(){
    double left=inf,right=-inf;
    scanf("%d%lf",&n,&alpha);
    for (int i=0;i<=n;i++){
        double h;scanf("%lf",&h);h=h/tan(alpha);
        H[i]=(i==0)?h:H[i-1]+h;
    }
    for (int i=0;i<=n;i++){
        double r;if (i==n) r=0;else scanf("%lf",&r);
        left=min(left,H[i]-r);right=max(right,H[i]+r);
        C[i]=((Circle){r,((Point){H[i],0})});
    }
    //for (int i=0;i<=n;i++) cout<<H[i]<<" ";cout<<endl;
    //for (int i=0;i<=n;i++) cout<<"("<<C[i].p.x<<","<<C[i].p.y<<") "<<C[i].r<<endl;
    for (int i=0;i<n;i++) CalcLine(C[i],C[i+1],i);
    //for (int i=0;i<n;i++) cout<<"("<<L[i].first.x<<","<<L[i].first.y<<") ("<<L[i].second.x<<","<<L[i].second.y<<")"<<endl;
    //cout<<left<<" "<<right<<endl;
    printf("%.2lf\n",Simpson(left,right,1e-3)*2);
    return 0;
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
Point Rotate(Point A,double agl){
    return ((Point){A.x*cos(agl)-A.y*sin(agl),A.y*cos(agl)+A.x*sin(agl)});
}
void CalcLine(Circle A,Circle B,int id){
    double d=(B.p-A.p).len(),dr=A.r-B.r;
    if (fabs(dr)>=d) return;
    double agl=acos(dr/d);
    //cout<<id<<":"<<d<<" "<<dr<<" "<<agl<<" "<<dr/d<<endl;
    L[id]=make_pair(A.p+Rotate((Point){A.r,0},agl),B.p+Rotate((Point){B.r,0},agl));
    return;
}
double Calc(double x){
    double mx=0;
    for (int i=0;i<n;i++)
        if (L[i].first.x<=x&&L[i].second.x>=x)
            mx=max(mx,L[i].first.y+(L[i].second.y-L[i].first.y)/(L[i].second.x-L[i].first.x)*(x-L[i].first.x));
    for (int i=0;i<=n;i++)
        if (fabs(x-C[i].p.x)<=C[i].r){
            double d=fabs(x-C[i].p.x);
            mx=max(mx,sqrt(sqr(C[i].r)-sqr(d)));
        }
    return mx;
}
double Inte(double l,double r){
    return (r-l)*(Calc(l)+Calc(r)+Calc((l+r)/2)*4)/6;
}
double Simpson(double l,double r,double eps){
    double mid=(l+r)/2,k=Inte(l,r),kl=Inte(l,mid),kr=Inte(mid,r);
    if (fabs(kl+kr-k)<eps*15) return kl+kr;
    return Simpson(l,mid,eps/2)+Simpson(mid,r,eps/2);
}