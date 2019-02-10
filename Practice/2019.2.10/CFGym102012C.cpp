#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<iostream>
using namespace std;

#define sqr(x) ((x)*(x))
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=52;
const double eps=1e-8;
const double inf=1e8;
class Point{
    public:
    double x,y;
    double len(){
        return sqrt(sqr(x)+sqr(y));
    }
};
class QData{
    public:
    int opt,a,b;double d;
};

int n;
double D[2][maxN][maxN];
bool vis[2][maxN][maxN];
priority_queue<QData> Heap;
Point H[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (double rate,Point A);
ostream & operator << (ostream &os,Point A);
Point GetX(Point A,Point B,double x);
Point GetY(Point A,Point B,double y);
bool operator < (QData A,QData B);
bool InRange(double l,double r,double x);
void Push(int opt,int a,int b,double cost);

int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);for (int i=0;i<=n;i++) scanf("%lf",&H[i].y),H[i].x=i;
        H[n+1]=((Point){n+1,0});for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) D[0][i][j]=D[1][i][j]=inf;
        D[0][0][n]=0;Heap.push((QData){0,0,n,0});mem(vis,0);
        while (!Heap.empty()){
            int a=Heap.top().a,b=Heap.top().b,opt=Heap.top().opt;Heap.pop();
            if (vis[opt][a][b]) continue;vis[opt][a][b]=1;
            Point A,B;double bd=D[opt][a][b];
            //cout<<opt<<" "<<a<<" "<<b<<" "<<bd<<endl;
            if (opt==0){
                A=H[a];B=GetY(H[b],H[b+1],H[a].y);
                //cout<<A<<" "<<B<<endl;
                if ((B-H[b]).len()<eps) Push(1,a,b,bd);
                if (a!=0&&InRange(H[b].y,H[b+1].y,H[a-1].y)){
                    //cout<<"A1"<<endl;
                    Point nB=GetY(H[b],H[b+1],H[a-1].y);
                    Push(0,a-1,b,bd+(A-H[a-1]).len()+(B-nB).len());
                }
                if (a!=n&&InRange(H[b].y,H[b+1].y,H[a+1].y)){
                    //cout<<"A2"<<endl;
                    Point nB=GetY(H[b],H[b+1],H[a+1].y);
                    Push(0,a+1,b,bd+(A-H[a+1]).len()+(B-nB).len());
                }
                for (int aa=max(a-1,0);aa<=a;aa++){
                    if (InRange(H[aa].y,H[aa+1].y,H[b].y)){
                        Point nA=GetY(H[aa],H[aa+1],H[b].y);
                        Push(1,aa,b,bd+(A-nA).len()+(B-H[b]).len());
                    }
                    if (b!=n&&InRange(H[aa].y,H[aa+1].y,H[b+1].y)){
                        Point nA=GetY(H[aa],H[aa+1],H[b+1].y);
                        Push(1,aa,b+1,bd+(A-nA).len()+(B-H[b+1]).len());
                    }
                }
            }
            else{
                A=GetY(H[a],H[a+1],H[b].y);B=H[b];
                //cout<<A<<" "<<B<<endl;
                if ((A-H[a]).len()<eps) Push(0,a,b,bd);
                if (b!=0&&InRange(H[a].y,H[a+1].y,H[b-1].y)){
                    //cout<<"B1"<<endl;
                    Point nA=GetY(H[a],H[a+1],H[b-1].y);
                    Push(1,a,b-1,bd+(A-nA).len()+(B-H[b-1]).len());
                }
                if (b!=n&&InRange(H[a].y,H[a+1].y,H[b+1].y)){
                    //cout<<"B2"<<endl;
                    Point nA=GetY(H[a],H[a+1],H[b+1].y);
                    Push(1,a,b+1,bd+(A-nA).len()+(B-H[b+1]).len());
                }
                for (int bb=max(b-1,0);bb<=b;bb++){
                    if (InRange(H[bb].y,H[bb+1].y,H[a].y)){
                        //cout<<"B3-1 "<<bb<<endl;
                        Point nB=GetY(H[bb],H[bb+1],H[a].y);
                        Push(0,a,bb,bd+(A-H[a]).len()+(B-nB).len());
                    }
                    if (a!=n&&InRange(H[bb].y,H[bb+1].y,H[a+1].y)){
                        //cout<<"B3-2 "<<bb<<endl;
                        Point nB=GetY(H[bb],H[bb+1],H[a+1].y);
                        //cout<<B<<" "<<nB<<" "<<A<<" "<<H[a+1]<<endl;
                        Push(0,a+1,bb,bd+(A-H[a+1]).len()+(B-nB).len());
                    }
                }
            }
        }
        printf("%.15lf\n",min(D[0][n][0],D[1][n][0]));
    }
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
Point GetY(Point A,Point B,double y){
    if (fabs(A.y-B.y)<eps) return A;
    double r=(y-A.y)/(B.y-A.y);
    return A+r*(B-A);
}
bool operator < (QData A,QData B){
    return A.d>B.d;
}
bool InRange(double l,double r,double x){
    if (l>r) swap(l,r);return x<=r&&x>=l;
}
void Push(int opt,int a,int b,double cost){
    //cout<<"Push:"<<opt<<" "<<a<<" "<<b<<" "<<cost<<endl;
    if (vis[opt][a][b]) return;
    if (D[opt][a][b]>cost) Heap.push((QData){opt,a,b,D[opt][a][b]=cost});
    return;
}