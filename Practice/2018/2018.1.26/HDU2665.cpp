#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100110;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs;
	int sum;
};

int n,m;
int nodecnt=0;
SegmentData S[maxN*20];
int root[maxN];
int Arr[maxN],Brr[maxN];

void Build(int &now,int l,int r);
void Update(int &now,int l,int r,int num);
int Query(int now1,int now2,int l,int r,int kth);

int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		nodecnt=0;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d",&Arr[i]),Brr[i]=Arr[i];
		sort(&Brr[1],&Brr[n+1]);
		for (int i=1;i<=n;i++) Arr[i]=lower_bound(&Brr[1],&Brr[n+1],Arr[i])-Brr;
		//for (int i=1;i<=n;i++) cout<<Arr[i]<<" ";cout<<endl;
		Build(root[0],1,n);
		for (int i=1;i<=n;i++) root[i]=root[i-1],Update(root[i],1,n,Arr[i]);
		//for (int i=0;i<=n;i++) cout<<root[i]<<" "<<S[root[i]].sum<<endl;
		while (m--)
		{
			int l,r,kth;scanf("%d%d%d",&l,&r,&kth);
			//cout<<"pos:"<<Query(root[l-1],root[r],1,n,kth)<<endl;
			printf("%d\n",Brr[Query(root[l-1],root[r],1,n,kth)]);
		}
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)/2;
	Build(S[now].ls,l,mid);
	Build(S[now].rs,mid+1,r);
	return;
}

void Update(int &now,int l,int r,int num)
{
	S[++nodecnt]=S[now];
	S[now=nodecnt].sum++;
	//cout<<now<<" ["<<l<<","<<r<<"] "<<num<<" "<<S[now].sum<<endl;
	if (l==r) return;
	int mid=(l+r)/2;
	if (num<=mid) Update(S[now].ls,l,mid,num);
	else Update(S[now].rs,mid+1,r,num);
	return;
}

int Query(int now1,int now2,int l,int r,int kth)
{
	if (l==r) return l;
	int lsize=S[S[now2].ls].sum-S[S[now1].ls].sum;
	//cout<<"["<<l<<","<<r<<"] "<<S[now1].sum<<" "<<S[now2].sum<<" "<<lsize<<endl;
	int mid=(l+r)/2;
	if (lsize>=kth) return Query(S[now1].ls,S[now2].ls,l,mid,kth);
	else return Query(S[now1].rs,S[now2].rs,mid+1,r,kth-lsize);
}
