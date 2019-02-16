#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=50010;
const int inf=2147483647;

ll Mu[maxNum],Low[maxNum];
ll Musum[maxNum],F[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void Init();

int main()
{
	Init();
	int T;scanf("%d",&T);
	while (T--)
	{
		ll n,m;scanf("%lld%lld",&n,&m);if (n>m) swap(n,m);
		ll ans=0;
		for (ll i=1,last;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ans=ans+(Musum[last]-Musum[i-1])*F[n/i]*F[m/i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}

void Init()
{
	notprime[1]=1;Mu[1]=1;Low[1]=1;F[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1,Low[i]=1,F[i]=2;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0)
			{
				Low[i*Prime[j]]=Low[i]+1;
				F[i*Prime[j]]=F[i]/(Low[i]+1)*(Low[i]+2);
				break;
			}
			Mu[i*Prime[j]]=-Mu[i];
			F[i*Prime[j]]=F[i]*F[Prime[j]];
			Low[i*Prime[j]]=1;
		}
	}
	//for (int i=1;i<=20;i++) cout<<i<<":"<<F[i]<<"  ";cout<<endl;
	for (int i=1;i<maxNum;i++) Musum[i]=Musum[i-1]+Mu[i],F[i]+=F[i-1];
	return;
}
