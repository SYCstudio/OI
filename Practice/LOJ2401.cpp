#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=30300;
class Point{
    public:
    double x,y;
};
int n,m;
Point A,B;
vector<Point> Drg[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,double rate);
double Cross(Point A,Point B);
bool check(Point D1,Point D2);

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        int x,y,c;scanf("%d%d%d",&x,&y,&c);
        Drg[c].push_back((Point){x,y});
    }
    scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
    int Q;scanf("%d",&Q);
    while (Q--){
        int a,b,cnt=0;scanf("%d%d",&a,&b);
        for (int i=0,sz1=Drg[a].size();i<sz1;i++)
            for (int j=0,sz2=Drg[b].size();j<sz2;j++)
                cnt+=check(Drg[a][i],Drg[b][j]);
        printf("%d\n",cnt);
    }
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
Point operator * (Point A,double rate){
    return ((Point){A.x*rate,A.y*rate});
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
bool check(Point D1,Point D2){
}