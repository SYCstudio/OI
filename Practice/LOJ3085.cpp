#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ft first
#define sd second
#define mp make_pair
const int maxN=101000;
const int maxP=505000;

class Point{
public:
    double x,y;
    Point(){
	x=y=0;return;
    }
    Point(double a,double b){
	x=a;y=b;return;
    }
};

int n,A,B,C,crxcnt=0;
double XST,XED;
pair<double,double> P[maxN];
Point Crx[maxP];
map<int,int> Cnt[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
double Cross(Point A,Point B);
Point GetCross(int i,int j);
int main(){
    scanf("%d%d%d%d%lf%lf",&n,&A,&B,&C,&XST,&XED);
    for (int i=1;i<=n;i++) scanf("%lf",&P[i].ft);
    for (int i=1;i<=n;i++) scanf("%lf",&P[i].sd);
    sort(&P[1],&P[n+1]);

    set<pair<int,int> > Gs;
    for (int i=1;i<=n;i++){
	for (set<pair<int,int> >::iterator it=Gs.rbegin();it!=Gs.rend();++it){
	    if ((*it).ft<=P[i].sd) break;
	    Crx[++crxcnt]=GetCross(i,(*it).sd);
	    ++Cnt[(*it).sd][i];
	}
	Gs.insert(mp(P[i].sd,i));
    }
}
Point operator + (Point A,Point B){
    return (Point)(A.x+B.x,A.y+B.y);
}
Point operator - (Point A,Point B){
    return (Point)(A.x-B.x,A.y-B.y);
}
double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
Point GetCross(int i,int j){
}
