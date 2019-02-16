#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

ll n,K,L,R;
ll A[maxN],BS[maxN];
bool vis[maxN];

ll Calc(ll limit);

int main(){
	scanf("%lld%lld%lld%lld",&n,&K,&L,&R);
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]);

	for (int i=K-1;i>=0;i--)
		if (vis[i]==0){
			BS[i]=(1ll<<K)-1;
			for (int j=1;j<=n;j++)
				if (A[j]&(1ll<<i)) BS[i]&=A[j];
				else BS[i]&=(~A[j]);
			for (int j=i;j>=0;j--)
				if (BS[i]&(1ll<<j)) vis[j]=1;
		}

	printf("%lld\n",Calc(R)-Calc(L-1));
	return 0;
}

ll Calc(ll limit){
	if (limit<0) return 0;
	ll ret=0,sum=0;
	for (int i=0;i<K;i++) sum+=(BS[i]!=0);
	for (int i=K-1;i>=0;i--)
		if (BS[i]){
			--sum;
			if (limit>=BS[i]){
				ret|=(1ll<<sum);
				limit-=BS[i];
			}
		}
	return ret+1;
}
