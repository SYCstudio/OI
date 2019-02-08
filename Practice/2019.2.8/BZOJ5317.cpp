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

const int maxN=101000*2;

int n,m,Q;
Point P1[maxN],P2[maxN],Bp[maxN],Sm[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream &os,Point A);
double Cross(Point A,Point B);
void GetConvex(Point *P,int &T);
bool cmpx(Point A,Point B);
bool cmpc(Point A,Point B);

int main(){
    //freopen("in","r",stdin);freopen("out","w",stdout);
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=n;i++) scanf("%lf%lf",&P1[i].x,&P1[i].y);
    for (int i=1;i<=m;i++) scanf("%lf%lf",&P2[i].x,&P2[i].y),P2[i].x*=-1,P2[i].y*=-1;
    GetConvex(P1,n);GetConvex(P2,m);
    //for (int i=1;i<=n;i++) cout<<P1[i]<<" ";cout<<endl;
    //for (int i=1;i<=m;i++) cout<<P2[i]<<" ";cout<<endl;

    Sm[1]=P1[1]+P2[1];
    P1[n+1]=P1[1];P2[m+1]=P2[1];
    for (int i=1;i<=n;i++) P1[i]=P1[i+1]-P1[i];
    for (int i=1;i<=m;i++) P2[i]=P2[i+1]-P2[i];

    //for (int i=1;i<=n;i++) cout<<P1[i]<<" ";cout<<endl;
    //for (int i=1;i<=m;i++) cout<<P2[i]<<" ";cout<<endl;

    int top=1,p1=1,p2=1;
    while (p1<=n||p2<=m)
        if (p2>m||(p1<=n&&Cross(P1[p1],P2[p2])>=0)) ++top,Sm[top]=Sm[top-1]+P1[p1++];
        else ++top,Sm[top]=Sm[top-1]+P2[p2++];
    GetConvex(Sm,top);

    //for (int i=1;i<=top;i++) cout<<Sm[i]<<" ";cout<<endl;

    Point dpt=Sm[1];
    for (int i=1;i<=top;i++) Sm[i]=Sm[i]-dpt;
    Sm[top+1]=Sm[1];

    //for (int i=1;i<=top;i++) cout<<Sm[i]<<" ";cout<<endl;

    while (Q--){
        Point q;scanf("%lf%lf",&q.x,&q.y);
        q=q-dpt;
        //cout<<q<<" "<<Cross(q,Sm[1])<<" "<<Cross(q,Sm[top])<<endl;
        if (Cross(q,Sm[2])>0||Cross(q,Sm[top])<0) puts("0");
        else{
            int p=lower_bound(&Sm[1],&Sm[top+1],q,cmpc)-Sm-1;
            if (Cross(Sm[p+1]-Sm[p],q-Sm[p])>=0) puts("1");
            else puts("0");
        }
    }

    return 0;
}

Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
ostream & operator << (ostream &os,Point A){
    os<<"("<<(int)A.x<<","<<(int)A.y<<")";return os;
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
void GetConvex(Point *P,int &T){
    sort(&P[1],&P[T+1],cmpx);
    Point st=P[1];for (int i=1;i<=T;i++) P[i]=P[i]-st;
    sort(&P[1],&P[T+1],cmpc);
    int top=0;
    for (int i=1;i<=T;i++){
        while (top>=2&&Cross(Bp[top]-Bp[top-1],P[i]-Bp[top-1])<=0) --top;
        Bp[++top]=P[i];
    }
    for (int i=1;i<=top;i++) P[i]=st+Bp[i];
    T=top;return;
}
bool cmpx(Point A,Point B){
    if (A.y!=B.y) return A.y<B.y;
    return A.x<B.x;
}
bool cmpc(Point A,Point B){
    return Cross(A,B)>0||(Cross(A,B)==0&&A.len()<B.len());
}