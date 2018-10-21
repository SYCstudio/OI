#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxNum=1000010;
const int inf=2147483647;

int Mu[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetMu();
ll Check(ll n);

int main()
{
	GetMu();
	int T;scanf("%d",&T);
	while (T--)
	{
		int n;scanf("%d",&n);
		ll l=1,r=1e10,ans;
		do
		{
			ll mid=(l+r)/2;
			if (Check(mid)>=n)
				ans=mid,r=mid-1;
			else l=mid+1;
		}
		while (l<=r);
		printf("%lld\n",ans);
	}
	return 0;
}

void GetMu()
{
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Mu[i]=-1,Prime[++pricnt]=i;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
			Mu[i*Prime[j]]=-Mu[i];
		}
	}
	return;
}

ll Check(ll n)
{
	ll ret=0;
	for (ll i=1;i*i<=n;i++) ret=ret+Mu[i]*n/i/i;
	return ret;
}
