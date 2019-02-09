#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define sqr(x) ((x)*(x))
class Point{
    public:
    double x,y;
    double len(){
        return sqrt(sqr(x)+sqr(y));
    }
};

const int maxN=510;

int n,m;
Point A[maxN],B[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
double Cross(Point A,Point B);
void Convex(Point *P,int &T);

int main(){
    while (scanf("%d%d",&n,&m)!=EOF&&n&&m){
        for (int i=1;i<=n;i++) scanf("%lf%lf",&A[i].x,&A[i].y);
        for (int i=1;i<=m;i++) scanf("%lf%lf",&B[i].x,&B[i].y);
        Convex(A,n);Convex(B,m);
        if (n<=2&&m<=2){
            
        }
    }
}