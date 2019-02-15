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

ll n,K;

int main(){
	scanf("%lld%lld",&n,&K);
	n=min(n,K-1);
	ll mn=K-n;
	if (mn>n){
		printf("0\n");return 0;
	}
	printf("%lld\n",(n-mn+1)/2);
	return 0;
}
