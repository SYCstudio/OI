#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxNum=10000010;
const int inf=2147483647;

ll F[maxNum];
int Mu[maxNum];
int pricnt=0,Prime[maxNum/100];
bool notprime[maxNum];

void Init();

int main()
{
	Init();
	int T;scanf("%d",&T);
	while (T--)
	{
		int n,m;scanf("%d%d",&n,&m);if (n>m) swap(n,m);
		ll ans=0;
		for (int i=1,last;i<=n;i=last+1)
		{
			last=min(n/(n/i),m/(m/i));
			ans=ans+(F[last]-F[i-1])*(ll)((n/i))*(ll)((m/i));
		}
		printf("%lld\n",ans);
	}
	return 0;
}

void Init()
{
	Mu[1]=1;F[1]=0;notprime[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1,F[i]=1;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j]<maxNum);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0)
			{
				F[i*Prime[j]]=Mu[i];
				break;
			}
			Mu[i*Prime[j]]=-Mu[i];
			F[i*Prime[j]]=Mu[i]-F[i];
		}
	}
	for (int i=1;i<maxNum;i++) F[i]+=F[i-1];
	return;
}
