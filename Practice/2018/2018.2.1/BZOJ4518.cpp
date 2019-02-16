#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (((ll)x)*(x))
#define Y(k,j1,j2) ((ll)F[k][j1]-(ll)F[k][j2]+(ll)sqr(Sum[j1])-(ll)sqr(Sum[j2]))
#define X(j1,j2) ((ll)Sum[j1]-(ll)Sum[j2])

const int maxN=3010;
const int inf=2147483647;

ll n,m;
ll Length[maxN],Sum[maxN],Queue[maxN];
ll F[maxN][maxN];

int main()
{
	scanf("%lld%lld",&n,&m);mem(F,63);F[0][0]=0;
	for (ll i=1;i<=n;i++) scanf("%lld",&Length[i]),Sum[i]=Sum[i-1]+Length[i];
	for (ll i=1;i<=m;i++)
	{
		ll l=0,r=0;
		for (ll j=1;j<=n;j++)
		{
			while ((l<r)&&(Y(i-1,Queue[l],Queue[l+1])>2*Sum[j]*X(Queue[l],Queue[l+1]))) l++;
			F[i][j]=F[i-1][Queue[l]]+sqr(Sum[j]-Sum[Queue[l]]);
			while ((l<r)&&(Y(i-1,Queue[r-1],Queue[r])*X(Queue[r],j)>Y(i-1,Queue[r],j)*X(Queue[r-1],Queue[r]))) r--;
			Queue[++r]=j;
		}
	}
	printf("%lld\n",(ll)m*F[m][n]-sqr(Sum[n]));
	return 0;
}
