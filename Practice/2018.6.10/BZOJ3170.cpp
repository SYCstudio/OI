#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
ll X[maxN],Y[maxN];
ld A[maxN],B[maxN],Sx1[maxN],Sx2[maxN],Sy1[maxN],Sy2[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&X[i],&Y[i]);
		A[i]=1.0*(X[i]+Y[i])/2.0;B[i]=1.0*(X[i]-Y[i])/2.0;
	}
	sort(&A[1],&A[n+1]);sort(&B[1],&B[n+1]);
	for (int i=1;i<=n;i++) Sx1[i]=Sx1[i-1]+A[i],Sy1[i]=Sy1[i-1]+B[i];
	for (int i=n;i>=1;i--) Sx2[i]=Sx2[i+1]+A[i],Sy2[i]=Sy2[i+1]+B[i];
	ll Ans=1e18;
	for (int i=1;i<=n;i++)
	{
		ll px=lower_bound(&A[1],&A[n+1],1.0*(X[i]+Y[i])/2.0)-A;
		ll py=lower_bound(&B[1],&B[n+1],1.0*(X[i]-Y[i])/2.0)-B;
		Ans=min(Ans,(ll)((1.0*(X[i]+Y[i])/2.0*px-Sx1[px])+(Sx2[px+1]-1.0*(X[i]+Y[i])/2.0*(n-px))
						 +(1.0*(X[i]-Y[i])/2.0*py-Sy1[py])+(Sy2[py+1]-1.0*(X[i]-Y[i])/2.0*(n-py))));
	}
	printf("%lld\n",Ans);
	return 0;
}
