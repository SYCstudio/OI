#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

int n;
ll L[maxN],R[maxN],Ans;

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&L[i],&R[i]),Ans+=L[i]+R[i]+1;
	sort(&L[1],&L[n+1]);sort(&R[1],&R[n+1]);
	for (int i=1;i<=n;i++) Ans-=min(L[i],R[i]);
	printf("%lld\n",Ans);return 0;
}
