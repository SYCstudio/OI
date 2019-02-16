#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const int maxL=1010;
const int inf=2147483647;

int n,st,mx;
int C[maxN];
bool F[maxN][maxL];

int main()
{
	scanf("%d%d%d",&n,&st,&mx);
	for (int i=1;i<=n;i++) scanf("%d",&C[i]);
	F[0][st]=1;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=mx;j++)
		{
			if (j-C[i]>=0) F[i][j]=F[i][j]|F[i-1][j-C[i]];
			if (j+C[i]<=mx) F[i][j]=F[i][j]|F[i-1][j+C[i]];
		}
	int pos=-1;
	for (int i=mx;i>=0;i--) if (F[n][i]) {pos=i;break;}
	printf("%d\n",pos);
	return 0;
}
