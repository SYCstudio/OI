#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int inf=2147483647;

int n,m;
ll X;
ll A[maxN],B[maxN];
ll L1[maxN],L2[maxN];

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&A[i]),A[i]=A[i-1]+A[i];
	for (int i=1;i<=m;i++) scanf("%lld",&B[i]),B[i]=B[i-1]+B[i];
	scanf("%lld",&X);
	mem(L1,127);mem(L2,127);
	for (int len=1;len<=n;len++)
		for (int l=1;l+len-1<=n;l++)
			L1[len]=min(L1[len],A[l+len-1]-A[l-1]);
	for (int len=1;len<=m;len++)
		for (int l=1;l+len-1<=m;l++)
			L2[len]=min(L2[len],B[l+len-1]-B[l-1]);
	ll Ans=0;
	for (int i=1,j=m;i<=n;i++){
		while ((j>=1)&&(L2[j]*L1[i]>X)) j--;
		if (L2[j]*L1[i]<=X) Ans=max(Ans,1ll*i*j);
	}
	printf("%lld\n",Ans);return 0;
}
