#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

map<ll,int> h;
ll p,a,b,limit,now,t,i;
bool getans=0;

int main(){
	ll p,a,b;
	while(scanf("%lld%lld%lld",&p,&a,&b)!=EOF){
		if (a%p==0){
			printf("no solution\n");
			continue;
		}
		h.clear();
		limit=ceil(sqrt(p));
		now=b%p;t=1;h[now]=0;
		for (i=1;i<=limit;++i){
			now=now*a%p;t=t*a%p;
			h[now]=i;
		}
		getans=0;
		now=1;
		for (i=1;i<=limit;++i){
			now=now*t%p;
			if (h[now]){
				printf("%lld\n",((i*limit-h[now])%p+p)%p);getans=true;break;
			}
		}
		if (!getans) printf("no solution\n");
	}

	return 0;
}
