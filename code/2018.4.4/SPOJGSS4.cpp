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

const int maxN=201000;
const int inf=2147483647;

class SegmentData
{
public:
	ll mx,sum;
};

int n,m;
ll Arr[maxN];
SegmentData S[maxN<<2];

void Build(int now,int l,int r);
void Modify(int now,int l,int r,int ql,int qr);
ll Query(int now,int l,int r,int ql,int qr);

int main()
{
	//ios::sync_with_stdio(false);
	int cas=0;
	while (scanf("%d",&n)!=EOF)//cin>>n;
	{
		//cout<<n<<endl;
		if (cas!=0) printf("\n");
		printf("Case #%d:\n",++cas);
		for (int i=1;i<=n;i++) scanf("%lld\n",&Arr[i]);//cin>>Arr[i];
		Build(1,1,n);
		
		scanf("%d",&m);//cin>>m;
		while (m--)
		{
			int opt,l,r;scanf("%d%d%d",&opt,&l,&r);//cin>>opt>>l>>r;
			if (l>r) swap(l,r);
			if (opt==1) printf("%lld\n",Query(1,1,n,l,r));//cout<<Query(1,1,n,l,r)<<endl;
			if (opt==0) Modify(1,1,n,l,r);
		}
	}
	return 0;
}

void Build(int now,int l,int r)
{
	if (l==r)
	{
		S[now].mx=S[now].sum=Arr[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now].sum=S[lson].sum+S[rson].sum;
	S[now].mx=max(S[lson].mx,S[rson].mx);
	return;
}

void Modify(int now,int l,int r,int ql,int qr)
{
	if (S[now].mx<=1) return;
	if (l==r)
	{
		S[now].mx=sqrt(S[now].mx);S[now].sum=S[now].mx;
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr);
	else
	{
		Modify(lson,l,mid,ql,mid);
		Modify(rson,mid+1,r,mid+1,qr);
	}
	S[now].sum=S[lson].sum+S[rson].sum;
	S[now].mx=max(S[lson].mx,S[rson].mx);
	return;
}

ll Query(int now,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
