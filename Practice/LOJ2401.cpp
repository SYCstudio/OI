#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

#define sqr(x) ((x)*(x))
const int maxN=30300;

class Point{
    public:
    double x,y;
    double len(){
        return sqrt(sqr(x)+sqr(y));
    }
    double agl(){
        return atan2(y,x);
    }
};

int n,m;
Point A,B;
vector<Point> Dg[maxN];
vector<double> Ag1[maxN],Ag2[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
double Cross(Point A,Point B);
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        Point x;int c;scanf("%lf%lf%d",&x.x,&x.y,&c);
        Dg[c].push_back(x);
    }
    scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
    for (int i=1;i<=m;i++){
        Ag1[i].resize(Dg[i].size());
        Ag2[i].resize(Dg[i].size());
        for (int j=0,sz=Dg[i].size();j<sz;j++) Ag1[i][j]=(Dg[i][j]-A).agl(),Ag2[i][j]=(Dg[i][j]-B).agl();
        sort(Ag1[i].begin(),Ag1[i].end());
        sort(Ag2[i].begin(),Ag2[i].end());
    }

    int Q;scanf("%d",&Q);
    while (Q--){
        int E,F,cnt=0;scanf("%d%d",&E,&F);
        if (Dg[E].size()>Dg[F].size()) swap(E,F);
        for (int i=0,sz=Dg[E].size();i<sz;i++){
            Point 
        }
    }
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}