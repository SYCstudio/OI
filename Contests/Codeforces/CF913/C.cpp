#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=35;
const int inf=2147483647;

ll n,L;
ll Cost[maxN],Sum[maxN];

int main()
{
	for (int i=0;i<maxN;i++) Cost[i]=6e18;
	cin>>n>>L;
	ll pos;for (pos=0;(1ll<<pos)<=L;pos++) ;//cout<<pos<<endl;
	for (int i=0;i<n;i++) cin>>Cost[i];
	for (int i=n-2;i>=0;i--) Cost[i]=min(Cost[i],Cost[i+1]);
	for (int i=1;i<=pos+1;i++) Cost[i]=min(Cost[i],Cost[i-1]*2);
	//for (int i=0;i<n;i++) cout<<Cost[i]<<" ";cout<<endl;
	Sum[0]=Cost[0];for (int i=1;i<=pos+1;i++) Sum[i]=Sum[i-1]+Cost[i];
	//for (int i=0;i<n;i++) cout<<Sum[i]<<" ";cout<<endl;
	ll Ans=Cost[pos];
	ll ret=0;
	for (int i=pos;i>=0;i--)
	{
		Ans=min(Ans,ret+Cost[i+1]);
		ret=ret+((L&(1<<i))!=0)*Cost[i];
		//cout<<i<<" "<<ret<<endl;
	}
	Ans=min(Ans,ret);
	printf("%lld\n",Ans);
	return 0;
}
