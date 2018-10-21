#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson S[now].ls
#define rson S[now].rs
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=510010;
const int inf=2147483647;

class SegmentData
{
public:
	int sum;
	int ls,rs;
};

int n,m;
int nodecnt,root[maxN];
int Arr[maxN];
int numcnt,Num[maxN];
SegmentData S[maxN*50];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos,int key);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&Arr[i]);
		Num[++numcnt]=Arr[i];
	}
	sort(&Num[1],&Num[numcnt+1]);
	numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	Build(root[0],1,numcnt);
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		Modify(root[i],1,numcnt,find(Arr[i]),1);
	}
	while (m--)
	{
		int ql,qr;scanf("%d%d",&ql,&qr);
		int siz=(qr-ql+1)/2;
		//cout<<"siz:"<<siz<<endl;
		int r1=root[ql-1],r2=root[qr];
		int L=1,R=numcnt;
		bool getans=1;
		while (L!=R)
		{
			int lsize=S[S[r2].ls].sum-S[S[r1].ls].sum;
			int rsize=S[S[r2].rs].sum-S[S[r1].rs].sum;
			int mid=(L+R)>>1;
			//cout<<"["<<L<<","<<R<<"]"<<" "<<lsize<<" "<<rsize<<endl;
			if (lsize>siz) r1=S[r1].ls,r2=S[r2].ls,R=mid;
			else if (rsize>siz) r1=S[r1].rs,r2=S[r2].rs,L=mid+1;
			else
			{
				getans=0;
				break;
			}
		}
		if (getans==0) printf("0\n");
		else printf("%d\n",Num[L]);
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
