#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=101000;

int n,pcnt;
ll A[maxN],P[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]);
	ll x=A[1];
	for (int i=2;1ll*i*i<=x;i++)
		if (x%i==0){
			P[++pcnt]=i;while (x%i==0) x/=i;
		}
	if (x!=1) P[++pcnt]=x;
	for (int i=1;i<=n;i++){
		ll g=__gcd(A[1],A[i]);
		if (g==1){
			printf("-1 ");continue;
		}
		for (int j=1;j<=pcnt;j++)
			if (g%P[j]==0){
				printf("%lld ",g/P[j]);
				break;
			}
	}
	return 0;
}
