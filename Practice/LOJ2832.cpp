#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define double long double
class Point{
public:
    double x,y;
    Point(){}
    Point(double _x,double _y){
	x=_x;y=_y;return;
    }
    double len(){
	return sqrt(x*x+y*y);
    }
    double angle(){
	return atan2(y,x);
    }
};

const int maxN=310;
const double INF=1e18;
const double eps=1e-10;

int n,S;
Point P[maxN];
double Dst[maxN][maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,double B);
ostream & operator << (ostream & os,Point A);
double Cross(Point A,Point B);
double Dot(Point A,Point B);
bool same(double x,double y);
bool check(Point A,Point B);
bool Intersection(Point A,Point B,Point C,Point D);
pair<double,Point> calc(Point A,Point L1,Point L2);
int main(){
    scanf("%d%d",&n,&S);
    for (int i=1;i<=n;i++){
	scanf("%LF%LF%LF%LF",&P[i].x,&P[i].y,&P[n+4+i].x,&P[n+4+i].y);
	if (Cross(P[i],P[n+4+i])<0) swap(P[i],P[n+4+i]);
    }
    P[n+1]=P[n+4+n+1]=((Point){S,S});
    P[n+2]=P[n+4+n+2]=((Point){-S,S});
    P[n+3]=P[n+4+n+3]=((Point){-S,-S});
    P[n+4]=P[n+4+n+4]=((Point){S,-S});
    n+=4;

    for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) Dst[i][j]=INF;

    for (int i=1;i<=n;i++)
	for (int j=i+1;j<=n;j++){
	    double d=INF,key;Point c1,c2;pair<double,Point> ret;
	    //cout<<i<<"-"<<j<<" ";
	    if (check(P[i],P[j])) if ((key=(P[i]-P[j]).len())<d) d=key,c1=P[i],c2=P[j];
	    if (check(P[i],P[j+n])) if ((key=(P[i]-P[j+n]).len())<d) d=key,c1=P[i],c2=P[j+n];
	    if (check(P[i+n],P[j])) if ((key=(P[i+n]-P[j]).len())<d) d=key,c1=P[i+n],c2=P[j];
	    if (check(P[i+n],P[j+n])) if ((key=(P[i+n]-P[j+n]).len())<d) d=key,c1=P[i+n],c2=P[j+n];
	    //cout<<P[i]<<" "<<P[i+n]<<"|"<<P[j]<<" "<<P[j+n]<<endl;
	    //cout<<i<<"-"<<j<<" "<<d<<" "<<calc(P[i],P[j],P[j+n])<<" "<<calc(P[i+n],P[j],P[j+n])<<" "<<calc(P[j],P[i],P[i+n])<<" "<<calc(P[j+n],P[i],P[i+n])<<endl;
	    ret=calc(P[i],P[j],P[j+n]);if (ret.first<d) d=ret.first,c1=P[i],c2=ret.second;
	    ret=calc(P[i+n],P[j],P[j+n]);if (ret.first<d) d=ret.first,c1=P[i+n],c2=ret.second;
	    ret=calc(P[j],P[i],P[i+n]);if (ret.first<d) d=ret.first,c1=ret.second,c2=P[j];
	    ret=calc(P[j+n],P[i],P[i+n]);if (ret.first<d) d=ret.first,c1=ret.second,c2=P[j+n];
	    //d2=min(d2,calc(P[i],P[j],P[j+n]));d2=min(d2,calc(P[i+n],P[j],P[j+n]));
	    //d2=min(d2,calc(P[j],P[i],P[i+n]));d2=min(d2,calc(P[j+n],P[i],P[i+n]));
	    //cout<<"c1c2:"<<c1<<" "<<c2<<endl;
	    if (Cross(c1,c2)>0) Dst[i][j]=d;else Dst[j][i]=d;
	}
    /*
    for (int i=1;i<=n;i++){
	for (int j=1;j<=n;j++)
	    if (same(Dst[i][j],INF)) printf("inf ");
	    else printf("%5.5LF ",Dst[i][j]);
	printf("\n");
    }
    //*/

    for (int k=1;k<=n;k++) for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Dst[i][j]=min(Dst[i][j],Dst[i][k]+Dst[k][j]);
    /*
    for (int i=1;i<=n;i++){
	for (int j=1;j<=n;j++)
	    if (same(Dst[i][j],INF)) printf("inf ");
	    else printf("%5.5LF ",Dst[i][j]);
	printf("\n");
    }
    //*/
    
    double Ans=INF;for (int i=1;i<=n;i++) Ans=min(Ans,Dst[i][i]);
    printf("%.10LF\n",Ans);return 0;
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
ostream & operator << (ostream & os,Point A){
    os<<"("<<A.x<<","<<A.y<<")";return os;
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
double Dot(Point A,Point B){
    return A.x*B.x+A.y*B.y;
}
bool same(double x,double y){
    return fabs(x-y)<eps;
}
bool check(Point A,Point B){
    if ((A-B).len()<eps){
	if (A.x>-S&&A.x<S&&A.y>-S&&A.y<S) return 0;
	return 1;
    }
    Point L1(S,S),L2(-S,S),L3(-S,-S),L4(S,-S);
    if (Intersection(L1,L2,A,B)||Intersection(L2,L3,A,B)||Intersection(L3,L4,A,B)||Intersection(L4,L1,A,B)
	||Intersection(L1,L3,A,B)||Intersection(L2,L4,A,B)) return 0;
    return 1;
}
bool Intersection(Point A,Point B,Point C,Point D){
    return (Cross(B-C,D-C)*Cross(A-C,D-C)<0)&&(Cross(C-A,B-A)*Cross(D-A,B-A)<0);
}
pair<double,Point> calc(Point A,Point L1,Point L2){
    if ((L1-L2).len()<eps) return make_pair(INF,((Point){0,0}));
    Point d=L2-L1;Point td=d;swap(td.x,td.y);td.x=-td.x;
    Point p=L1+d*(Cross(td,L1-A)/Cross(d,td));
    //cout<<"p:"<<p<<endl;
    if (check(A,p)&&same((L1-L2).len(),(L1-p).len()+(L2-p).len())) return make_pair(fabs(Cross(L1-A,L2-A))/(L1-L2).len(),p);
    else return make_pair(INF,((Point){0,0}));
}
