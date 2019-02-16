#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=15;
const int maxK=120;
const int inf=2147483647;

int n,K;
int P[maxN];
int Relay[maxN];
ld F[maxK][(1<<maxN)+10];

int main()
{
	scanf("%d%d",&K,&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&P[i]);
		int k;scanf("%d",&k);
		while (k!=0)
		{
			Relay[i]|=1<<(k-1);
			scanf("%d",&k);
		}
	}
	for (int i=K;i>=1;i--)
		for (int j=0;j<(1<<(n+1));j++)
		{
			for (int k=0;k<n;k++)
				if ((j&Relay[k])==Relay[k])
					F[i][j]+=max(F[i+1][j],F[i+1][j|(1<<k)]+P[k]);
				else F[i][j]+=F[i+1][j];
			F[i][j]=F[i][j]/(ld)n;
		}
	printf("%.6LF\n",F[1][0]);
	return 0;
}
