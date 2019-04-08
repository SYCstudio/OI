#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long double ld;
typedef long long ll;
class Point{
    public:
    ld x,y,agl;
    ld len(){
        return sqrt(x*x+y*y);
    }
    void G(){
        agl=atan2(y,x);return;
    }
};

const int maxN=1010;
const long double Pi=acos(-1);

int n;
Point P[maxN],R[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
Point operator * (Point A,long double rate);
long double Cross(Point A,Point B);
bool acmp(Point A,Point B);
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%LF%LF",&P[i].x,&P[i].y);
    ll Ans=0;
    for (int i=1;i<=n;i++){
        Point base=P[i];
        for (int j=1,rcnt=0;j<=n;j++) if (i!=j) R[++rcnt]=P[j]-base,R[rcnt].G();
        sort(&R[1],&R[n],acmp);
    }
}