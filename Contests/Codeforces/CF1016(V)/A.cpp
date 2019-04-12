#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    int n,m;scanf("%d%d",&n,&m);
    ll sum=0,cnt=0;
    for (int i=1;i<=n;i++){
	ll x;scanf("%lld",&x);
	sum+=x;ll c=sum/m;
	printf("%lld ",c-cnt);cnt=c;
    }
    return 0;
}
