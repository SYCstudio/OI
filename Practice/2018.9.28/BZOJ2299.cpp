#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

bool check(ll x,ll y,ll d);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		ll a,b,x,y;scanf("%lld%lld%lld%lld",&a,&b,&x,&y);
		ll d=__gcd(a,b)*2;
		if (check(x,y,d)||check(x+b,y+a,d)||check(x+a,y+b,d)||check(x+a+b,y+a+b,d)) printf("Y\n");
		else printf("N\n");
	}
}

bool check(ll x,ll y,ll d){
	return (x%d==0)&&(y%d==0);
}
