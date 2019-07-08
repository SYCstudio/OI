#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

#define sqr(x) ((x)*(x))
#define double long double
const int maxN=30300;
const double Pi=acos(-1);

class Point
{
public:
	double x,y;
	double len()
	{
		return sqrt(sqr(x)+sqr(y));
	}
	double agl()
	{
		return atan2(y,x);
	}
};
class SegmentData
{
public:
	int ls,rs,cnt;
};

int n,m;
Point A,B;
vector<Point> Dg[maxN];
pair<double,double> Sorter[maxN];
int nodecnt;
SegmentData S[maxN*20];
vector<double> X[maxN],Y[maxN];
vector<int> rt[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream & os,Point A);
double Cross(Point A,Point B);
void Modify(int &x,int l,int r,int p);
int QueryS(int x,int l,int r,int ql,int qr);
int Query(int c,double ax,double ay,double bx,double by);
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) {
		Point x;
		int c;
		scanf("%LF%LF%d",&x.x,&x.y,&c);
		Dg[c].push_back(x);
	}
	scanf("%LF%LF%LF%LF",&A.x,&A.y,&B.x,&B.y);
	for (int i=1; i<=m; i++) {
		int sz=Dg[i].size();
		for (int j=0; j<sz; j++) Sorter[j+1]=make_pair((Dg[i][j]-A).agl(),(Dg[i][j]-B).agl());

		sort(&Sorter[1],&Sorter[sz+1]);
		X[i].resize(sz+1);
		Y[i].resize(sz+1);
		rt[i].resize(sz+1);
		for (int j=1; j<=sz; j++) X[i][j]=Sorter[j].first,swap(Sorter[j].first,Sorter[j].second);
		sort(&Sorter[1],&Sorter[sz+1]);
		for (int j=1; j<=sz; j++) Y[i][j]=Sorter[j].first,Sorter[j].first=j,swap(Sorter[j].first,Sorter[j].second);
		sort(&Sorter[1],&Sorter[sz+1]);
		for (int j=1; j<=sz; j++) {
			rt[i][j]=rt[i][j-1];
			Modify(rt[i][j],1,sz,(Sorter[j].second+0.5));
		}
	}

	int Q;
	scanf("%d",&Q);
	while (Q--) {
		int E,F,cnt=0;
		scanf("%d%d",&E,&F);
		if (Dg[E].size()<=Dg[F].size()) {
			for (int i=0,sz=Dg[E].size(); i<sz; i++) {
				Point p=Dg[E][i];
				if (Cross(B-p,A-p)>0) cnt+=Query(F,(B-A).agl(),(A-p).agl(),(B-p).agl(),(A-B).agl())
					                           +Query(F,(p-A).agl(),(B-A).agl(),(A-B).agl(),(p-B).agl());
				else cnt+=Query(F,(A-p).agl(),(B-A).agl(),(A-B).agl(),(B-p).agl())
					          +Query(F,(B-A).agl(),(p-A).agl(),(p-B).agl(),(A-B).agl());
			}
		} else {
			for (int i=0,sz=Dg[F].size(); i<sz; i++) {
				Point p=Dg[F][i];
				if (Cross(B-p,A-p)>0) cnt+=Query(E,(A-B).agl(),(p-A).agl(),(p-B).agl(),(B-A).agl())
					                           +Query(E,(B-A).agl(),(A-p).agl(),(B-p).agl(),(A-B).agl());
				else cnt+=Query(E,(p-A).agl(),(A-B).agl(),(B-A).agl(),(p-B).agl())
					          +Query(E,(A-p).agl(),(B-A).agl(),(A-B).agl(),(B-p).agl());
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}
Point operator + (Point A,Point B)
{
	return ((Point) {
		A.x+B.x,A.y+B.y
	});
}
Point operator - (Point A,Point B)
{
	return ((Point) {
		A.x-B.x,A.y-B.y
	});
}
ostream & operator << (ostream & os,Point A)
{
	os<<"("<<A.x<<","<<A.y<<")";
	return os;
}
double Cross(Point A,Point B)
{
	return A.x*B.y-A.y*B.x;
}
void Modify(int &x,int l,int r,int p)
{
	S[++nodecnt]=S[x];
	x=nodecnt;
	++S[x].cnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Modify(S[x].ls,l,mid,p);
	else Modify(S[x].rs,mid+1,r,p);
}
int Query(int c,double ax,double ay,double bx,double by)
{
	if (ax>ay) return Query(c,-Pi*2,ay,bx,by)+Query(c,ax,Pi*2,bx,by);
	if (bx>by) return Query(c,ax,ay,-Pi*2,by)+Query(c,ax,ay,bx,Pi*2);
	int size=Dg[c].size(),al=0,ar=0,bl=0,br=0;

	if (ay<X[c][1]||ax>X[c][size]||by<Y[c][1]||bx>Y[c][size]) return 0;
	int l=1,r=size;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (X[c][mid]<=ax) al=mid,l=mid+1;
		else r=mid-1;
	}
	l=1;
	r=size;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (X[c][mid]<=ay) ar=mid,l=mid+1;
		else r=mid-1;
	}
	l=1;
	r=size;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (Y[c][mid]>=bx) bl=mid,r=mid-1;
		else l=mid+1;
	}
	l=1;
	r=size;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (Y[c][mid]<=by) br=mid,l=mid+1;
		else r=mid-1;
	}
	if (bl>br||al>ar) return 0;
	return QueryS(rt[c][ar],1,size,bl,br)-QueryS(rt[c][al],1,size,bl,br);
}
int QueryS(int x,int l,int r,int ql,int qr)
{
	if (!x) return 0;
	if (l==ql&&r==qr) return S[x].cnt;
	int mid=(l+r)>>1;
	if (qr<=mid) return QueryS(S[x].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return QueryS(S[x].rs,mid+1,r,ql,qr);
	else return QueryS(S[x].ls,l,mid,ql,mid)+QueryS(S[x].rs,mid+1,r,mid+1,qr);
}