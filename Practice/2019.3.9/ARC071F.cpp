#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000100<<1;
const int Mod=1e9+7;

int n;
int F[maxN],G[maxN];

int main()
{
	scanf("%d",&n);
	F[0]=G[0]=1;
	for (int i=1; i<=n+n; i++) {
		int l=max(0,i-n-1),r=min(n-1,i-3);
		if (l<=r) F[i]=(((F[i]+G[r]-(l?G[l-1]:0))%Mod)+Mod)%Mod;
		if (i<=n) F[i]=(F[i]+F[i-1])%Mod;
		G[i]=(G[i-1]+F[i])%Mod;
	}
	int Ans=(G[n+n]-G[n-1]+Mod)%Mod;
	for (int i=0; i+2<=n; i++) {
		if (i+2<=n) Ans=(Ans+1ll*F[i]*(n-1)%Mod*(n-1)%Mod)%Mod;
		//else if (i+1<=n) Ans=(Ans+1ll*F[i]*(n-1)%Mod)%Mod;
	}
	printf("%d\n",Ans);
	return 0;
}