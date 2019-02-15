#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

int main(){
	ll p,q;
	scanf("%lld%lld",&p,&q);
	if (p==q) printf("%lld\n",(p-1)*(q+1)/4);
	else printf("%lld\n",(p-1)*(q-1)/4);return 0;
}
