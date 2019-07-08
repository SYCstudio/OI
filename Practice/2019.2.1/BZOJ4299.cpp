#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=101000;

class SegmentData
{
public:
	int ls,rs,sum;
};

int n,m,nodecnt,rt[maxN];
SegmentData S[maxN*32];

void Insert(int &x,int l,int r,int p);
int Query(int xl,int xr,int l,int r,int ql,int qr);

int main()
{
	scanf("%d",&n);
	for (int i=1,x; i<=n; i++) scanf("%d",&x),Insert(rt[i]=rt[i-1],1,1000000000,x);
	scanf("%d",&m);
	while (m--) {
		int Ans=0,l,r;
		scanf("%d%d",&l,&r);
		while (1) {
			int q=Query(rt[l-1],rt[r],1,1000000000,1,Ans+1);
			if (Ans==q) break;
			Ans=q;
		}
		printf("%d\n",Ans+1);
	}
	return 0;
}
void Insert(int &x,int l,int r,int p)
{
	S[++nodecnt]=S[x];
	x=nodecnt;
	S[x].sum+=p;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Insert(S[x].ls,l,mid,p);
	else Insert(S[x].rs,mid+1,r,p);
	return;
}
int Query(int xl,int xr,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return S[xr].sum-S[xl].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) Query(S[xl].ls,S[xr].ls,l,mid,ql,qr);
	else if (ql>=mid+1) Query(S[xl].rs,S[xr].rs,mid+1,r,ql,qr);
	else return Query(S[xl].ls,S[xr].ls,l,mid,ql,mid)+Query(S[xl].rs,S[xr].rs,mid+1,r,mid+1,qr);
}
/*
5
1 2 4 9 10
5
1 1
1 2
1 3
1 4
1 5
//*/
