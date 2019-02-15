#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100000;
const int inf=2147483647;

int Count(int x);

int main(){
	int n,a,b,c,d,x;
	scanf("%d%d%d%d%d%d",&n,&a,&b,&c,&d,&x);
	int cnt0=0,cnt1=0;
	for (int i=1;i<=n;i++){
		x=(1ll*a*x%d*x%d+1ll*x*b%d+c)%d;
		if (Count(x)&1) ++cnt1;
		else ++cnt0;
	}
	printf("%lld\n",1ll*cnt1*cnt0);return 0;
}

int Count(int x){
	int ret=0;
	while (x) x-=(x)&(-x),++ret;
	return ret;
}
