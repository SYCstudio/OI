#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define Dct(x,Num,cnt) (lower_bound(&Num[1],&Num[cnt+1],x)-Num)
const int maxN=100010;

class Point
{
public:
	int x,y,c;
};
class SegmentData
{
public:
	int ls,rs,cnt;
};

int n,K,Ans;
Point P[maxN];
int numx,Nx[maxN],numy,Ny[maxN],Mark[maxN];
int rt[maxN],nodecnt,lft[maxN],rht[maxN],Cnt[maxN];
SegmentData Sg[maxN*20];

void Calc();
bool cmpc(Point A,Point B);
bool cmpx(Point A,Point B);
bool cmpy(Point A,Point B);
void Modify(int &x,int l,int r,int p);
int Query(int lx,int rx,int y);
int Query(int x,int l,int r,int ql,int qr);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		Ans=0;
		scanf("%d%d",&n,&K);
		for (int i=1; i<=n; i++) scanf("%d%d%d",&P[i].x,&P[i].y,&P[i].c);
		numx=numy=0;
		for (int i=1; i<=n; i++) Nx[++numx]=P[i].x,Ny[++numy]=P[i].y;
		sort(&Nx[1],&Nx[numx+1]);
		numx=unique(&Nx[1],&Nx[numx+1])-Nx-1;
		sort(&Ny[1],&Ny[numy+1]);
		numy=unique(&Ny[1],&Ny[numy+1])-Ny-1;
		for (int i=1; i<=n; i++) P[i].x=lower_bound(&Nx[1],&Nx[numx+1],P[i].x)-Nx,P[i].y=lower_bound(&Ny[1],&Ny[numy+1],P[i].y)-Ny;
		Calc();
		for (int i=1; i<=n; i++) P[i].y=numy-P[i].y+1;
		Calc();
		printf("%d\n",Ans);
	}
}
void Calc()
{
	nodecnt=0;
	memset(Mark,0,sizeof(Mark));
	sort(&P[1],&P[n+1],cmpx);
	for (int i=1,j=1; i<=numx; i++) {
		rt[i]=rt[i-1];
		while (j<=n&&P[j].x==i) Modify(rt[i],1,numy,P[j].y),++j;
	}
	sort(&P[1],&P[n+1],cmpc);
	for (int l=1,r; l<=n; l=r+1) {
		r=l;
		while (r+1<=n&&P[r+1].c==P[l].c) ++r;
		sort(&P[l],&P[r+1],cmpx);
		Mark[P[l].c]=1;
		for (int i=l; i<r; i++) Ans=max(Ans,Query(P[i].x+1,P[i+1].x-1,1));
		Ans=max(Ans,Query(1,P[l].x-1,1));
		Ans=max(Ans,Query(P[r].x+1,numx,1));

		for (int i=l; i<r; i++)
			if (P[i].x!=P[i+1].x) {
				int a=P[i].x,b=P[i+1].x;
				rht[a]=b;
				lft[b]=a;
			}
		lft[P[l].x]=0;
		rht[P[r].x]=0;
		for (int i=l; i<=r; i++) ++Cnt[P[i].x];

		sort(&P[l],&P[r+1],cmpy);
		for (int i=l; i<=r; i++) {
			int px=P[i].x;
			if (--Cnt[px]) continue;
			int ql=lft[px]+1,qr=rht[px]-1;
			if (lft[px]==0) ql=1;
			if (rht[px]==0) qr=numx;
			Ans=max(Ans,Query(ql,qr,P[i].y+1));
			ql=lft[px];
			qr=rht[px];
			if (ql) rht[ql]=qr;
			if (qr) lft[qr]=ql;
		}
	}
	for (int i=1; i<=K; i++) if (!Mark[i]) Ans=n;
	return;
}
bool cmpc(Point A,Point B)
{
	return A.c<B.c;
}
bool cmpx(Point A,Point B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
bool cmpy(Point A,Point B)
{
	if (A.y!=B.y) return A.y<B.y;
	return A.x<B.x;
}
void Modify(int &x,int l,int r,int p)
{
	Sg[++nodecnt]=Sg[x];
	x=nodecnt;
	++Sg[x].cnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Modify(Sg[x].ls,l,mid,p);
	else Modify(Sg[x].rs,mid+1,r,p);
	return;
}
int Query(int lx,int rx,int y)
{
	if (lx>rx||y>numy) return 0;
	return Query(rt[rx],1,numy,y,numy)-Query(rt[lx-1],1,numy,y,numy);
}
int Query(int x,int l,int r,int ql,int qr)
{
	if (x==0) return 0;
	if (l==ql&&r==qr) return Sg[x].cnt;
	int mid=(l+r)>>1;
	if (ql<=mid) return Query(Sg[x].ls,l,mid,ql,mid)+Sg[Sg[x].rs].cnt;
	else return Query(Sg[x].rs,mid+1,r,ql,qr);
}