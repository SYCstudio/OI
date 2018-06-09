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
	int mn,lazy;
};

class Data
{
public:
	int h,k;
};

int n,mxH;
Data D[maxN];
SegmentData S[maxN<<2];

bool cmp(Data A,Data B);
void PushDown(int now);
void Update(int now);
void Modify(int now,int l,int r,int ql,int qr,int key);
int GetNum(int now,int l,int r,int pos);
int QueryNum(int now,int l,int r,int key);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&D[i].h,&D[i].k);
	sort(&D[1],&D[n+1],cmp);
	mxH=D[n].h+1;Modify(1,1,mxH,mxH,mxH,-inf);
	for (int i=1;i<=n;i++)
	{
		//cout<<i<<endl;
		int pos=D[i].h-D[i].k+1;
		//cout<<"pos:"<<pos<<endl;
		int num=GetNum(1,1,mxH,pos);
		//cout<<"num:"<<num<<endl;
		int p1=QueryNum(1,1,mxH,num),p2=QueryNum(1,1,mxH,num-1);
		//cout<<"p1:"<<p1<<" p2:"<<p2<<endl;
		if (p2<=D[i].h)
		{
			Modify(1,1,mxH,p2,D[i].h,1);
			Modify(1,1,mxH,p1,p2-pos+p1-1,1);
		}
		else Modify(1,1,mxH,p1,p1+D[i].k-1,1);
		//for (int j=1;j<=mxH;j++) cout<<GetNum(1,1,mxH,j)<<" ";cout<<endl;
	}
	ll Ans=0;
	for (int i=1;i<mxH;i++)
	{
		ll x=GetNum(1,1,mxH,i);
		Ans+=x*(x-1)/2;
	}
	printf("%lld\n",Ans);
	return 0;
}

bool cmp(Data A,Data B){
	return A.h<B.h;
}

void PushDown(int now)
{
	if (S[now].lazy)
	{
		int lz=S[now].lazy;S[now].lazy=0;
		S[lson].lazy+=lz;S[rson].lazy+=lz;
		S[lson].mn+=lz;S[rson].mn+=lz;
	}
	return;
}

void Update(int now)
{
	S[now].mn=min(S[lson].mn,S[rson].mn);
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key)
{
	//cout<<"Modify:"<<now<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<key<<endl;
	if ((l==ql)&&(r==qr)){
		S[now].mn+=key;S[now].lazy+=key;return;
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

int GetNum(int now,int l,int r,int pos)
{
	if (l==r) return S[now].mn;
	PushDown(now);
	int mid=(l+r)>>1;
	if (pos<=mid) return GetNum(lson,l,mid,pos);
	else return GetNum(rson,mid+1,r,pos);
}

int QueryNum(int now,int l,int r,int key)
{
	if (l==r) return l;
	PushDown(now);
	int mid=(l+r)>>1;
	if (S[lson].mn<=key) return QueryNum(lson,l,mid,key);
	else return QueryNum(rson,mid+1,r,key);
}
