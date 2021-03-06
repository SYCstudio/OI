#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
class SegmentData
{
public:
	int sz,t1,t2,l,r;
	double sxy,sx,sx2,sy;
	double CovS,CovT,PS,PT;
	SegmentData()
	{
		t1=t2=CovS=CovT=PS=PT=0;
		return;
	}
};

const int maxN=101000;

int n,m;
int Ix[maxN],Iy[maxN];
SegmentData S[maxN<<2];
double Sm[maxN],Sm2[maxN];

SegmentData operator + (SegmentData A,SegmentData B);
void Build(int x,int l,int r);
void PushDown(int x);
void Plus(int x,double s,double t);
void Cover(int x,double s,double t);
void ModifyP(int x,int l,int r,int ql,int qr,double s,double t);
void ModifyS(int x,int l,int r,int ql,int qr,double s,double t);
SegmentData Query(int x,int l,int r,int ql,int qr);
double Calc(SegmentData A);

int main()
{
	//freopen("5.in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) Sm[i]=Sm[i-1]+i,Sm2[i]=Sm2[i-1]+1ll*i*i;
	for (int i=1; i<=n; i++) scanf("%d",&Ix[i]);
	for (int i=1; i<=n; i++) scanf("%d",&Iy[i]);
	Build(1,1,n);
	while (m--) {
		int opt,l,r,s,t;
		scanf("%d%d%d",&opt,&l,&r);
		if (opt>=2) scanf("%d%d",&s,&t);
		if (opt==1) printf("%.10lf\n",Calc(Query(1,1,n,l,r)));
		if (opt==2) ModifyP(1,1,n,l,r,s,t);
		if (opt==3) ModifyS(1,1,n,l,r,s,t);
	}
	return 0;
}
SegmentData operator + (SegmentData A,SegmentData B)
{
	SegmentData C;
	C.sz=A.sz+B.sz;
	C.sxy=A.sxy+B.sxy;
	C.sx=A.sx+B.sx;
	C.sy=A.sy+B.sy;
	C.sx2=A.sx2+B.sx2;
	C.l=A.l;
	C.r=B.r;
	return C;
}
#define ls (x<<1)
#define rs (ls|1)
void Build(int x,int l,int r)
{
	if (l==r) {
		S[x].sz=1;
		S[x].sxy=1ll*Ix[l]*Iy[l];
		S[x].sx=Ix[l];
		S[x].sy=Iy[l];
		S[x].l=S[x].r=l;
		S[x].sx2=1ll*Ix[l]*Ix[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	S[x]=S[ls]+S[rs];
	return;
}
void PushDown(int x)
{
	if (S[x].t2) {
		Cover(ls,S[x].CovS,S[x].CovT);
		Cover(rs,S[x].CovS,S[x].CovT);
		S[x].t2=S[x].CovS=S[x].CovT=0;
	}
	if (S[x].t1) {
		Plus(ls,S[x].PS,S[x].PT);
		Plus(rs,S[x].PS,S[x].PT);
		S[x].t1=S[x].PS=S[x].PT=0;
	}
	return;
}
void Plus(int x,double s,double t)
{
	S[x].t1=1;
	S[x].PS+=s;
	S[x].PT+=t;
	S[x].sxy=S[x].sxy+S[x].sx*t+S[x].sy*s+S[x].sz*s*t;
	S[x].sx2=S[x].sx2+2ll*s*S[x].sx+S[x].sz*s*s;
	S[x].sx=S[x].sx+S[x].sz*s;
	S[x].sy=S[x].sy+S[x].sz*t;
	return;
}
void Cover(int x,double s,double t)
{
	S[x].t2=1;
	S[x].t1=S[x].PS=S[x].PT=0;
	S[x].CovS=s;
	S[x].CovT=t;
	S[x].sxy=S[x].sz*s*t+(s+t)*(Sm[S[x].r]-Sm[S[x].l-1])+Sm2[S[x].r]-Sm2[S[x].l-1];
	S[x].sx2=s*s*S[x].sz+s*2*(Sm[S[x].r]-Sm[S[x].l-1])+Sm2[S[x].r]-Sm2[S[x].l-1];
	S[x].sx=S[x].sz*s+Sm[S[x].r]-Sm[S[x].l-1];
	S[x].sy=S[x].sz*t+Sm[S[x].r]-Sm[S[x].l-1];
	return;
}
void ModifyP(int x,int l,int r,int ql,int qr,double s,double t)
{
	if (l==ql&&r==qr) {
		Plus(x,s,t);
		return;
	}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) ModifyP(ls,l,mid,ql,qr,s,t);
	else if (ql>=mid+1) ModifyP(rs,mid+1,r,ql,qr,s,t);
	else ModifyP(ls,l,mid,ql,mid,s,t),ModifyP(rs,mid+1,r,mid+1,qr,s,t);
	S[x]=S[ls]+S[rs];
	return;
}
void ModifyS(int x,int l,int r,int ql,int qr,double s,double t)
{
	if (l==ql&&r==qr) {
		Cover(x,s,t);
		return;
	}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) ModifyS(ls,l,mid,ql,qr,s,t);
	else if (ql>=mid+1) ModifyS(rs,mid+1,r,ql,qr,s,t);
	else ModifyS(ls,l,mid,ql,mid,s,t),ModifyS(rs,mid+1,r,mid+1,qr,s,t);
	S[x]=S[ls]+S[rs];
	return;
}
SegmentData Query(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return S[x];
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return Query(ls,l,mid,ql,mid)+Query(rs,mid+1,r,mid+1,qr);
}
double Calc(SegmentData A)
{
	double x=(double)A.sx/(double)A.sz,y=(double)A.sy/(double)A.sz;
	double up=A.sxy-x*A.sy-y*A.sx+A.sz*x*y;
	double down=A.sx2-x*2*A.sx+A.sz*x*x;
	return up/down;
}
