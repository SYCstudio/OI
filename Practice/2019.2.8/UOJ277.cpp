#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))

const int maxC=510;
const int maxN=maxC*maxC*8;
const int maxM=maxN*10;
const double Pi=acos(-1);
const double inf=1e10;
const double eps=1e-8;

class Point
{
public:
	double x,y;
	double len()
	{
		return sqrt(sqr(x)+sqr(y));
	}
};
class Circle
{
public:
	Point p;
	double r;
};

int n,nodecnt;
Circle C[maxC];
vector<pair<double,int> > P[maxC];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
double W[maxM],Dst[maxM];
priority_queue<pair<double,int> > H;
bool vis[maxN];

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
ostream & operator << (ostream &os,Point A);
Point Rotate(Point A,double agl);
Point Get(Circle C,double agl);
double Cross(Point A,Point B);
double Dot(Point A,Point B);
double Bond(double agl);
void Link(int u,int v);
bool check(Point A,Point B,int u,int v);
void Add_Edge(int u,int v,double w);

int main()
{
	//freopen("circle10.in","r",stdin);freopen("out","w",stdout);
	double sx,sy,tx,ty;
	scanf("%lf%lf%lf%lf",&sx,&sy,&tx,&ty);
	scanf("%d",&n);
	mem(Head,-1);
	C[n+1]=((Circle) {
		(Point) {sx,sy},0
	});
	C[n+2]=((Circle) {
		(Point) {tx,ty},0
	});
	for (int i=1; i<=n; i++) {
		scanf("%lf%lf%lf",&C[i].p.x,&C[i].p.y,&C[i].r);
	}
	for (int i=1; i<=n+2; i++) for (int j=i+1; j<=n+2; j++) Link(i,j);
	for (int i=1; i<=n+2; i++) {
		sort(P[i].begin(),P[i].end());
		int sz=P[i].size()-1;
		if (sz==-1) cerr<<"ERR"<<endl;
		for (int j=0; j<=sz-1; j++) Add_Edge(P[i][j].second,P[i][j+1].second,C[i].r*(P[i][j+1].first-P[i][j].first));
		Add_Edge(P[i][sz].second,P[i][0].second,C[i].r*(Pi*2-P[i][sz].first+P[i][0].first));
	}
	for (int i=1; i<=nodecnt; i++) Dst[i]=inf;
	int S=P[n+1][0].second,T=P[n+2][0].second;
	Dst[S]=0;
	H.push(make_pair(0,S));
	while (!H.empty()) {
		int u=H.top().second;
		H.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=Head[u]; i!=-1; i=Next[i])
			if (Dst[V[i]]>Dst[u]+W[i]) {
				Dst[V[i]]=Dst[u]+W[i];
				H.push(make_pair(-Dst[V[i]],V[i]));
			}
	}
	printf("%.1lf\n",Dst[T]);
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
ostream & operator << (ostream &os,Point A)
{
	os<<"("<<A.x<<","<<A.y<<")";
	return os;
}
Point Rotate(Point A,double agl)
{
	return ((Point) {
		A.x*cos(agl)-A.y*sin(agl),A.y*cos(agl)+A.x*sin(agl)
	});
}
Point Get(Circle C,double agl)
{
	Point A=((Point) {
		C.r,0
	});
	A=Rotate(A,agl);
	return A+C.p;
}
double Cross(Point A,Point B)
{
	return A.x*B.y-A.y*B.x;
}
double Dot(Point A,Point B)
{
	return A.x*B.x+A.y*B.y;
}
double Bond(double agl)
{
	while (agl<0) agl+=Pi*2;
	while (agl>=Pi*2) agl-=Pi*2;
	return agl;
}
void Link(int u,int v)
{
	if (C[u].r<C[v].r) swap(u,v);
	Point pd=C[v].p-C[u].p;
	double d=(C[u].p-C[v].p).len(),dr=C[u].r-C[v].r;
	double theta=Bond(atan2(pd.y,pd.x)),agl=acos(dr/d);
	//cout<<"running at :"<<u<<" "<<v<<" "<<C[u].p<<"["<<C[u].r<<"] "<<C[v].p<<"["<<C[v].r<<"]"<<" "<<pd<<" "<<nodecnt<<" "<<edgecnt<<endl;
	//cout<<d<<" "<<dr<<" "<<agl<<" "<<tan(theta)<<endl;
	Point A=Get(C[u],agl+theta),B=Get(C[v],agl+theta);
	if (check(A,B,u,v)) {
		//cout<<"case1:"<<u<<" "<<v<<" "<<A<<" "<<B<<endl;
		P[u].push_back(make_pair(Bond(agl+theta),++nodecnt));
		P[v].push_back(make_pair(Bond(agl+theta),++nodecnt));
		Add_Edge(nodecnt-1,nodecnt,(A-B).len());
	}
	A=Get(C[u],theta-agl);
	B=Get(C[v],theta-agl);
	if (check(A,B,u,v)) {
		//cout<<"case2:"<<u<<" "<<v<<" "<<A<<" "<<B<<endl;
		P[u].push_back(make_pair(Bond(theta-agl),++nodecnt));
		P[v].push_back(make_pair(Bond(theta-agl),++nodecnt));
		Add_Edge(nodecnt-1,nodecnt,(A-B).len());
	}
	dr=C[u].r+C[v].r;
	agl=acos(dr/d);
	A=Get(C[u],agl+theta);
	B=Get(C[v],Pi+agl+theta);
	if (check(A,B,u,v)) {
		//cout<<"case3:"<<u<<" "<<v<<" "<<A<<" "<<B<<endl;
		P[u].push_back(make_pair(Bond(agl+theta),++nodecnt));
		P[v].push_back(make_pair(Bond(Pi+agl+theta),++nodecnt));
		Add_Edge(nodecnt-1,nodecnt,(A-B).len());
	}
	A=Get(C[u],theta-agl);
	B=Get(C[v],Pi-agl+theta);
	if (check(A,B,u,v)) {
		//cout<<"case4:"<<u<<" "<<v<<" "<<A<<" "<<B<<endl;
		P[u].push_back(make_pair(Bond(theta-agl),++nodecnt));
		P[v].push_back(make_pair(Bond(Pi-agl+theta),++nodecnt));
		Add_Edge(nodecnt-1,nodecnt,(A-B).len());
	}
	return;
}
bool check(Point A,Point B,int u,int v)
{
	double len=(B-A).len();
	for (int i=1; i<=n; i++)
		if (i!=u&&i!=v) {
			double d=fabs(Cross(A-C[i].p,B-C[i].p)/len);
			if (d+eps>C[i].r) continue;
			double l=Dot(B-A,C[i].p-A)/len;
			if (l>eps&&l<len+eps) return 0;
		}
	return 1;
}
void Add_Edge(int u,int v,double w)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	W[edgecnt]=w;
	Next[++edgecnt]=Head[v];
	Head[v]=edgecnt;
	V[edgecnt]=u;
	W[edgecnt]=w;
	return;
}