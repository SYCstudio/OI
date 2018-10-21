#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (((ll)x)*((ll)x))
#define Y(k,j1,j2) (F[j1][k&1]-sqr(Sum[j1])-F[j2][k&1]+sqr(Sum[j2]))
#define X(j1,j2) (Sum[j2]-Sum[j1])

const int maxN=100010;
const int maxK=210;
const int inf=2147483647;

int n,K;
ll Arr[maxN],Queue[maxN];
ll Sum[maxN];
ll F[maxN][2];

int main()
{
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%lld",&Arr[i]);
	for (int i=1;i<=n;i++) Sum[i]=Sum[i-1]+(ll)Arr[i];
	for (int j=1;j<=K;j++)
	{
		int now=j&1;
		int l=1,r=0;
		for (int i=1;i<=n;i++)
		{
			while ((l<r)&&(Y(j-1,Queue[l],Queue[l+1])<=Sum[i]*X(Queue[l],Queue[l+1]))) l++;
			F[i][now]=F[Queue[l]][now^1]+Sum[Queue[l]]*Sum[i]-sqr(Sum[Queue[l]]);
			while ((l<r)&&(Y(j-1,Queue[r-1],Queue[r])*X(Queue[r],i)>=Y(j-1,Queue[r],i)*X(Queue[r-1],Queue[r]))) r--;
			Queue[++r]=i;
		}
	}
	printf("%lld\n",F[n][K&1]);
	return 0;
}
