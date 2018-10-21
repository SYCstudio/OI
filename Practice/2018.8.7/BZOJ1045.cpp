#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000100;
const int inf=2147483647;

int n;
ll A[maxN];

int main()
{
	scanf("%d",&n);
	ll sum=0;
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]),sum+=A[i];
	sum/=n;
	for (int i=1;i<=n;i++) A[i]=A[i]-sum;
	for (int i=2;i<=n;i++) A[i]=A[i]+A[i-1];

	sort(&A[1],&A[n+1]);

	ll ret=A[(n+1)/2];

	ll Ans=0;
	for (int i=1;i<=n;i++) Ans=Ans+abs(ret-A[i]);

	printf("%lld\n",Ans);

	return 0;
}
