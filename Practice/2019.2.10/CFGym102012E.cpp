#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
#define ls (x<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
const int maxN=101000;
class SegmentData
{
public:
	ll mx,cnt,pls,cov,sz,tmx,tcnt;
};
int n,Input[maxN];
class SegmentTree
{
public:
	SegmentData S[maxN<<2];
	int Get(int x,int l,int r,int ql,int qr,ll limit)
	{
		if (l==ql&&r==qr) S[x].tcnt=S[x].cnt,S[x].tmx=S[x].mx;
		if (S[x].tmx<limit) return 0;
		if (l==r) return 1;
		PushDown(x);
		if (l<=mid&&r>mid) {
			if (ql<=l&&qr>=mid) S[ls].tmx=S[ls].mx,S[ls].tcnt=S[ls].cnt;
			if (S[ls].tmx>=limit) return Get(ls,l,mid,ql,mid,limit)+S[x].tcnt-S[ls].tcnt;
			else return Get(rs,mid+1,r,mid+1,qr,limit);
		}
		if (qr<=mid) return Get(ls,l,mid,ql,qr,limit);
		else return Get(ls,l,mid,ql,mid,limit);
	}
	void Update(int x,int l,int r)
	{
		S[x].mx=max(S[ls].mx,S[rs].mx);
		S[x].cnt=S[ls].cnt+Get(rs,mid+1,r,mid+1,r,S[ls].mx);
		S[x].tmx=S[x].mx;
		S[x].tcnt=S[x].cnt;
		return;
	}
	void Build(int x,int l,int r)
	{
		S[x].mx=S[x].cnt=S[x].pls=S[x].cov=S[x].sz=S[x].tmx=S[x].tcnt=0;
		S[x].sz=r-l+1;
		if (l==r) {
			S[x].mx=Input[l];
			S[x].cnt=1;
			return;
		}
		Build(ls,l,mid);
		Build(rs,mid+1,r);
		Update(x,l,r);
		return;
	}
	void Cover(int x,ll k)
	{
		S[x].mx=k;
		S[x].cnt=S[x].sz;
		S[x].pls=0;
		S[x].cov=k;
		return;
	}
	void Plus(int x,ll k)
	{
		S[x].mx+=k;
		if (S[x].cov) S[x].cov+=k;
		else S[x].pls+=k;
		return;
	}
	void PushDown(int x)
	{
		if (S[x].cov) {
			Cover(ls,S[x].cov);
			Cover(rs,S[x].cov);
			S[x].cov=0;
		}
		if (S[x].pls) {
			Plus(ls,S[x].pls);
			Plus(rs,S[x].pls);
			S[x].pls=0;
		}
		return;
	}
	ll Mx(int x,int l,int r,int ql,int qr)
	{
		if (l==ql&&r==qr) return S[x].mx;
		PushDown(x);
		if (qr<=mid) return Mx(ls,l,mid,ql,qr);
		else if (ql>=mid+1) return Mx(rs,mid+1,r,ql,qr);
		else return max(Mx(ls,l,mid,ql,mid),Mx(rs,mid+1,r,mid+1,qr));
	}
	void SetSame(int x,int l,int r,int ql,int qr,ll key)
	{
		if (l==ql&&r==qr) {
			Cover(x,key);
			return;
		}
		PushDown(x);
		if (qr<=mid) SetSame(ls,l,mid,ql,qr,key);
		else if (ql>=mid+1) SetSame(rs,mid+1,r,ql,qr,key);
		else SetSame(ls,l,mid,ql,mid,key),SetSame(rs,mid+1,r,mid+1,qr,key);
		Update(x,l,r);
		return;
	}
	void RangePlus(int x,int l,int r,int ql,int qr,ll key)
	{
		if (l==ql&&r==qr) {
			Plus(x,key);
			return;
		}
		PushDown(x);
		if (qr<=mid) RangePlus(ls,l,mid,ql,qr,key);
		else if (ql>=mid+1) RangePlus(rs,mid+1,r,ql,qr,key);
		else RangePlus(ls,l,mid,ql,mid,key),RangePlus(rs,mid+1,r,mid+1,qr,key);
		Update(x,l,r);
		return;
	}
	void RangeQuery(int x,int l,int r,int ql,int qr)
	{
		if (l==ql&&r==qr) {
			//cout<<"Q At:"<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<":"<<S[x].mx<<" "<<S[x].tcnt<<endl;
			S[x].tcnt=S[x].cnt;
			S[x].tmx=S[x].mx;
			return;
		}
		PushDown(x);
		if (qr<=mid) {
			RangeQuery(ls,l,mid,ql,qr);
			S[x].tcnt=S[ls].tcnt;
			S[x].tmx=S[ls].tmx;
		} else if (ql>=mid+1) {
			RangeQuery(rs,mid+1,r,ql,qr);
			S[x].tcnt=S[rs].tcnt;
			S[x].tmx=S[rs].tmx;
		} else {
			RangeQuery(ls,l,mid,ql,mid);
			RangeQuery(rs,mid+1,r,mid+1,qr);
			S[x].tmx=max(S[ls].tmx,S[rs].tmx);
			S[x].tcnt=S[ls].tcnt+Get(rs,mid+1,r,mid+1,qr,S[ls].tmx);
		}
		//cout<<"RangeQuery:"<<l<<" "<<r<<" "<<ql<<" "<<qr<<":"<<S[x].tmx<<" "<<S[x].tcnt<<endl;
		return;
	}
	int Query(int x,int l,int r)
	{
		if (l>r) return 0;
		//for (int i=1;i<=n;i++) cout<<Mx(1,1,n,i,i)<<" ";cout<<endl;
		ll mx=Mx(1,1,n,x,l),keyx=Mx(1,1,n,x,x);
		//cout<<"mx:"<<mx<<" keyx:"<<keyx<<endl;
		if (mx==keyx) {
			//cout<<"Case1"<<endl;
			int ql=l,qr=r,pos=r+1;
			while (ql<=qr) {
				int md=(ql+qr)>>1;
				if (Mx(1,1,n,l,md)>keyx) pos=md,qr=md-1;
				else ql=md+1;
			}
			int Ans=pos-l;
			if (pos<=r) {
				RangeQuery(1,1,n,pos,r);
				Ans+=S[1].tcnt;
			}
			return Ans;
		} else {
			//cout<<"Case2"<<endl;
			ll lft=Mx(1,1,n,l,l);
			//cout<<"lft:"<<lft<<endl;
			SetSame(1,1,n,l,l,mx);
			RangeQuery(1,1,n,l,r);
			int Ans=S[1].tcnt-(lft<mx);
			SetSame(1,1,n,l,l,lft);
			//cout<<"Ans:"<<Ans<<endl;
			return Ans;
		}
	}
};

int Q;
SegmentTree T1,T2;

int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d%d",&n,&Q);
		for (int i=1; i<=n; i++) scanf("%d",&Input[i]);
		T1.Build(1,1,n);
		reverse(&Input[1],&Input[n+1]);
		T2.Build(1,1,n);
		while (Q--) {
			int opt,l,r,k;
			scanf("%d%d%d%d",&opt,&l,&r,&k);
			if (opt==1) T1.RangePlus(1,1,n,l,r,k),T2.RangePlus(1,1,n,n-r+1,n-l+1,k);
			if (opt==2) T1.SetSame(1,1,n,l,r,k),T2.SetSame(1,1,n,n-r+1,n-l+1,k);
			if (opt==3) {
				if (k>=l&&k<=r) printf("%d\n",T1.Query(k,k+1,r)+T2.Query(n-k+1,n-(k-1)+1,n-l+1)+1);
				else if (k<l) printf("%d\n",T1.Query(k,l,r));
				else printf("%d\n",T2.Query(n-k+1,n-r+1,n-l+1));
			}
		}
	}
	return 0;
}