#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=501;
const int maxW=100010;
const int inf=147483647;

int n,W;
int F[maxW];
int Weight[maxN];
int Cost[maxN];

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int w2;
		scanf("%d%d",&w2,&W);
		W=W-w2;
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d%d",&Cost[i],&Weight[i]);
		for (int i=0;i<=W;i++)
			F[i]=inf;
		F[0]=0;
		for (int i=1;i<=n;i++)
			for (int j=Weight[i];j<=W;j++)
				F[j]=min(F[j],F[j-Weight[i]]+Cost[i]);
		if (F[W]==inf)
			printf("This is impossible.\n");
		else
			printf("The minimum amount of money in the piggy-bank is %d.\n",F[W]);
	}
	return 0;
}
