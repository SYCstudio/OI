#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

class Point{
public:
    double x,y;
    double len(){
	return sqrt(x*x+y*y);
    }
};

const int maxN=1010000;
const double eps=1e-8;
const double INF=1e18;

int n,St[maxN];
Point P[maxN];

bool cmpx(Point A,Point B);
Point operator - (Point A,Point B);
double Cross(Point A,Point B);
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%lf%lf",&P[i].x,&P[i].y);
    sort(&P[1],&P[n+1],cmpx);
    P[n+1]=((Point){0,P[1].y});
    P[n+2]=((Point){P[n].x,0});
    n+=2;
    sort(&P[1],&P[n+1],cmpx);
    int top=0;
    for (int i=1;i<=n;i++){
	while (top>=2&&Cross(P[St[top]]-P[St[top-1]],P[i]-P[St[top-1]])>0) --top;
	St[++top]=i;
    }
    for (int i=1;i<=top;i++) P[i]=P[St[i]];
    n=top;
    //for (int i=1;i<=n;i++) cout<<"("<<P[i].x<<" "<<P[i].y<<") ";cout<<endl;

    double Ans=INF;
    for (int i=2;i<n;i++){
	double l=-(P[i].y-P[i-1].y)/(P[i].x-P[i-1].x);
	double r=-(P[i].y-P[i+1].y)/(P[i].x-P[i+1].x);
	if (fabs(l)<eps) l=eps;
	if (fabs(1/l)<eps) l=1/eps;
	if (fabs(r)<eps) r=eps;
	if (fabs(1/r)<eps) r=1/eps;
	double k=sqrt(P[i].x/P[i].y);
	//cout<<l<<" "<<r<<" "<<k<<" "<<Ans<<endl;
	if (l<=k&&k<=r) Ans=min(Ans,P[i].x+P[i].y+k*P[i].x+P[i].y/k);
	Ans=min(Ans,P[i].x+P[i].y+l*P[i].x+P[i].y/l);
	Ans=min(Ans,P[i].x+P[i].y+r*P[i].x+P[i].y/r);
    }
    printf("%.4lf\n",Ans);return 0;
}
bool cmpx(Point A,Point B){
    if (fabs(A.x-B.x)<eps) return A.y>B.y;
    return A.x<B.x;
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
