#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNum=10000010;
const int maxP=1000010;
const int inf=2147483647;

int n,m;
bool notprime[maxNum];
int pricnt=0,Prime[maxP];

int main()
{
	scanf("%d%d",&n,&m);
	notprime[1]=1;
	for (int i=2;i<=n;i++)
    {
		if (notprime[i]==0)
			Prime[++pricnt]=i;
		for (int j=1;(j<=pricnt)&&((ll)i*Prime[j]<=n);j++)
		{
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0) break;
		}
    }
	while (m--)
    {
		int x;scanf("%d",&x);
		if (notprime[x]==1) printf("No\n");
		else printf("Yes\n");
    }
	return 0;
}
