#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long
#define ls (x<<1)
#define rs (ls|1)

const int maxN=505000;
const int inf=2147483647;
const ll INF=2000000000;

class SegmentData
{
public:
	int mx,smx,mn,smn,pls,mxt,mnt,sz;
	ll sum;
};

int n,m,A[maxN];
SegmentData S[maxN<<2];

void Build(int x,int l,int r);
void Update(int x);
void Plus(int x,ll k);
void Pushmn(int x,ll k);
void Pushmx(int x,ll k);
void PushDown(int x);
void Add(int x,int l,int r,int ql,int qr,ll k);
void Max(int x,int l,int r,int ql,int qr,ll k);
void Min(int x,int l,int r,int ql,int qr,ll k);
ll Query(int x,int l,int r,int ql,int qr,int opt);

int main()
{
	//freopen("15.in","r",stdin);freopen("out","w",stdout);
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%d",&A[i]);
	Build(1,1,n);
	scanf("%d",&m);
	while (m--) {
		//cout<<"running on :"<<m<<endl;
		int opt,l,r,x;
		scanf("%d%d%d",&opt,&l,&r);
		if (opt<=3) scanf("%d",&x);
		if (opt==1) Add(1,1,n,l,r,x);
		else if (opt==2) Max(1,1,n,l,r,x);
		else if (opt==3) Min(1,1,n,l,r,x);
		else printf("%lld\n",Query(1,1,n,l,r,opt-3));

		//for (int i=1;i<=n;i++) cout<<Query(1,1,n,i,i,1)<<" ";cout<<endl;
	}
	return 0;
}
void Build(int x,int l,int r)
{
	S[x].sz=r-l+1;
	if (l==r) {
		S[x].mx=S[x].mn=S[x].sum=A[l];
		S[x].mxt=S[x].mnt=1;
		S[x].smx=-INF;
		S[x].smn=INF;
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	Update(x);
	return;
}
void Update(int x)
{
	S[x].mx=max(S[ls].mx,S[rs].mx);
	S[x].mn=min(S[ls].mn,S[rs].mn);
	S[x].mxt=(S[x].mx==S[ls].mx)*S[ls].mxt+(S[x].mx==S[rs].mx)*S[rs].mxt;
	S[x].mnt=(S[x].mn==S[ls].mn)*S[ls].mnt+(S[x].mn==S[rs].mn)*S[rs].mnt;
	S[x].smx=max(S[ls].smx,S[rs].smx);
	S[x].smn=min(S[ls].smn,S[rs].smn);
	if (S[x].mx!=S[ls].mx) S[x].smx=max(S[x].smx,S[ls].mx);
	if (S[x].mx!=S[rs].mx) S[x].smx=max(S[x].smx,S[rs].mx);
	if (S[x].mn!=S[ls].mn) S[x].smn=min(S[x].smn,S[ls].mn);
	if (S[x].mn!=S[rs].mn) S[x].smn=min(S[x].smn,S[rs].mn);
	S[x].sum=S[ls].sum+S[rs].sum;
	return;
}
void Plus(int x,ll k)
{
	S[x].sum+=k*S[x].sz;
	S[x].mx+=k;
	S[x].mn+=k;
	S[x].pls+=k;
	if (S[x].smx!=-INF) S[x].smx+=k;
	if (S[x].smn!=INF) S[x].smn+=k;
	return;
}
void Pushmx(int x,ll k)
{
	if (S[x].mn==S[x].mx) S[x].mn=k;
	if (S[x].smn==S[x].mx) S[x].smn=k;
	S[x].sum+=(k-S[x].mx)*S[x].mxt;
	S[x].mx=k;
	return;
}
void Pushmn(int x,ll k)
{
	if (S[x].mx==S[x].mn) S[x].mx=k;
	if (S[x].smx==S[x].mn) S[x].smx=k;
	S[x].sum+=(k-S[x].mn)*S[x].mnt;
	S[x].mn=k;
	return;
}
void PushDown(int x)
{
	//cout<<"PushDown:"<<x<<endl;
	if (S[x].pls) {
		Plus(ls,S[x].pls);
		Plus(rs,S[x].pls);
		S[x].pls=0;
	}
	if (S[x].mx<S[ls].mx) Pushmx(ls,S[x].mx);
	if (S[x].mx<S[rs].mx) Pushmx(rs,S[x].mx);
	if (S[x].mn>S[ls].mn) Pushmn(ls,S[x].mn);
	if (S[x].mn>S[rs].mn) Pushmn(rs,S[x].mn);
	return;
}
void Add(int x,int l,int r,int ql,int qr,ll k)
{
	if (l==ql&&r==qr) {
		Plus(x,k);
		return;
	}
	PushDown(x);
	int mid=(l+r)>>1;
	if (qr<=mid) Add(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Add(rs,mid+1,r,ql,qr,k);
	else Add(ls,l,mid,ql,mid,k),Add(rs,mid+1,r,mid+1,qr,k);
	Update(x);
	return;
}
void Max(int x,int l,int r,int ql,int qr,ll k)
{
	if (S[x].mn>=k) return;
	//cout<<"Max:"<<x<<" "<<ql<<" "<<qr<<" "<<k<<endl;
	/*
	if (l==r){
		S[x].mn=max(S[x].mn,k);
		S[x].sum=S[x].mx=S[x].mn;
		return;
	}
	//*/

	if (l==ql&&r==qr)
		if (k<S[x].smn) {
			Pushmn(x,k);
			return;
		}
	//*/
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Max(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Max(rs,mid+1,r,ql,qr,k);
	else Max(ls,l,mid,ql,mid,k),Max(rs,mid+1,r,mid+1,qr,k);
	Update(x);
	return;
}
void Min(int x,int l,int r,int ql,int qr,ll k)
{
	if (S[x].mx<=k) return;
	/*
	if (l==r){
		S[x].mn=min(S[x].mn,k);
		S[x].mx=S[x].sum=S[x].mn;
		return;
	}
	//*/

	if (l==ql&&r==qr)
		if (S[x].smx<k) {
			Pushmx(x,k);
			return;
		}
	//*/
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Min(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Min(rs,mid+1,r,ql,qr,k);
	else Min(ls,l,mid,ql,mid,k),Min(rs,mid+1,r,mid+1,qr,k);
	Update(x);
	return;
}
ll Query(int x,int l,int r,int ql,int qr,int opt)
{
	if (l==ql&&r==qr)
		if (opt==1) return S[x].sum;
		else if (opt==2) return S[x].mx;
		else return S[x].mn;
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) return Query(ls,l,mid,ql,qr,opt);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr,opt);
	else if (opt==1) return Query(ls,l,mid,ql,mid,opt)+Query(rs,mid+1,r,mid+1,qr,opt);
	else if (opt==2) return max(Query(ls,l,mid,ql,mid,opt),Query(rs,mid+1,r,mid+1,qr,opt));
	else return min(Query(ls,l,mid,ql,mid,opt),Query(rs,mid+1,r,mid+1,qr,opt));
}
/*
2
1 2
2
2 1 2 2
4 1 2
//*/
