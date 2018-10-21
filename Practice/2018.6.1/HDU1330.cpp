#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int inf=2147483647;

int C;
int P[maxN],A[maxN];
int F[maxN];

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		mem(F,0);
		scanf("%d",&C);
		for (int i=1;i<=C;i++) scanf("%d%d",&A[i],&P[i]);
		for (int i=1;i<=C;i++) A[i]+=A[i-1];
		F[0]=0;
		for (int i=1;i<=C;i++)
		{
			F[i]=inf;
			for (int j=0;j<i;j++) F[i]=min(F[i],F[j]+P[i]*(A[i]-A[j]+10));
		}
		printf("%d\n",F[C]);
	}
	return 0;
}
