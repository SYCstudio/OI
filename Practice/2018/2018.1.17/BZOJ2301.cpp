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

int Mu[maxNum];
int Musum[maxNum];
int pricnt=0,Prime[maxNum];
bool notprime[maxNum];

void GetMu();
int Calc(int n,int m);

int main()
{
	GetMu();
	int T;scanf("%d",&T);
	while (T--)
	{
		int a,b,c,d,K;scanf("%d%d%d%d%d",&a,&b,&c,&d,&K);
		printf("%d\n",Calc(b/K,d/K)-Calc((a-1)/K,d/K)-Calc(b/K,(c-1)/K)+Calc((a-1)/K,(c-1)/K));
	}
	return 0;
}

void GetMu()
{
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<maxNum;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=-1;
		for (int j=1;(j<=pricnt)&&((ll)i*(ll)Prime[j])<maxNum;j++)
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
	int ret=0;if (n>m) swap(n,m);
	for (int i=1,last;i<=n;i=last+1)
	{
		last=min(n/(n/i),m/(m/i));
		ret=ret+(Musum[last]-Musum[i-1])*(n/i)*(m/i);
	}
	return ret;
}
