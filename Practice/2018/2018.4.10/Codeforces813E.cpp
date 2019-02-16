#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson S[now].ls
#define rson S[now].rs

const int maxN=110000;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int ls,rs;
};

int n,K;
int nodecnt,root[maxN];
int Arr[maxN];
int Num[maxN];
queue<int> Queue[maxN];
SegmentData S[maxN*100];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int r1,int r2,int l,int r,int ql,int qr);

int main()
{
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);
	Build(root[0],0,n);
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		int id=0;
		if (Num[Arr[i]]==K){
			id=Queue[Arr[i]].front();Queue[Arr[i]].pop();
		}
		else Num[Arr[i]]++;
		Queue[Arr[i]].push(i);
		Modify(root[i],0,n,id,1);
	}
	int Q;scanf("%d",&Q);
	int lastans=0;
	while (Q--)
	{
		int l,r;scanf("%d%d",&l,&r);
		l=(l+lastans)%n+1;
		r=(r+lastans)%n+1;
		if (l>r) swap(l,r);
		printf("%d\n",lastans=Query(root[l-1],root[r],0,n,0,l-1));
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	if (l==r){
		S[now].sum+=key;return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	S[now].sum=S[lson].sum+S[rson].sum;
	return;
}

int Query(int r1,int r2,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[r2].sum-S[r1].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[r1].ls,S[r2].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(S[r1].rs,S[r2].rs,mid+1,r,ql,qr);
	else return Query(S[r1].ls,S[r2].ls,l,mid,ql,mid)+Query(S[r1].rs,S[r2].rs,mid+1,r,mid+1,qr);
}
