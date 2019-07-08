#include<bits/stdc++.h>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=5010;
int n,Col[maxN];
int F[maxN][maxN][2];

int c(int l,int r)
{
	return Col[l]!=Col[r];
}
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%d",&Col[i]);
	mem(F,63);
	for (int i=1; i<=n; i++) F[i][i][0]=F[i][i][1]=0;
	for (int len=1; len<n; len++)
		for (int l=1; l+len-1<=n; l++)
			for (int b=0; b<=1; b++) {
				int r=l+len-1,p=(b?r:l);
				if (l>1) F[l-1][r][0]=min(F[l-1][r][0],F[l][r][b]+c(l-1,p));
				if (r<n) F[l][r+1][1]=min(F[l][r+1][1],F[l][r][b]+c(r+1,p));
			}
	printf("%d\n",min(F[1][n][0],F[1][n][1]));
	return 0;
}