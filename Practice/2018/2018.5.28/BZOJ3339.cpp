#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxNum=200000;
const int inf=2147483647;

class SegmentData
{
public:
	int mn,mx;
	int ls,rs;
};

int n,m;
int Arr[maxN];
int nodecnt,root[maxN];
SegmentData S[maxN*100];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int ql,int qr);
int Query(int now,int l,int r,int limit);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);
	Build(root[0],0,maxNum);
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		Modify(root[i],0,maxNum,Arr[i],i);
	}
	for (int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		printf("%d\n",Query(root[r],0,maxNum,l));
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	S[now].mn=S[now].mx=0;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	if (l==r){
		S[now].mn=S[now].mx=key;return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
	S[now].mn=min(S[S[now].ls].mn,S[S[now].rs].mn);
	S[now].mx=max(S[S[now].ls].mx,S[S[now].rs].mx);
	return;
}

int Query(int now,int l,int r,int limit)
{
	if (l==r) return l;
	int mid=(l+r)>>1;
	if (S[S[now].ls].mn<limit) return Query(S[now].ls,l,mid,limit);
	else return Query(S[now].rs,mid+1,r,limit);
}
