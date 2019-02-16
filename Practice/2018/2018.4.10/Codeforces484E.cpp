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
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=100100;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs;
};

class Data
{
public:
	ll sum;
	ll presum,sufsum;
	ll mx;
};

class NumData
{
public:
	int pos,key;
};

int n;
int nodecnt=0,root[maxN];
int numcnt=0,Num[maxN];
SegmentData S[maxN*50];
Data D[maxN*50];
NumData ND[maxN];

bool operator < (NumData A,NumData B);
Data operator + (Data A,Data B);

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);
Data Query(int now,int l,int r,int ql,int qr);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&ND[i].key);
		Num[++numcnt]=ND[i].key;ND[i].pos=i;
	}
	sort(&ND[1],&ND[n+1]);
	sort(&Num[1],&Num[numcnt+1]);
	//numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	Build(root[1],1,n);
	for (int i=2;i<=n;i++)
	{
		root[i]=root[i-1];
		Modify(root[i],1,n,ND[i-1].pos,-inf);
	}
	int Q;scanf("%d",&Q);
	while (Q--)
	{
		int ql,qr,k;scanf("%d%d%d",&ql,&qr,&k);
		int l=1,r=n,Ans;
		//cout<<"Q:["<<ql<<","<<qr<<"] "<<k<<endl;
		do
		{
			int mid=(l+r)>>1;
			Data D=Query(root[mid],1,n,ql,qr);
			//cout<<"["<<l<<","<<r<<"] "<<D.mx<<" "<<D.sum<<" "<<D.presum<<" "<<D.sufsum<<endl;
			if (D.mx>=k) Ans=mid,l=mid+1;
			else r=mid-1;
		}
		while (l<=r);
		printf("%d\n",ND[Ans].key);
	}
	return 0;
}

bool operator < (NumData A,NumData B)
{
	if (A.key!=B.key) return A.key<B.key;
	return A.pos<B.pos;
}

Data operator + (Data A,Data B)
{
	Data Ret;
	Ret.sum=A.sum+B.sum;
	Ret.presum=max(A.presum,A.sum+B.presum);
	Ret.sufsum=max(A.sufsum+B.sum,B.sufsum);
	Ret.mx=max(max(A.mx,B.mx),A.sufsum+B.presum);
	return Ret;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r){
		D[now].sum=D[now].presum=D[now].sufsum=D[now].mx=1;return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	D[now]=D[lson]+D[rson];
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	if (l==r)
	{
		D[now].sum=key;
		D[now].presum=D[now].sufsum=D[now].mx=max(key,0);
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	D[now]=D[lson]+D[rson];
	return;
}

Data Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return D[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
