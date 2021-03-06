#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long

const int maxN=400010;
const ll INF=1e18;

class Point
{
public:
	ll x,y;
};

Point operator + (Point A,Point B);
Point operator - (Point A,Point B);
bool operator == (Point A,Point B);
ll Cross(Point A,Point B);
ll Prod(Point A,Point B);

class Convex
{
public:
	vector<Point> V;
	int opt;
	void push_back(Point A)
	{
		//V.push_back(A);return;

		int sz=V.size()-1;
		//if ((sz>=0)&&(V[sz]==A)) return;
		while ((sz>0)&&( ((opt==1)&&(Cross(V[sz]-V[sz-1],A-V[sz])>=0))
		                 ||((opt==2)&&(Cross(A-V[sz],V[sz]-V[sz-1])>=0)) )) --sz,V.pop_back();
		V.push_back(A);
		return;
	}
	ll query(Point A)
	{
		int sz=V.size()-1,l=0,r=sz;
		ll ret=-INF;

		while (r-l>=3) {
			int msz=(r-l)/3,ql=l+msz,qr=r-msz;
			if (Prod(V[ql],A)<Prod(V[qr],A)) l=ql;
			else r=qr;
		}
		//*/
		for (int i=l; i<=r; i++) ret=max(ret,Prod(V[i],A));
		return ret;
	}
};

class SegmentData
{
public:
	int ls,rs,mid;
	Convex up,down;
};

int n,rt[maxN],Sz[maxN],top,rL[maxN],rR[maxN],nodecnt;
SegmentData S[maxN*10];

ll Query(int x,int l,int r,int ql,int qr,Point A);
Convex Merge(Convex A,Convex B);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	char opc;
	scanf("%d %c",&n,&opc);
	ll lstans=0;
	int ncnt=0;
	while (n--) {
		char opt;
		scanf(" %c",&opt);
		if (opt=='A') {
			int x,y;
			scanf("%d%d",&x,&y);
			if (opc!='E') x^=lstans,y^=lstans;
			//cerr<<x<<" "<<y<<endl;
			++top;
			++ncnt;
			rL[top]=rR[top]=ncnt;
			Sz[top]=1;
			rt[top]=++nodecnt;
			S[nodecnt].up.opt=1;
			S[nodecnt].up.push_back((Point) {
				x,y
			});
			S[nodecnt].down.opt=2;
			S[nodecnt].down.push_back((Point) {
				x,y
			});
			while ((top>1)&&(Sz[top]==Sz[top-1])) {
				int u=++nodecnt;
				S[u].up.opt=1;
				S[u].down.opt=2;
				S[u].mid=rR[top-1];
				S[u].up=Merge(S[rt[top]].up,S[rt[top-1]].up);
				S[u].down=Merge(S[rt[top]].down,S[rt[top-1]].down);
				S[u].ls=rt[top-1];
				S[u].rs=rt[top];
				rR[top-1]=rR[top];
				Sz[top-1]+=Sz[top];
				--top;
				rt[top]=u;
			}
		} else {
			int x,y,l,r;
			scanf("%d%d%d%d",&x,&y,&l,&r);
			if (opc!='E') x^=lstans,y^=lstans,l^=lstans,r^=lstans;
			ll Ans=-INF;
			for (int i=1; i<=top; i++)
				if ((rR[i]>=l)&&(rL[i]<=r)) Ans=max(Ans,Query(rt[i],rL[i],rR[i],max(l,rL[i]),min(r,rR[i]),((Point) {
					x,y
				})));
			lstans=Ans&(0x7fffffff);
			printf("%lld\n",Ans);
		}
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
bool operator == (Point A,Point B)
{
	return (A.x==B.x)&&(A.y==B.y);
}
ll Cross(Point A,Point B)
{
	return 1ll*A.x*B.y-1ll*A.y*B.x;
}
ll Prod(Point A,Point B)
{
	return 1ll*A.x*B.x+1ll*A.y*B.y;
}
ll Query(int x,int l,int r,int ql,int qr,Point A)
{
	if ((l==ql)&&(r==qr)) return max(S[x].up.query(A),S[x].down.query(A));
	if (qr<=S[x].mid) return Query(S[x].ls,l,S[x].mid,ql,qr,A);
	else if (ql>=S[x].mid+1) return Query(S[x].rs,S[x].mid+1,r,ql,qr,A);
	else return max(Query(S[x].ls,l,S[x].mid,ql,S[x].mid,A),Query(S[x].rs,S[x].mid+1,r,S[x].mid+1,qr,A));
}
bool cmp(Point A,Point B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
Convex Merge(Convex A,Convex B)
{
	Convex R;
	R.opt=A.opt;
	R.V.clear();
	int sz1=A.V.size()-1,sz2=B.V.size()-1,p1=0,p2=0;

	while ((p1<=sz1)||(p2<=sz2))
		if ((p2==sz2+1)||((p1<=sz1)&&(cmp(A.V[p1],B.V[p2])))) R.push_back(A.V[p1++]);
		else R.push_back(B.V[p2++]);
	//*/
	return R;
}
