#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=100005;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs;
	int sum;
};

int n,nodecnt=0,length;
int root[maxN];
SegmentData S[maxN*25];
int Arr[maxN];
int Brr[maxN];

int Find(int key);
void Build(int &now,int l,int r);
void Update(int &now,int l,int r,int num);
int Query(int now1,int now2,int l,int r,int qr);

int main()
{
	int T;scanf("%d",&T);
	for (int ti=1;ti<=T;ti++)
	{
		mem(S,0);
		mem(root,0);
		printf("Case %d:\n",ti);
		RG int Q;
		nodecnt=0;
		scanf("%d%d",&n,&Q);
		for (RG int i=1;i<=n;i++) scanf("%d",&Arr[i]),Brr[i]=Arr[i];
		sort(&Brr[1],&Brr[n+1]);length=unique(&Brr[1],&Brr[n+1])-Brr-1;
		for (RG int i=1;i<=n;i++) Arr[i]=Find(Arr[i]);
		//for (int i=1;i<=n;i++) cout<<Arr[i]<<" ";cout<<endl;
		Build(root[0],1,length);
		for (RG int i=1;i<=n;i++) root[i]=root[i-1],Update(root[i],1,length,Arr[i]);
		while (Q--)
		{
			RG int l,r,h;scanf("%d%d%d",&l,&r,&h);l++;r++;
			RG int hh=Find(h);
			if (hh==0) {printf("0\n");continue;}
			printf("%d\n",Query(root[l-1],root[r],1,length,hh));
		}
	}
	return 0;
}

void Build(RG int &now,RG int l,RG int r)
{
	now=++nodecnt;
	if (l==r) return;
	RG int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);
	Build(S[now].rs,mid+1,r);
	return;
}

void Update(RG int &now,RG int l,RG int r,RG int num)
{
	//cout<<now<<endl;
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].sum++;
	if (l==r) return;
	RG int mid=(l+r)>>1;
	if (num<=mid) Update(S[now].ls,l,mid,num);
	else Update(S[now].rs,mid+1,r,num);
}

int Query(RG int now1,RG int now2,RG int l,RG int r,RG int qr)
{
	if (qr==r) return S[now2].sum-S[now1].sum;
	RG int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[now1].ls,S[now2].ls,l,mid,qr);
	else return Query(S[now1].ls,S[now2].ls,l,mid,mid)+Query(S[now1].rs,S[now2].rs,mid+1,r,qr);
}


int Find(int key)
{
	int l=1,r=length;
	int ret=0;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (Brr[mid]<=key)
			ret=mid,l=mid+1;
		else r=mid-1;
	}
	return ret;
}
