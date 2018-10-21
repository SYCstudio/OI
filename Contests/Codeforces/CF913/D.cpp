#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long

const int maxN=200110;
const int inf=2147483647;

class Problem
{
public:
	ll lim,tim;
};

bool operator < (Problem A,Problem B)
{
	return A.tim<B.tim;
}

ll n,T;
Problem P[maxN];

int Check(int mid);

int main()
{
	scanf("%lld%lld",&n,&T);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&P[i].lim,&P[i].tim);
	sort(&P[1],&P[n+1]);
	int l=0,r=n;
	int Ans=0;
	do
	{
		int mid=(l+r)/2;
		if (Check(mid)>=mid)
		{
			Ans=mid;l=mid+1;
		}
		else r=mid-1;
	}
	while (l<=r);
	printf("%d\n%d\n",Ans,Ans);
	ll procnt=0,timcnt=0;
	for (int i=1;(i<=n)&&(procnt<Ans);i++)
	{
		if (timcnt+P[i].tim>T) break;
		if (P[i].lim<Ans) continue;
		procnt++;timcnt+=P[i].tim;
		printf("%d ",i);
	}
	printf("\n");
	return 0;
}

int Check(int mid)
{
	ll procnt=0,timcnt=0;
	for (int i=1;i<=n;i++)
	{
		if (timcnt+P[i].tim>T) break;
		if (P[i].lim<mid) continue;
		procnt++;timcnt+=P[i].tim;
	}
	return procnt;
}
