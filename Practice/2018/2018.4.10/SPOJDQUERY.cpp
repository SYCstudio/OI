#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)
#define lson S[now].ls
#define rson S[now].rs

const int maxN=30010;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int ls,rs;
};

int n,m;
int numcnt,Num[maxN],Arr[maxN];
int nodecnt,root[maxN];
int Lastpos[maxN];
SegmentData S[maxN*100];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&Arr[i]);
		Num[++numcnt]=Arr[i];
	}
	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	Build(root[0],1,n);
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		int k=find(Arr[i]);
		if (Lastpos[k]!=0) Modify(root[i],1,n,Lastpos[k],-1);
		Modify(root[i],1,n,i,1);
		Lastpos[k]=i;
	}

	int Q;scanf("%d",&Q);
	while (Q--)
	{
		int L,R;scanf("%d%d",&L,&R);
		printf("%d\n",Query(root[R],1,n,L,R));
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
}

int Query(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
