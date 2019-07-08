#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ft first
#define sd second
#define mp make_pair
const int maxN=101000;
const int maxP=505000;
const double eps=1e-8;

class Point
{
public:
	double x,y;
	Point()
	{
		x=y=0;
		return;
	}
	Point(double a,double b)
	{
		x=a;
		y=b;
		return;
	}
};
class Watcher
{
public:
	double x,l,r;
	int opt;
	Watcher()
	{
		x=l=r=0;
		opt=0;
		return;
	}
	Watcher(double a,double b,double c,int o)
	{
		x=a;
		l=b;
		r=c;
		opt=o;
		return;
	}
};

int n,A,B,C,crxcnt=0,numy,Id[maxN],uId[maxN];
double XST,XED,srty[maxN+maxN];
pair<double,double> P[maxN];
Point Crx[maxP];
Watcher Wch[maxN+maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream & os,Point A);
double Cross(Point A,Point B);
Point GetCross(int i,int j);
bool xcmp(Point A,Point B);
bool ycmp(int A,int B);
bool wcmp(Watcher A,Watcher B);
namespace Fenwick
{
int B[maxN+maxN];
void P(int p,int k);
int Q(int p);
}

int main()
{
	scanf("%d%d%d%d%lf%lf",&n,&A,&B,&C,&XST,&XED);
	for (int i=1; i<=n; i++) scanf("%lf",&P[i].ft);
	for (int i=1; i<=n; i++) scanf("%lf",&P[i].sd);
	sort(&P[1],&P[n+1]);

	set<pair<double,int> > Gs;
	for (int i=1; i<=n; i++) {
		for (set<pair<double,int> >::reverse_iterator it=Gs.rbegin(); it!=Gs.rend(); ++it) {
			if ((*it).ft<=P[i].sd) break;
			Crx[++crxcnt]=GetCross(i,(*it).sd);
		}
		Gs.insert(mp(P[i].sd,i));
	}

	ll baseans=0,Ans1=1ll*crxcnt*A,Ans2;

	//Work C
	for (int i=1; i<=crxcnt; i++) Crx[i]=(Point) {
		Crx[i].x+Crx[i].y,Crx[i].x-Crx[i].y
	};
	sort(&Crx[1],&Crx[crxcnt+1],xcmp);
	int K,wcnt=0;
	scanf("%d",&K);
	srty[++numy]=1e18;
	for (int i=1; i<=K; i++) {
		double dx,dy,r,x,y;
		scanf("%lf%lf%lf",&dx,&dy,&r);
		x=dx+dy;
		y=dx-dy;
		Wch[++wcnt]=(Watcher) {
			x-r,y-r,y+r+eps,1
		};
		Wch[++wcnt]=(Watcher) {
			x+r+eps,y-r,y+r+eps,-1
		};
		srty[++numy]=y-r;
		srty[++numy]=y+r+eps;
	}
	sort(&srty[1],&srty[numy+1]);
	sort(&Wch[1],&Wch[wcnt+1],wcmp);
	numy=unique(&srty[1],&srty[numy+1])-srty-1;

#define Dct(x) (lower_bound(&srty[1],&srty[numy+1],x)-srty)
	for (int l=1,r,p=1; l<=wcnt; l=r+1) {
		while (p<=crxcnt&&Crx[p].x<Wch[l].x) {
			if (Fenwick::Q(Dct(Crx[p].y+eps)-1)) ++baseans;
			++p;
		}
		r=l;
		while (r<wcnt&&Wch[r+1].x==Wch[l].x) ++r;
		for (int i=l; i<=r; i++) {
			if (Wch[i].opt==1) Fenwick::P(Dct(Wch[i].l),1),Fenwick::P(Dct(Wch[i].r),-1);
			else Fenwick::P(Dct(Wch[i].l),-1),Fenwick::P(Dct(Wch[i].r),1);
		}
	}
#undef Dct

	baseans=baseans*C;
	for (int i=1; i<=crxcnt; i++) Crx[i]=(Point) {
		(Crx[i].x+Crx[i].y)/2,(Crx[i].x-Crx[i].y)/2
	};

	//Work A,B
	for (int i=1; i<=n; i++) Id[i]=i;
	sort(&Id[1],&Id[n+1],ycmp);
	for (int i=1; i<=n; i++) uId[Id[i]]=i;
	int c=0;
	for (int i=1; i<=n; i++)
		if (Id[i]!=i) {
			int p=uId[i];
			++c;
			swap(Id[i],Id[p]);
			uId[Id[i]]=i;
			uId[Id[p]]=p;
		}
	Ans2=A*c+B*(crxcnt-c);

	Ans1+=baseans;
	Ans2+=baseans;
	if (Ans1>Ans2) swap(Ans1,Ans2);
	printf("%lld %lld\n",Ans1,Ans2);
	return 0;
}
Point operator + (Point A,Point B)
{
	return (Point) {
		A.x+B.x,A.y+B.y
	};
}
Point operator - (Point A,Point B)
{
	return (Point) {
		A.x-B.x,A.y-B.y
	};
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
Point GetCross(int i,int j)
{
	double ki=(P[i].sd-P[i].ft)/(XED-XST),kj=(P[j].sd-P[j].ft)/(XED-XST);
	double sk=ki-kj,d=(P[j].ft-P[i].ft)/sk;
	return (Point) {
		XST+d,P[i].ft+d*ki
	};
}
bool xcmp(Point A,Point B)
{
	if (fabs(A.x-B.x)>eps) return A.x<B.x;
	return A.y<B.y;
}
bool ycmp(int A,int B)
{
	return P[A].sd<P[B].sd;
}
bool wcmp(Watcher A,Watcher B)
{
	return A.x<B.x;
}
namespace Fenwick
{
void P(int p,int k)
{
	while (p<=numy) {
		B[p]+=k;
		p+=p&(-p);
	}
	return;
}
int Q(int p)
{
	int r=0;
	while (p) {
		r+=B[p];
		p-=p&(-p);
	}
	return r;
}
}
