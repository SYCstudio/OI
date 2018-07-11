#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

bool notprime[maxN];
int pricnt,Prime[maxN],Mu[maxN],H[maxN],Low[maxN];

void Init();

int main()
{
	Init();
}

void Init()
{
	notprime[1]=0;Mu[1]=1;H[1]=1;Low[1]=1;
	for (int i=2;i<maxN;i++)
	{
		if (notprime[i]==0) Prime[++pricnt]=i,Mu[i]=1,H[i]=H[i]+1,Low[i]=i;
		for (int j=1;(j<=pricnt)&&(1ll*i*Prime[j]<maxN);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0)
			{
				Mu[i*Prime[j]]=0;
				H[i*Prime[j]]=H[i/Low[i]]*H[Low[i]*Prime[j]];
				Low[i*Prime[j]]=Low[i]*Prime[j];
			}
			Mu[i*Prime[j]]=-Mu[i];
			H[i*Prime[j]]=H[i]*H[Prime[j]];
			Low[i*Prime[j]]=Prime[j];
		}
	}
	return;
}
