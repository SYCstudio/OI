#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;

#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back
#define ft first
#define sd second

const int maxN=1010;
const int maxNode=maxN*maxN;
const int maxM=maxNode*8;
const ld eps=1e-7;
const ld INF=1e18;

class Point
{
public:
	ld x,y;
	ld len()
	{
		return sqrt(sqr(x)+sqr(y));
	}
};

int n,m;
ld va,vb,nodecnt=0;
int edgecnt=0,Head[maxNode],Next[maxM],V[maxM];
Point P[maxN];
vector<pair<ld,int> > St[maxN];
ld Dist[maxNode],W[maxM];
priority_queue<pair<ld,int> > H;
bool vis[maxNode];

ld crs(Point A,Point B);
ld dst(Point A,Point B);
Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
bool operator < (Point A,Point B);
ostream & operator << (ostream & os,Point A);
bool cmp(pair<ld,int> A,pair<ld,int> B);
void Calc(int p,int q1,int q2);
void Add_Edge(int u,int v,ld w);

int main()
{
	scanf("%d",&n);
	scanf("%lf%lf",&va,&vb);
	P[0].x=P[0].y=0;
	for (int i=1; i<=n; i++) scanf("%lf%lf",&P[i].x,&P[i].y),St[i].push_back(mp((P[i]-P[i-1]).len(),i-1));
	nodecnt=n;
	mem(Head,-1);
	for (int i=0; i<=n; i++)
		for (int j=0; j<n; j++) ////////////////modify
			if (i!=j&&i!=j+1) {
				Calc(i,j,j+1);
				Calc(i,j+1,j);
			}
	//cout<<"nodecnt:"<<nodecnt<<endl;

	for (int i=1; i<=n; i++) { ////////////////modify
		sort(St[i].begin(),St[i].end(),cmp);
		int sz=St[i].size()-1;
		for (int j=0; j<sz; j++)
			Add_Edge(St[i][j].sd,St[i][j+1].sd,(St[i][j].ft-St[i][j+1].ft)/va);
		Add_Edge(St[i][sz].sd,i,(St[i][sz].ft)/va);
	}
	//cout<<"edgecnt:"<<edgecnt<<endl;

	/*
	for (int i=1;i<=1;i++){////////////////modify
	cout<<i<<":";
	for (int j=0,sz=St[i].size();j<sz;j++)
	    cout<<St[i][j].ft<<" ";
	cout<<endl;
	}
	//*/

	for (int i=0; i<=nodecnt; i++) Dist[i]=INF;
	Dist[0]=0;
	H.push(mp(0,0));
	while (!H.empty()) {
		int u=H.top().second;
		H.pop();
		if (vis[u]) continue;
		vis[u]=1;
		//cout<<u<<" "<<Dist[u]<<endl;
		for (int i=Head[u]; i!=-1; i=Next[i]) {
			if (Dist[V[i]]>Dist[u]+W[i]) {
				//cout<<u<<" -> "<<V[i]<<" "<<W[i]<<endl;
				Dist[V[i]]=Dist[u]+W[i];
				H.push(mp(-Dist[V[i]],V[i]));
			}
		}
	}
	printf("%.6lf\n",Dist[n]);
	return 0;
}
ld crs(Point A,Point B)
{
	return A.x*B.y-A.y*B.x;
}
ld dst(Point A,Point B)
{
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
ld dot(Point A,Point B)
{
	return A.x*B.x+A.y*B.y;
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
bool operator < (Point A,Point B)
{
	if (fabs(A.x-B.x)>eps) return A.x<B.x;
	else return A.y<B.y;
}
ostream & operator << (ostream & os,Point A)
{
	os<<"("<<A.x<<","<<A.y<<")";
	return os;
}
bool cmp(pair<ld,int> A,pair<ld,int> B)
{
	if (fabs(A.ft-B.ft)>eps) return A.ft>B.ft;
	return A.sd<B.sd;
}
void Calc(int p,int q1,int q2)
{
	//cout<<"Calc:"<<p<<" "<<q1<<" "<<q2<<" "<<P[p]<<" "<<P[q1]<<" "<<P[q2]<<endl;
	//cout<<"dot:"<<dot(P[q1]-P[q2],P[p]-P[q2])<<endl;
	if (dot(P[q1]-P[q2],P[p]-P[q2])<eps) {
		Add_Edge(p,q2,(P[p]-P[q2]).len()/vb);
		return;
	}
	ld dis=(P[q1]-P[q2]).len();
	ld h=fabs(crs(P[p]-P[q1],P[p]-P[q2]))/dis;
	ld L=sqrt(sqr((P[p]-P[q2]).len())-h*h+eps);
	ld l=max((ld)0,L-dis),r=L;
	if (l>r) return;
	int cnt=30;
	while (l+eps<r&&cnt--) {
		ld ql=l+(r-l)/3,qr=r-(r-l)/3;
		ld lk=sqrt(ql*ql+h*h)/vb+(L-ql)/va,rk=sqrt(qr*qr+h*h)/vb+(L-qr)/va;
		if (lk<rk) r=qr;
		else l=ql;
	}
	//cout<<dis<<" "<<h<<" "<<L<<" "<<l<<endl;
	if (fabs(l-L)<eps) {
		Add_Edge(p,q2,sqrt(l*l+h*h)/vb);
		return;
	}
	if (L>dis&&fabs(L-dis-l)<eps) {
		Add_Edge(p,q1,sqrt(l*l+h*h)/vb);
		return;
	}
	q2=max(q1,q2);
	St[q2].push_back(mp(q1<q2?L-l:dis-(L-l),++nodecnt));
	Add_Edge(p,nodecnt,sqrt(l*l+h*h)/vb);
	return;
}
void Add_Edge(int u,int v,ld w)
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
