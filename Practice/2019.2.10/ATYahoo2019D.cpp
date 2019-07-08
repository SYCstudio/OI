#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int maxN=202000;
const ll INF=1e18;

int n;
ll Sum[maxN],F[maxN],G[maxN],Even[maxN],Cost[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		ll x;
		scanf("%lld",&x);
		Sum[i]=Sum[i-1]+x;
		Even[i]=Even[i-1]+(~x&1);
		Cost[i]=Cost[i-1]+(x<=2?2-x:(x&1));
	}
	//for (int i=1;i<=n;i++) cout<<Sum[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Even[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Cost[i]<<" ";cout<<endl;
	ll mn=0;
	for (int i=1; i<=n; i++) mn=min(mn,-Cost[i]+Sum[i]),F[i]=mn+Cost[i];
	mn=Cost[n];
	for (int i=n-1; i>=0; i--) mn=min(mn,Sum[n]+Cost[i]-Sum[i]),G[i]=mn-Cost[i];

	//for (int i=0;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=0;i<=n;i++) cout<<G[i]<<" ";cout<<endl;

	ll Ans=INF;
	mn=INF;
	for (int i=0; i<=n; i++) mn=min(mn,F[i]-Even[i]),Ans=min(Ans,mn+Even[i]+G[i]);
	printf("%lld\n",Ans);
	return 0;
}