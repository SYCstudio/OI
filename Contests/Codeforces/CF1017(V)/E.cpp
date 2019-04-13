#include<bits/stdc++.h>
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

const int maxN=101000;
const double eps=1e-10;
const double Pi=acos(-1);

int n,m;
Point M1[maxN+maxN],M2[maxN+maxN];
int Nxt[maxN*4];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream &os,Point A);
bool cmpc(Point A,Point B);
double Cross(Point A,Point B);
void Convex(Point *P,int &T);
bool check();
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%lf%lf",&M1[i].x,&M1[i].y);
    for (int i=1;i<=m;i++) scanf("%lf%lf",&M2[i].x,&M2[i].y);
    Convex(M1,n);Convex(M2,m);
    //for (int i=1;i<=n;i++) cout<<M1[i]<<" ";cout<<endl;
    //for (int i=1;i<=m;i++) cout<<M2[i]<<" ";cout<<endl;

    if (check()) puts("YES");else puts("NO");
    return 0;
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
ostream & operator << (ostream & os,Point A){
    os<<"("<<A.x<<","<<A.y<<")";return os;
}
bool cmpc(Point A,Point B){
    return Cross(A,B)>0||(fabs(Cross(A,B))<eps&&A.len()<B.len());
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
void Convex(Point *P,int &T){
    static Point Bp[maxN];
    Point base=P[1];for (int i=2;i<=T;i++) if (P[i].y<base.y||(fabs(P[i].y-base.y)<eps&&P[i].x<base.x)) base=P[i];
    for (int i=1;i<=T;i++) P[i]=P[i]-base;sort(&P[1],&P[T+1],cmpc);
    int top=0;
    for (int i=1;i<=T;i++){
        if (top&&(P[i]-Bp[top]).len()<eps) continue;
        while (top>=2&&Cross(P[i]-Bp[top-1],Bp[top]-Bp[top-1])>=0) --top;
        Bp[++top]=P[i];
    }
    T=top;for (int i=1;i<=top;i++) P[i]=Bp[i]+base;return;
}
bool check(){
    if (n!=m) return 0;
    static double Mh[maxN*4],Ms[maxN*4];
    for (int i=1;i<=n;i++) M1[i+n]=M1[i];
    int cnt1=0,cnt2=0;
    for (int i=1;i<n+n;i++){
	if (i>=2){
	    Point p1=M1[i]-M1[i-1],p2=M1[i]-M1[i+1];
	    Mh[++cnt1]=p1.angle()-p2.angle();
	    if (Mh[cnt1]<0) Mh[cnt1]+=Pi+Pi;
	    //Mh[++cnt1]=Cross(p2,p1)/p1.len()/p2.len();
	}
	Mh[++cnt1]=(M1[i+1]-M1[i]).len();
    }
    for (int i=1;i<m;i++){
	if (i>=2){
	    Point p1=M2[i]-M2[i-1],p2=M2[i]-M2[i+1];
	    Ms[++cnt2]=p1.angle()-p2.angle();
	    if (Ms[cnt2]<0) Ms[cnt2]+=Pi+Pi;
	    //Ms[++cnt2]=(Cross(p2,p1))/p1.len()/p2.len();
	}
	Ms[++cnt2]=(M2[i+1]-M2[i]).len();
    }
    //for (int i=1;i<=cnt1;i++) cout<<Mh[i]<<" ";cout<<endl;
    //for (int i=1;i<=cnt2;i++) cout<<Ms[i]<<" ";cout<<endl;
    Nxt[1]=Nxt[0]=0;
    for (int i=2,j=0;i<=cnt2;i++){
	while (j&&fabs(Ms[j+1]-Ms[i])>eps) j=Nxt[j];
	if (fabs(Ms[j+1]-Ms[i])<eps) ++j;
	Nxt[i]=j;
    }
    for (int i=1,j=0;i<=cnt1;i++){
	while (j&&fabs(Mh[i]-Ms[j+1])>eps) j=Nxt[j];
	if (fabs(Mh[i]-Ms[j+1])<eps) ++j;
	if (j==cnt2) return 1;
    }
    return 0;
}
