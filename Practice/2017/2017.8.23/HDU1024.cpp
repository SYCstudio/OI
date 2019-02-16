#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=1000011;
const int inf=2147483647;

int n,m;
int Arr[maxN];
ll F[maxN];
ll Pre_max[maxN];

int main()
{
	while (cin>>m>>n)
	{
		for (int i=1;i<=n;i++)
			scanf("%d",&Arr[i]);
		memset(F,0,sizeof(F));
		memset(Pre_max,0,sizeof(Pre_max));
		ll nowmax;
		for (int i=1;i<=m;i++)
		{
			nowmax=-inf;
			for (int j=i;j<=n;j++)
			{
				F[j]=max(F[j-1]+Arr[j],Pre_max[j-1]+Arr[j]);//新开一组，或加入到之前的最大的一组中去
				Pre_max[j-1]=nowmax;//更新前面最大的
				nowmax=max(nowmax,F[j]);
			}
		}
		printf("%lld\n",nowmax);
	}
	return 0;
}
