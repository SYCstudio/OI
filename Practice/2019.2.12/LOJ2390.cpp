#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;
typedef long long ll;
#define Min(x,y) x=min(x,y)
#define Max(x,y) x=max(x,y)
const int maxN=310;
const int inf=1000000000;
const ll INF=1e18;
class Range
{
public:
	ll l,r,a,b,c;
};
class Pos
{
public:
	ll x,y;
};
class MonotonusQueue
{
public:
	int l,r;
	pair<int,ll> Q[maxN*2];
	void Init()
	{
		l=1;
		r=0;
		return;
	}
	void Push(int x,ll y)
	{
		while (l<=r&&Q[r].second<=y) --r;
		Q[++r]=make_pair(x,y);
		//cout<<"Afterpush:";for (int i=l;i<=r;i++) cout<<"("<<Q[i].first<<","<<Q[i].second<<") ";cout<<endl;
		return;
	}
	ll Front(int x)
	{
		while (l<=r&&Q[l].first<x) ++l;
		if (l>r) return INF;
		return Q[l].second;
	}
};
int n,cntx=0;
Pos P[maxN];
ll Ca[maxN][maxN],Cb[maxN][maxN],Cc[maxN][maxN];
ll W,H,Xn[maxN],Ans=1e18;
MonotonusQueue Qa,Qb,Qc;
Range R[maxN*2];
queue<ll> Qx;

bool cmpx(Pos A,Pos B);
bool cmpy(Pos A,Pos B);
void Calc(ll len);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%lld%lld%d",&W,&H,&n);
	for (int i=1; i<=n; i++) scanf("%lld%lld",&P[i].x,&P[i].y);
	sort(&P[1],&P[n+1],cmpx);
	for (int i=1,j; i<=n; i=j+1) {
		j=i;
		while (j<n&&P[j+1].x==P[i].x) ++j;
		++cntx;
		Xn[cntx]=P[i].x;
	}
	sort(&P[1],&P[n+1],cmpy);
	for (int i=0; i<maxN; i++) for (int j=0; j<maxN; j++) Ca[i][j]=Cb[i][j]=Cc[i][j]=INF;
	for (int l=1; l<=cntx; l++)
		for (int r=l; r<=cntx; r++) {
			ll lsty=-1;
			Cc[l][r]=0;
			for (int i=1; i<=n; i++)
				if (P[i].x>=Xn[l]&&P[i].x<=Xn[r]) {
					if (lsty==-1) Ca[l][r]=P[i].y-1;
					else Max(Cc[l][r],P[i].y-lsty-1);
					lsty=P[i].y;
				}
			Cb[l][r]=H-lsty;
			//cout<<"("<<l<<","<<r<<") "<<Ca[l][r]<<" "<<Cb[l][r]<<" "<<Cc[l][r]<<endl;
		}
	ll mxter=0;
	for (int i=1; i<cntx; i++) Max(mxter,Xn[i+1]-Xn[i]);
	Calc(max(Xn[1]-1+W-Xn[cntx],mxter));
	Calc(W-1);
	for (int i=1; i<=cntx; i++) {
		Calc(Xn[i]-1);
		Calc(W-Xn[i]);
		for (int j=i+1; j<=cntx; j++) Calc(Xn[j]-Xn[i]-1),Calc(Xn[j]-Xn[i]-1+W),Calc(Xn[i]-1+W-Xn[j]);
	}
	printf("%lld\n",Ans);
	return 0;
}
bool cmpx(Pos A,Pos B)
{
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}
bool cmpy(Pos A,Pos B)
{
	if (A.y!=B.y) return A.y<B.y;
	return A.x<B.x;
}
void Calc(ll len)
{
	if (len<0) return;
	//cout<<"Calc:"<<len<<endl;
	int rcnt=0,p=1,lst=1;
	while (!Qx.empty()) Qx.pop();
	while (p<=cntx||!Qx.empty())
		if (Qx.empty()||(p<=cntx&&Xn[p]<=Xn[Qx.front()]+len)) {
			int ql=Qx.empty()?0:Qx.front(),qr=Qx.empty()?0:Qx.back();
			//cout<<"Case1:"<<lst<<" "<<p<<" "<<Xn[p]<<" "<<ql<<" "<<qr<<endl;
			if (lst<Xn[p]) R[++rcnt]=((Range) {
				lst,Xn[p]-1,Ca[ql][qr],Cb[ql][qr],Cc[ql][qr]
			});
			Qx.push(p);
			lst=Xn[p];
			++p;
			//cout<<"r:"<<rcnt<<endl;
		} else {
			int ql=Qx.front(),qr=Qx.back();
			//cout<<"Case2:"<<lst<<" "<<ql<<" "<<qr<<endl;
			R[++rcnt]=((Range) {
				lst,Xn[Qx.front()]+len,Ca[ql][qr],Cb[ql][qr],Cc[ql][qr]
			});
			lst=Xn[Qx.front()]+len+1;
			Qx.pop();
			//cout<<"r:"<<rcnt<<endl;
		}
	//for (int i=1;i<=rcnt;i++) cout<<"("<<R[i].l<<","<<R[i].r<<") "<<R[i].a<<" "<<R[i].b<<" "<<R[i].c<<endl;

	Qa.Init();
	Qb.Init();
	Qc.Init();
	int p1=1,p2=0;
	for (p1=1; p1<=rcnt; p1++) {
		while (p2<rcnt&&R[p2].r<R[p1].l+W-1) {
			++p2;
			Qa.Push(R[p2].r,R[p2].a);
			Qb.Push(R[p2].r,R[p2].b);
			Qc.Push(R[p2].r,R[p2].c);
		}
		if (R[p2].r<R[p1].l+W-1) break;
		//cout<<"GET:"<<p1<<" "<<p2<<":"<<len<<"+max("<<Qa.Front(R[p1].l)<<"+"<<Qb.Front(R[p1].l)<<","<<Qc.Front(R[p1].l)<<")="<<len+max(Qa.Front(R[p1].l)+Qb.Front(R[p1].l),Qc.Front(R[p1].l))<<endl;
		Ans=min(Ans,len+max(Qa.Front(R[p1].l)+Qb.Front(R[p1].l),Qc.Front(R[p1].l)));
	}
	return;
}