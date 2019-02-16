#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson S[now].ls
#define rson S[now].rs

const int maxN=20110;
const int inf=2147483647;

class Data
{
public:
	int pos,key;
};

class SegmentData
{
public:
	int sum;
	int presum,sufsum;
	int ls,rs;
};

int n,nodecnt;
int root[maxN];
Data D[maxN];
SegmentData S[maxN*100];

bool operator < (Data A,Data B);
void Build(int &now,int l,int r);
void Update(int now);
void Modify(int &now,int l,int r,int pos,int key);
int Query_sum(int now,int l,int r,int ql,int qr);
int Query_pre(int now,int l,int r,int ql,int qr);
int Query_suf(int now,int l,int r,int ql,int qr);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&D[i].key);
		D[i].pos=i;
	}
	sort(&D[1],&D[n+1]);
	Build(root[1],1,n);
	for (int i=2;i<=n;i++)
	{
		root[i]=root[i-1];
		Modify(root[i],1,n,D[i-1].pos,-2);
	}
	/*
	cout<<endl;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) cout<<Query_sum(root[i],1,n,j,j)<<" ";
		cout<<endl;
	}
	//*/
	int lastans=0;
	int Q;scanf("%d",&Q);
	while (Q--)
	{
		int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
		a=(a+lastans)%n;b=(b+lastans)%n;c=(c+lastans)%n;d=(d+lastans)%n;
		if (a>b) swap(a,b);if (a>c) swap(a,c);if (a>d) swap(a,d);
		if (b>c) swap(b,c);if (b>d) swap(b,d);if (c>d) swap(c,d);
		a++;b++;c++;d++;
		//cout<<"["<<a<<","<<b<<"] ["<<c<<","<<d<<"] "<<endl;
		int l=1,r=n,Ans;
		do
		{
			int mid=(l+r)>>1;
			//cout<<mid<<":"<<Query_sum(root[mid],1,n,b,c)<<" "<<Query_suf(root[mid],1,n,a,b-1)<<" "<<Query_pre(root[mid],1,n,c+1,d)<<endl;
			int sum=Query_sum(root[mid],1,n,b,c)+Query_suf(root[mid],1,n,a,b-1)+Query_pre(root[mid],1,n,c+1,d);
			if (sum>=0) Ans=mid,l=mid+1;
			else r=mid-1;
		}
		while (l<=r);
		cout<<(lastans=D[Ans].key)<<endl;
	}
	return 0;
}

bool operator < (Data A,Data B)
{
	if (A.key!=B.key) return A.key<B.key;
	return A.pos<B.pos;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r){
		S[now].sum=S[now].presum=S[now].sufsum=1;return;
	}
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	Update(now);return;
}

void Update(int now)
{
	S[now].sum=S[lson].sum+S[rson].sum;
	S[now].presum=max(S[lson].presum,S[lson].sum+S[rson].presum);
	S[now].sufsum=max(S[rson].sufsum,S[rson].sum+S[lson].sufsum);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	if (l==r)
	{
		S[now].sum+=key;
		S[now].presum=S[now].sufsum=max(0,S[now].sum);
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Update(now);return;
}

int Query_sum(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_sum(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_sum(rson,mid+1,r,ql,qr);
	else return Query_sum(lson,l,mid,ql,mid)+Query_sum(rson,mid+1,r,mid+1,qr);
}

int Query_pre(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].presum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_pre(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_pre(rson,mid+1,r,ql,qr);
	else return max(Query_pre(lson,l,mid,ql,mid),Query_sum(lson,l,mid,ql,mid)+Query_pre(rson,mid+1,r,mid+1,qr));
}

int Query_suf(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sufsum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query_suf(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query_suf(rson,mid+1,r,ql,qr);
	else return max(Query_suf(lson,l,mid,ql,mid)+Query_sum(rson,mid+1,r,mid+1,qr),Query_suf(rson,mid+1,r,mid+1,qr));
}
