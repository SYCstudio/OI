#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

ll n,K;
ll Size[maxN];

int main()
{
	scanf("%lld%lld",&n,&K);
	for (int i=1;i<=K;i++) scanf("%lld",&Size[i]);
	ll Ansid=1,Anscnt=(ll)(n/Size[1])*Size[1];
	for (int i=2;i<=K;i++)
		if ((ll)(n/Size[i])*Size[i]>Anscnt){
			Ansid=i;Anscnt=(ll)(n/Size[i])*Size[i];
		}
	printf("%lld %lld",Ansid,n/Size[Ansid]);
	return 0;
}
