#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=101000;
const ld eps=1e-6;
const int inf=2147483647;
const ll INF=1e18;

int n,K,ansL,ansR;
ll Val[maxN];
ld Sum[maxN];

bool Check(RG ld k);
ll gcd(RG ll a,RG ll b);

int main()
{
	scanf("%d%d",&n,&K);
	RG ld L=INF,R=-INF;
	for (RG int i=1;i<=n;i++) scanf("%lld",&Val[i]),L=min(L,(ld)Val[i]),R=max(R,(ld)Val[i]);
	L-=eps;R+=eps;
	int cnt=0;
	do
	{
		if (++cnt>=40) break;
		RG ld mid=(L+R)/2.0;
		if (Check(mid)) L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);
	RG ll sum=0;
	for (RG int i=ansL;i<=ansR;i++) sum+=Val[i];
	RG ll g=gcd(abs(sum),ansR-ansL+1);
	printf("%lld/%lld\n",sum/g,(ansR-ansL+1)/g);
	return 0;
}

bool Check(RG ld k)
{
	for (RG int i=1;i<=n;i++) Sum[i]=Sum[i-1]+Val[i]-k;
	for (RG int i=K,pos=0;i<=n;i++)
	{
		if (Sum[i]>=Sum[pos])
		{
			ansL=pos+1;ansR=i;
			return 1;
		}
		if (Sum[i-K+1]<Sum[pos]) pos=i-K+1;
	}
	return 0;
}

ll gcd(RG ll a,RG ll b)
{
	RG ll t;
	while (b) t=a,a=b,b=t%b;
	return a;
}
