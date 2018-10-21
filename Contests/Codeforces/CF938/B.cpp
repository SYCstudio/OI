#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;
const ll INF=1e18;

int n;
ll Pos[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Pos[i]);Pos[n+1]=1000000;Pos[0]=1;
	ll Ans=INF;
	for (int i=0;i<=n;i++) Ans=min(Ans,max(Pos[i]-1ll,1000000ll-Pos[i+1]));
	printf("%lld\n",Ans);
	return 0;
}
