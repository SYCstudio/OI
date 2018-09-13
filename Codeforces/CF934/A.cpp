#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100;
const int inf=2147483647;

int n,m;
ll A[maxN],B[maxN];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]);
	for (int i=1;i<=m;i++) scanf("%lld",&B[i]);
	ll Ans=1e18+10;
	for (int i=1;i<=n;i++)
	{
		ll nowAns=-1e18+10;
		for (int x=1;x<=n;x++)
			if (x!=i)
				for (int y=1;y<=m;y++)
					nowAns=max(nowAns,A[x]*B[y]);
		Ans=min(Ans,nowAns);
	}
	printf("%lld\n",Ans);
	return 0;
}
