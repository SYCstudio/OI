#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1;
const int inf=2147483647;

ll n,m;

int main()
{
	cin>>n>>m;
	ll ret=1;
	while ((ret<=m)&&(n>=1))
		ret=ret*2ll,n--;
	if ((n!=0)||(ret>=m)) printf("%lld\n",m);
	else printf("%lld\n",m%ret);
	return 0;
}
