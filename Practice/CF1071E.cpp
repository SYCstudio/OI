#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define sqr(x) ((x)*(x))

class Point{
    public:
    double x,y;
    double len(){
        return sqrt(sqr(x)+sqr(y));
    }
};

const int maxN=101000;
const double eps=1e-8;

int n,W,H;
int Ti[maxN];
Point st,P[maxN][2];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (double rate,Point A);
ostream & operator << (ostream &os,Point A);
bool cmpx(Point A,Point B);
bool cmpc(Point A,Point B);
double Cross(Point A,Point B);
double Dot(Point A,Point B);
void Convex(Point *P,int &n);
bool Inconvex(Point *C,int n,Point p);
bool check(double dt);
bool Intersection(Point A1,Point A2,Point B1,Point B2);
Point GetIntersection(Point A1,Point A2,Point B1,Point B2);

int main(){
    //freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d%d",&n,&W,&H);
    scanf("%lf%lf",&st.x,&st.y);
    for (int i=1;i<=n;i++){
        double a,b;scanf("%d%lf%lf",&Ti[i],&a,&b);
        double rate=b/H,lx=0,rx=W,ly=0,ry=W;
        lx=max(lx,a-b*(W-a)/(H-b));
        rx=min(rx,a*b/(H-b)+a);
        ly=max(ly,a-(H-b)*(W-a)/b);
        ry=min(ry,a*(H-b)/b+a);
        P[i][0]=((Point){lx,ry});
        P[i][1]=((Point){rx,ly});
    }
    //for (int i=1;i<=n;i++) cout<<P[i][0]<<" "<<P[i][1]<<endl;

    //check(5.0);return 0;

    double l=0,r=W+W,Ans=-1;
    while (l+(1e-4)<r){
        double mid=(l+r)/2;
        if (check(mid)) Ans=mid,r=mid-eps;
        else l=mid+eps;
    }
    if (Ans<0) printf("-1\n");
    else printf("%.10lf\n",Ans);
    return 0;
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
Point operator * (double rate,Point A){
    return ((Point){A.x*rate,A.y*rate});
}
ostream & operator << (ostream &os,Point A){
    os<<"("<<A.x<<","<<A.y<<")";return os;
}
bool cmpx(Point A,Point B){
    if (A.y!=B.y) return A.y<B.y;
    return A.x<B.x;
}
bool cmpc(Point A,Point B){
    return Cross(A,B)>0||(fabs(Cross(A,B))<eps&&A.len()<B.len());
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
double Dot(Point A,Point B){
    return A.x*B.x+A.y*B.y;
}
void Convex(Point *P,int &n){
    static Point Bp[maxN];
    sort(&P[1],&P[n+1],cmpx);
    Point base=P[1];for (int i=1;i<=n;i++) P[i]=P[i]-base;
    sort(&P[1],&P[n+1],cmpc);
    int top=0;
    for (int i=1;i<=n;i++){
        if (i!=1&&(P[i]-P[i-1]).len()<eps) continue;
        while (top>=2&&Cross(P[i]-Bp[top-1],Bp[top]-Bp[top-1])>=0) --top;
        Bp[++top]=P[i];
    }
    for (int i=1;i<=top;i++) P[i]=Bp[i]+base;
    n=top;return;
}
bool Inconvex(Point *C,int n,Point p){
    if (n<=2){
        for (int i=1;i<=n;i++) if (fabs(C[i].x-p.x)<eps&&fabs(C[i].y-p.y)<eps) return 1;
        return 0;
    }
    for (int i=1;i<=n;i++) if (Cross(C[i+1]-C[i],p-C[i])<0) return 0;
    return 1;
}
bool check(double dt){
    //cout<<"check:"<<dt<<endl;
    Point L1=st,L2=st;
    Point F[4]={(Point){dt,dt},(Point){dt,-dt},(Point){-dt,dt},(Point){-dt,-dt}};
    for (int i=1;i<=n;i++){
        Point C[10],N[2];int cnt=0,ncnt=0;
        for (int f=0;f<4;f++) C[++cnt]=L1+(double)(Ti[i]-Ti[i-1])*F[f],C[++cnt]=L2+(double)(Ti[i]-Ti[i-1])*F[f];
        //for (int j=1;j<=cnt;j++) cout<<C[j]<<" ";cout<<endl;
        Convex(C,cnt);
        //for (int j=1;j<=cnt;j++) cout<<C[j]<<" ";cout<<endl;
        //cout<<"Compare with:"<<P[i][0]<<" "<<P[i][1]<<endl;
        C[cnt+1]=C[1];
        for (int j=1;j<=cnt;j++) if (Intersection(C[j],C[j+1],P[i][0],P[i][1])) N[ncnt++]=GetIntersection(C[j],C[j+1],P[i][0],P[i][1]);
        //cout<<"ncnt:"<<ncnt<<endl;
        if (ncnt==0){
            if (Inconvex(C,cnt,P[i][0])&&Inconvex(C,cnt,P[i][1])) N[ncnt++]=P[i][0],N[ncnt++]=P[i][1];
            else return 0;
        }
        else if (ncnt==1){
            if (Inconvex(C,cnt,P[i][0])) N[ncnt++]=P[i][0];
            else N[ncnt++]=P[i][1];
        }
        L1=N[0];L2=N[1];
        //cout<<"after "<<i<<":"<<L1<<" "<<L2<<endl;
    }
    return 1;
}
bool Intersection(Point A1,Point A2,Point B1,Point B2){
    //cout<<"Intersection:"<<A1<<" "<<A2<<" "<<B1<<" "<<B2<<":"<<Cross(B2-B1,A1-B1)<<" "<<Cross(B2-B1,A2-B1)<<" "<<Cross(A2-A1,B1-A1)<<" "<<Cross(A2-A1,B2-A1)<<endl;
    if ((A1-A2).len()<eps&&(B1-B2).len()<eps) return (fabs(A1.x-B1.x)<eps)&&(fabs(A1.y-B1.y)<eps);
    if ((A1-A2).len()<eps) swap(A1,B1),swap(A2,B2);
    if ((B1-B2).len()<eps){
        double dt=Dot(B1-A1,A2-A1),d=(A2-A1).len();
        if (dt>=0&&dt*d<=d) return 1;
        return 0;
    }
    return (Cross(B2-B1,A1-B1)*Cross(B2-B1,A2-B1)<=0)&&(Cross(A2-A1,B1-A1)*Cross(A2-A1,B2-A1)<=0);
}
Point GetIntersection(Point A1,Point A2,Point B1,Point B2){
    if ((B1-B2).len()<eps&&(A1-A2).len()<eps) return A1;
    if ((B1-B2).len()<eps) return B1;
    //cout<<"GetIntersection:"<<A1<<" "<<A2<<" "<<B1<<" "<<B2<<endl;
    double t=fabs(Cross(B2-B1,A1-B1)/Cross(A2-A1,B2-B1));
    return A1+t*(A2-A1);
}