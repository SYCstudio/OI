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

const int maxN=100010;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int ls,rs;
	void init(){
		sum=ls=rs=0;return;
	}
};

int n,m;
int nodecnt,root[maxN],Arr[maxN];
int numcnt,Num[maxN];
SegmentData S[maxN*100];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);

int main()
{
	int cas=0;
	while (scanf("%d",&n)!=EOF)
	{
		nodecnt=numcnt=0;mem(root,0);
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
			Modify(root[i],1,numcnt,find(Arr[i]),1);
		}
		int Q;scanf("%d",&Q);
		printf("Case %d:\n",++cas);
		while (Q--)
		{
			int ql,qr;scanf("%d%d",&ql,&qr);
			int kth=(qr-ql+2)/2;
			int r1=root[ql-1],r2=root[qr];
			int L=1,R=numcnt;
			while (L!=R)
			{
				int lsum=S[S[r2].ls].sum-S[S[r1].ls].sum;
				int mid=(L+R)>>1;
				if (lsum>=kth) r1=S[r1].ls,r2=S[r2].ls,R=mid;
				else r1=S[r1].rs,r2=S[r2].rs,L=mid+1,kth-=lsum;
			}
			printf("%d\n",Num[L]);
		}
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;S[now].init();
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
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
	S[now].sum=S[lson].sum+S[rson].sum;
	return;
}
