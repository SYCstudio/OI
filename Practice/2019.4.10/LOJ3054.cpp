#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;
typedef double ld;
const int maxN=1010;
const ld eps=1e-10;
const ld Pi=acos(-1);

class Point{
public:
    int x,y;
};
class Fraction{
public:
    ll a,b;
    void Init(ll x,ll y){
	a=x;b=y;static ll g;g=__gcd(abs(a),abs(b));
	a/=g;b/=g;if (b<0) a=-a,b=-b;
	return;
    }
};

int n,idcnt,Rc[maxN][maxN];
pair<ld,int> Srt[maxN+maxN];
Point P[maxN];
map<ll,int> Cnt;
map<pair<Fraction,Fraction>,int> Id;
vector<int> PX[maxN*maxN];

Point operator - (Point A,Point B);
bool operator < (Fraction A,Fraction B);
ostream & operator << (ostream &os,Fraction F);
ll GET(Point A);
int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d%d",&P[i].x,&P[i].y);
    for (int i=1;i<=n;i++)
	for (int j=i+1;j<=n;j++){
	    Fraction k,b;
	    if (P[i].y==P[j].y){
		if ((P[i].x+P[j].x)&1) continue;
		k.Init(1,0);b.Init(P[i].x+P[j].x,2);
	    }
	    else{
		k.Init(P[i].x-P[j].x,P[j].y-P[i].y);
		b.Init(1ll*(P[i].y+P[j].y)*(P[j].y-P[i].y)-1ll*(P[i].x-P[j].x)*(P[i].x+P[j].x),2ll*(P[j].y-P[i].y));
	    }
	    pair<Fraction,Fraction> pr=make_pair(k,b);
	    if (Id.count(pr)==0) Id[make_pair(k,b)]=++idcnt;
	    ll key;if (P[i].y==P[j].y) key=P[i].y+P[j].y;else key=P[i].x+P[j].x;
	    PX[Id[pr]].push_back(P[i].y==P[j].y?P[i].y+P[j].y:P[i].x+P[j].x);
	}
    for (int i=1;i<=idcnt;i++) sort(PX[i].begin(),PX[i].end());
    ll Ans=0;
    for (int i=1;i<=n;i++){
	for (int j=1,scnt=0;j<=n;j++) if (i!=j) Srt[++scnt]=make_pair(atan2(P[i].y-P[j].y,P[i].x-P[j].x),j);
	sort(&Srt[1],&Srt[n]);int top=n-1+n-1;
	for (int j=n;j<=top;j++) Srt[j]=Srt[j-(n-1)],Srt[j].first+=Pi+Pi;
	ll mul=0;
	Cnt.clear();
	for (int j=1,ql=1,qr=0;j<n;j++){
	    while (qr+1<=top&&Srt[qr+1].first+eps<Srt[j].first+Pi*1.5){
		++qr;
		mul+=Cnt[GET(P[Srt[qr].second]-P[i])];
		++Cnt[GET(P[Srt[qr].second]-P[i])];
	    }
	    while (ql<=top&&Srt[ql].first<=Srt[j].first+Pi*0.5+eps){
		--Cnt[GET(P[Srt[ql].second]-P[i])];
		mul-=Cnt[GET(P[Srt[ql].second]-P[i])];
		++ql;
	    }
	    Rc[i][Srt[j].second]=mul;
	}
    }
    for (int i=1;i<=n;i++)
	for (int j=i+1;j<=n;j++){
	    Fraction k,b;
	    if (P[i].x==P[j].x){
		k.Init(1,0);b.Init(P[i].x,1);
	    }
	    else{
		k.Init(P[i].y-P[j].y,P[i].x-P[j].x);
		b.Init(1ll*P[i].y*(P[i].x-P[j].x)-1ll*P[i].x*(P[i].y-P[j].y),P[i].x-P[j].x);
	    }
	    pair<Fraction,Fraction> pr=make_pair(k,b);
	    if (Id.count(pr)==0) continue;
	    int cc=Id[pr];ll k1,k2;
	    if (P[i].x==P[j].x) k1=P[i].y,k2=P[j].y;else k1=P[i].x,k2=P[j].x;
	    if (k1>k2) swap(k1,k2);
	    k1=k1+k1;k2=k2+k2;
	    Ans=Ans+1ll*(Rc[i][j]+Rc[j][i])*(upper_bound(PX[cc].begin(),PX[cc].end(),k2-1)-upper_bound(PX[cc].begin(),PX[cc].end(),k1));
	}
    printf("%lld\n",Ans*4);return 0;
}
bool operator < (Fraction A,Fraction B){
    if (A.a!=B.a) return A.a<B.a;
    return A.b<B.b;
}
Point operator - (Point A,Point B){
    return ((Point){A.x-B.x,A.y-B.y});
}
ll GET(Point A){
    return 1ll*(ll)A.x*(ll)A.x+1ll*(ll)A.y*(ll)A.y;
}
ostream & operator << (ostream &os,Fraction F){
    os<<F.a<<"/"<<F.b;return os;
}
