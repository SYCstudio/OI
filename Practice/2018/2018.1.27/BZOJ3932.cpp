#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210010;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs;
	ll cnt,sum;
	int tim;//时间戳
};

class Edge
{
public:
	int s,e,p;
};

int n,m;
int nodecnt=0,root[maxN];
int nowtim;
vector<int> E[maxN];
Edge Input[maxN];
SegmentData S[maxN*30];
int Num[maxN];

void Build(int &now,int l,int r);
void Update(int n1,int &n2,int l,int r,int id,ll key);
ll Query(int now,int l,int r,int kth);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&Input[i].s,&Input[i].e,&Input[i].p);
		Num[i]=Input[i].p;
	}
	sort(&Num[1],&Num[n+1]);
	for (int i=1;i<=n;i++)
	{
		Input[i].p=lower_bound(&Num[1],&Num[n+1],Input[i].p)-Num;
		E[Input[i].s].push_back(Input[i].p);E[Input[i].e+1].push_back(-Input[i].p);
	}
	Build(root[0],1,m+1);
	for (int i=1;i<=m+1;i++)
	{
		root[i]=root[i-1];nowtim=i;
		for (int j=0;j<E[i].size();j++)
			if (E[i][j]>0) Update(root[i],root[i],1,m+1,E[i][j],Num[E[i][j]]);
			else Update(root[i],root[i],1,m+1,-E[i][j],-Num[-E[i][j]]);
	}
	ll ans=1;
	for (int i=1;i<=m;i++)
	{
		int x,a,b,c;scanf("%d%d%d%d",&x,&a,&b,&c);
		int kth=((ll)a*(ll)ans%c+b%c)%c+1;
		if (S[root[x]].cnt<=kth) printf("%lld\n",ans=S[root[x]].sum);
		else printf("%lld\n",ans=Query(root[x],1,m+1,kth));
	}
	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Update(int n1,int &n2,int l,int r,int id,ll key)
{
	//cout<<id<<" "<<key<<endl;
	if (S[n1].tim!=nowtim)
	{
		S[++nodecnt]=S[n1];n2=nodecnt;
		S[n2].tim=nowtim;
	}
	if (key>0) S[n2].cnt++;else S[n2].cnt--;
	S[n2].sum=(ll)S[n2].sum+(ll)key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (id<=mid) Update(S[n1].ls,S[n2].ls,l,mid,id,key);
	else Update(S[n1].rs,S[n2].rs,mid+1,r,id,key);
	return;
}

ll Query(int now,int l,int r,int kth)
{
	if (l==r) return (ll)Num[l]*(ll)kth;
	int mid=(l+r)>>1;
	if (S[S[now].ls].cnt>=kth) return Query(S[now].ls,l,mid,kth);
	else return Query(S[now].rs,mid+1,r,kth-S[S[now].ls].cnt)+S[S[now].ls].sum;
}
