#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=1010;

ll C[maxN],S[maxN];

int main(){
	ll n,m;scanf("%lld%lld",&n,&m);
	for (int i=3;i<maxN;i++) C[i]=1ll*i*(i-1)*(i-2)/6;
	for (int i=1;i<maxN;i++) S[i]=S[i-1]+C[i];
	ll Ans=((n+1)*(m+1))*((n+1)*(m+1)-1)*((n+1)*(m+1)-2)/6ll-(n+1)*n*(n-1)/6*(m+1)-(m+1)*m*(m-1)/6*(n+1);
	//cout<<Ans<<endl;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			Ans-=1ll*(__gcd(i,j)-1)*(n-i+1)*(m-j+1)*2;
	printf("%lld\n",Ans);return 0;
}
