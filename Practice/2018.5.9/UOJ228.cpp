#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int inf=2147483647;

class SegmentData
{
public:
	ll sum,siz;
	ll mx,mn;
	ll cov,add;
	SegmentData(){
		cov=-1;return;
	}
};

int n,m;
int Arr[maxN];
SegmentData S[maxN<<2];

void Build(int now,int l,int r);
void Update(int now);
void PushDown(int now);
void Add(int now,ll key);
void Cover(int now,ll key);
void Modify_add(int now,int l,int r,int ql,int qr,ll key);
void Modify_sqrt(int now,int l,int r,int ql,int qr);
ll Query(int now,int l,int r,int ql,int qr); 

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);
	Build(1,1,n);
	for (int i=1;i<=m;i++)
	{
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if (opt==1)
		{
			int x;scanf("%d",&x);
			Modify_add(1,1,n,l,r,x);
		}
		if (opt==2) Modify_sqrt(1,1,n,l,r);
		if (opt==3) printf("%lld\n",Query(1,1,n,l,r));
	}
	return 0;
}

void Build(int now,int l,int r)
{
	S[now].siz=r-l+1;
	if (l==r)
	{
		S[now].mx=S[now].mn=S[now].sum=Arr[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Update(now);return;
}

void Update(int now)
{
	S[now].mn=min(S[lson].mn,S[rson].mn);
	S[now].mx=max(S[lson].mx,S[rson].mx);
	S[now].sum=S[lson].sum+S[rson].sum;
	return;
}

void PushDown(int now)
{
	if (S[now].add!=0)
	{
		Add(lson,S[now].add);Add(rson,S[now].add);
		S[now].add=0;
	}
	if (S[now].cov!=-1)
	{
		Cover(lson,S[now].cov);Cover(rson,S[now].cov);
		S[now].cov=-1;
	}
	return;
}

void Add(int now,ll key)
{
	S[now].mn+=key;S[now].mx+=key;
	S[now].sum+=key*S[now].siz;
	if (S[now].cov!=-1) S[now].cov+=key;
	else S[now].add+=key;
	return;
}

void Cover(int now,ll key)
{
	S[now].mn=S[now].mx=key;
	S[now].sum=key*S[now].siz;
	S[now].add=0;S[now].cov=key;
	return;
}

void Modify_add(int now,int l,int r,int ql,int qr,ll key)
{
	if ((l==ql)&&(r==qr)){
		Add(now,key);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify_add(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify_add(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify_add(lson,l,mid,ql,mid,key);
		Modify_add(rson,mid+1,r,mid+1,qr,key);
	}
	Update(now);return;
}

void Modify_sqrt(int now,int l,int r,int ql,int qr)
{
	if (S[now].mx<=1) return;
	if ((l==ql)&&(r==qr))
	{
		int x1=sqrt(S[now].mx),x2=sqrt(S[now].mn);
		if (x1==x2)
		{
			Cover(now,x1);
			return;
		}
		if (S[now].mx-x1==S[now].mn-x2)
		{
			Add(now,x1-S[now].mx);
			return;
		}
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify_sqrt(lson,l,mid,ql,qr);
	else if (ql>=mid+1) Modify_sqrt(rson,mid+1,r,ql,qr);
	else
	{
		Modify_sqrt(lson,l,mid,ql,mid);
		Modify_sqrt(rson,mid+1,r,mid+1,qr);
	}
	Update(now);return;
}

ll Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now].sum;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}


