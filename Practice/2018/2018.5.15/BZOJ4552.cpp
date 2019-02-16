#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
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
    int sum[2];
    int cov,siz;
};

class Option
{
public:
	int opt,l,r;
};

int n,Mid,m,Pos;
int numcnt,Num[maxN],Arr[maxN];
SegmentData S[maxN<<2];
Option O[maxN];

bool Check(int mid);
void Build(int now,int l,int r);
void Update(int now);
void PushDown(int now);
void Cover(int now,int key);
int Query(int now,int l,int r,int ql,int qr);
void Modify(int now,int l,int r,int ql,int qr,int key);

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
	{
	    scanf("%d",&Arr[i]);
		Num[i]=Arr[i];
	}
	for (int i=1;i<=m;i++) scanf("%d%d%d",&O[i].opt,&O[i].l,&O[i].r);
	scanf("%d",&Pos);
	sort(&Num[1],&Num[n+1]);
	numcnt=unique(&Num[1],&Num[n+1])-Num-1;
	int L=1,R=numcnt;
	int Ans=0;
	do
	{
		int mid=(L+R)>>1;
		if (Check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);
	printf("%d\n",Num[Ans]);
	return 0;
}

bool Check(int mid)
{
	Mid=mid;
	Build(1,1,n);
	//cout<<Mid<<" "<<Num[Mid]<<endl;
	//for (int i=1;i<=n;i++) cout<<(Query(1,1,n,i,i)==0)<<" ";cout<<endl;
	for (int i=1;i<=m;i++)
	{
		int num=Query(1,1,n,O[i].l,O[i].r);
		if (O[i].opt==0)
		{
			if (num) Modify(1,1,n,O[i].l,O[i].l+num-1,0);
			if (num!=O[i].r-O[i].l+1) Modify(1,1,n,O[i].l+num,O[i].r,1);
		}
		else
		{
			num=O[i].r-O[i].l+1-num;
			if (num) Modify(1,1,n,O[i].l,O[i].l+num-1,1);
			if (num!=O[i].r-O[i].l+1) Modify(1,1,n,O[i].l+num,O[i].r,0);
		}
		//for (int j=1;j<=n;j++) cout<<(Query(1,1,n,j,j)==0)<<" ";cout<<endl;
	}
	return (Query(1,1,n,Pos,Pos)==1);
}

void Build(int now,int l,int r)
{
	S[now].cov=-1;
	S[now].sum[0]=S[now].sum[1]=0;
	S[now].siz=r-l+1;
	if (l==r)
	{
		S[now].sum[Arr[l]>Num[Mid]]=1;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Update(now);return;
}

void Update(int now)
{
	S[now].sum[0]=S[lson].sum[0]+S[rson].sum[0];
	S[now].sum[1]=S[lson].sum[1]+S[rson].sum[1];
	return;
}

int Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now].sum[0];
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}

void PushDown(int now)
{
	if (S[now].cov!=-1)
	{
		Cover(lson,S[now].cov);Cover(rson,S[now].cov);
		S[now].cov=-1;
	}
	return;
}

void Cover(int now,int key)
{
	S[now].cov=key;
	S[now].sum[key]=S[now].siz;S[now].sum[key^1]=0;
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
	if ((l==ql)&&(r==qr)){
		Cover(now,key);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	Update(now);return;
}
