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

const int maxN=201000;
const int inf=2147483647;

int n,m;
int S[maxN<<2];
int UFS[maxN],Size[maxN];

void Modify(int now,int l,int r,int pos,int key);
int Kth(int now,int l,int r,int kth);
int Find(int x);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) UFS[i]=i,Size[i]=1;
	Modify(1,1,n,1,n);
	for (int i=1;i<=m;i++)
	{
		int opt;scanf("%d",&opt);
		if (opt==0)
		{
			int u,v;scanf("%d%d",&u,&v);
			u=Find(u);v=Find(v);
			if (u==v) continue;
			Modify(1,1,n,Size[u],-1);
			Modify(1,1,n,Size[v],-1);
			Size[u]+=Size[v];UFS[v]=u;
			Modify(1,1,n,Size[u],1);
		}
		if (opt==1)
		{
			int kth;scanf("%d",&kth);
			printf("%d\n",Kth(1,1,n,kth));
		}
	}
	return 0;
}

void Modify(int now,int l,int r,int pos,int key)
{
	S[now]+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	return;
}

int Kth(int now,int l,int r,int kth)
{
	if (l==r) return l;
	int mid=(l+r)>>1;
	if (kth<=S[rson]) return Kth(rson,mid+1,r,kth);
	else return Kth(lson,l,mid,kth-S[rson]);
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
