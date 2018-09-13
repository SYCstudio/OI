#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define RG register
#define IL inline
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1;
const int inf=2147483647;

int main()
{
	RG ll T;scanf("%lld",&T);
	while (T--)
	{
		RG ll X;scanf("%lld",&X);
		RG bool flag=0;
		for (RG ll n=1;n*n<=5e9;n++)
		{
			if (n*n<=X) continue;
			ll res=sqrt(n*n-X);
			ll m=n/res;if (m==0) continue;
			res=n/m;
			if (n*n-res*res==X)
			{
				flag=1;
				printf("%lld %lld\n",n,m);
				break;
			}
		}
		if (flag==0) printf("-1\n");
	}
	return 0;
}
