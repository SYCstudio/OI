#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=10000010;
const int Mod=998244353;
const int inf=2147483647;

int Mu[maxNum];
int Musum[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetMu();
int Calc(int n,int m);

int main()
{
	int n,m;
	GetMu();
	scanf("%d%d",&n,&m);if (m<n) swap(n,m);
	int ans=0;
	for (int i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ans=(ans+(ll)(i+last)*(ll)(last-i+1)/2%Mod*Calc(n/i,m/i)%Mod)%Mod;
	}
	printf("%d\n",(ans+Mod)%Mod);
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
	for (int i=1;i<maxNum;i++) Musum[i]=Musum[i-1]+Mu[i];
	return;
}

int Calc(int n,int m)
{
	int ret=0;
	for (int i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ret=(ret+(Musum[last]-Musum[i-1]+Mod)%Mod*(ll)(n/i)%Mod*(ll)(m/i)%Mod+Mod)%Mod;
	}
	return (ret+Mod)%Mod;
}
