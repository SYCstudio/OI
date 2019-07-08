#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=505000;

int n;
int lkey[maxN],rkey[maxN],ktype[maxN],lst[maxN],lft[maxN],rht[maxN],St[maxN];
vector<int> Hk[maxN];
int Mx[maxN<<2];

void Build(int x,int l,int r);
int GetLeft(int l,int r);
int Query(int x,int l,int r,int ql,int qr,int limit);

int main()
{
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d",&n);
	for (int i=1; i<n; i++) scanf("%d",&ktype[i]);
	for (int i=1; i<=n; i++) {
		int b;
		scanf("%d",&b);
		for (int j=1,x; j<=b; j++) scanf("%d",&x),Hk[i].push_back(x);
	}
	mem(lst,0);
	for (int i=1; i<n; i++) {
		for (int j=0,sz=Hk[i].size(); j<sz; j++) lst[Hk[i][j]]=i;
		lkey[i]=lst[ktype[i]];
	}
	for (int i=1; i<=n; i++) lst[i]=n+1;
	for (int i=n; i>1; i--) {
		for (int j=0,sz=Hk[i].size(); j<sz; j++) lst[Hk[i][j]]=i;
		rkey[i-1]=lst[ktype[i-1]];
	}
	lkey[0]=0;
	rkey[0]=n+1;
	lkey[0]=0;
	rkey[n]=n+1;
	//for (int i=1;i<n;i++) cout<<lkey[i]<<" "<<rkey[i]<<endl;
	Build(1,1,n-1);
	int top=0;
	for (int i=n; i>=1; i--) {
		St[++top]=i;
		rht[i]=i;
		lft[i]=GetLeft(i,rht[i]);
		while (top&&lkey[St[top]]>=lft[i]&&lkey[St[top]]<=rht[i]) {
			rht[i]=rht[St[top--]+1];
			lft[i]=GetLeft(lft[i],rht[i]);
		}
	}
	//for (int i=1;i<=n;i++) cout<<"["<<lft[i]<<","<<rht[i]<<"]"<<endl;
	int Q;
	scanf("%d",&Q);
	while (Q--) {
		int s,t;
		scanf("%d%d",&s,&t);
		(lft[s]<=t&&rht[s]>=t)?puts("YES"):puts("NO");
	}
	return 0;
}
void Build(int x,int l,int r)
{
	if (l==r) {
		Mx[x]=rkey[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	Mx[x]=max(Mx[ls],Mx[rs]);
	return;
}
int Query(int x,int l,int r,int ql,int qr,int limit)
{
	//cout<<"Query:"<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<limit<<endl;
	if (Mx[x]<=limit) return 0;
	if (l==r) return l;
	int mid=(l+r)>>1;
	if (l==ql&&r==qr) {
		if (Mx[rs]>limit) return Query(rs,mid+1,r,mid+1,qr,limit);
		else return Query(ls,l,mid,ql,mid,limit);
	}
	if (qr<=mid) return Query(ls,l,mid,ql,qr,limit);
	else if (ql>=mid+1) return Query(rs,mid+1,r,mid+1,qr,limit);
	else {
		int ret=Query(rs,mid+1,r,mid+1,qr,limit);
		if (ret) return ret;
		else return Query(ls,l,mid,ql,mid,limit);
	}
}
int GetLeft(int l,int r)
{
	if (l==1) return l;
	int ret=Query(1,1,n-1,1,l-1,r);
	//cout<<"Getleft:"<<l<<" "<<r<<":"<<(ret?ret+1:1)<<endl;
	return ret?ret+1:1;
}