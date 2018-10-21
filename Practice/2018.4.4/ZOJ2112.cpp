#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-(x)))
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=30010;
const int maxBit=15;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt;
	int ls,rs;
};

class Question
{
public:
	char opt;
	int a,b,c;
};

int n,m,nodecnt;
int Arr[maxN],root[maxN];
int numcnt=0,Num[maxN];
SegmentData S[maxN*400];
Question Q[maxN];
int rA[maxBit],rB[maxBit],cnt1,cnt2;

void Insert(int pos,int key,int opt);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int l,int r,int kth);

int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		nodecnt=0;mem(root,0);numcnt=0;mem(S,0);
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&Arr[i]);
			Num[++numcnt]=Arr[i];
		}
		for (int i=1;i<=m;i++)
		{
			Q[i].opt=getchar();
			while ((Q[i].opt!='Q')&&(Q[i].opt!='C')) Q[i].opt=getchar();
			if (Q[i].opt=='Q') scanf("%d%d%d",&Q[i].a,&Q[i].b,&Q[i].c);
			if (Q[i].opt=='C')
			{
				scanf("%d%d",&Q[i].a,&Q[i].b);
				Num[++numcnt]=Q[i].b;
			}
		}
	
		sort(&Num[1],&Num[numcnt+1]);
		numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

		for (int i=1;i<=n;i++) Insert(i,find(Arr[i]),1);
		for (int i=1;i<=m;i++)
			if (Q[i].opt=='Q')
			{
				cnt1=0;cnt2=0;
				for (int x=Q[i].a-1;x;x-=lowbit(x)) rA[++cnt1]=root[x];
				for (int x=Q[i].b;x;x-=lowbit(x)) rB[++cnt2]=root[x];
				printf("%d\n",Num[Query(1,numcnt,Q[i].c)]);
			}
			else
			{
				Insert(Q[i].a,find(Arr[Q[i].a]),-1);
				Arr[Q[i].a]=Q[i].b;
				Insert(Q[i].a,find(Arr[Q[i].a]),1);
			}
	}
	return 0;
}

void Insert(int pos,int key,int opt)
{
	while (pos<=n)
	{
		Modify(root[pos],1,numcnt,key,opt);
		pos+=lowbit(pos);
	}
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].cnt+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
	return;
}

int Query(int l,int r,int kth)
{
	if (l==r) return l;
	int lsize=0;
	for (int i=1;i<=cnt2;i++) lsize+=S[S[rB[i]].ls].cnt;
	for (int i=1;i<=cnt1;i++) lsize-=S[S[rA[i]].ls].cnt;
	int mid=(l+r)>>1;
	if (lsize>=kth)
	{
		for (int i=1;i<=cnt1;i++) rA[i]=S[rA[i]].ls;
		for (int i=1;i<=cnt2;i++) rB[i]=S[rB[i]].ls;
		return Query(l,mid,kth);
	}
	else
	{
		for (int i=1;i<=cnt1;i++) rA[i]=S[rA[i]].rs;
		for (int i=1;i<=cnt2;i++) rB[i]=S[rB[i]].rs;
		return Query(mid+1,r,kth-lsize);
	}
}
