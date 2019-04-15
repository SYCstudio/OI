#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=2010;

struct Point{
    ll x,y;
    double k(){
	return (double)y/(double)x;
    }
};
struct SorterData{
    Point L;int a,b;double agl;
};

int n,lcnt;ll S;
Point P[maxN];
SorterData Std[maxN*maxN];
int Id[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ll Cross(Point A,Point B);
bool xcmp(Point A,Point B);
bool lcmp(SorterData A,SorterData B);
ll calc(int a,int b,int c);
int main(){
    scanf("%d %lld",&n,&S);for (int i=1;i<=n;i++) scanf("%lld%lld",&P[i].x,&P[i].y);
    sort(&P[1],&P[n+1],xcmp);S=S+S;
    for (int i=1;i<=n;i++) for (int j=i+1;j<=n;j++) Std[++lcnt]=((SorterData){P[j]-P[i],i,j,(P[j]-P[i]).k()});
    sort(&Std[1],&Std[lcnt+1],lcmp);
    for (int i=1;i<=n;i++) Id[i]=i;

    for (int i=1;i<=lcnt;i++){
	int u=Id[Std[i].a],v=Id[Std[i].b];
	if (u>v) swap(u,v);
	int l=1,r=u-1;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (calc(mid,u,v)<S) r=mid-1;
	    else l=mid+1;
	}
	l=v+1;r=n;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (calc(mid,u,v)<S) l=mid+1;
	    else r=mid-1;
	}
	swap(P[u],P[v]);swap(Id[Std[i].a],Id[Std[i].b]);
    }
    puts("No");return 0;
}
Point operator + (Point A,Point B){
    return ((Point){A.x+B.x,A.y+B.y});
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
ll Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}
bool xcmp(Point A,Point B){
    return A.x<B.x;
}
bool lcmp(SorterData A,SorterData B){
    return A.agl<B.agl;
}
ll calc(int a,int b,int c){
    ll area=abs(Cross(P[a]-P[b],P[c]-P[b]));
    if (fabs(area-S)<1e-8){
	puts("Yes");
	printf("%lld %lld\n%lld %lld\n%lld %lld\n",(ll)P[a].x,(ll)P[a].y,(ll)P[b].x,(ll)P[b].y,(ll)P[c].x,(ll)P[c].y);
	exit(0);
    }
    return area;
}
