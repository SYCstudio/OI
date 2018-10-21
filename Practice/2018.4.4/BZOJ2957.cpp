#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=100100;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt;
	ld k;
};

int n,m;
SegmentData S[maxN<<2];

void Modify(int now,int l,int r,int pos,ld key);
int Query(int now,int l,int r,ld K);

int main()
{
	scanf("%d%d",&n,&m);
	while (m--)
	{
		int x,y;scanf("%d%d",&x,&y);//cin>>x>>y;
		Modify(1,1,n,x,y);
		//cout<<S[1].cnt<<endl;
		printf("%d\n",S[1].cnt);
	}
	return 0;
}

void Modify(int now,int l,int r,int pos,ld key)
{
	if (l==r)
	{
		S[now].k=key/(ld)pos;
		S[now].cnt=1;
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	S[now].k=max(S[lson].k,S[rson].k);
	S[now].cnt=S[lson].cnt+Query(rson,mid+1,r,S[lson].k);
	return;
}

int Query(int now,int l,int r,ld K)
{
	if (K>=S[now].k) return 0;
	if (l==r) return 1;
	int mid=(l+r)>>1;
	if (S[lson].k>=K) return Query(lson,l,mid,K)+S[now].cnt-S[lson].cnt;
	else return Query(rson,mid+1,r,K);
}
