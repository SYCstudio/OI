//动态规划，重要思想是把后面的代价也一起算，这样就不用记录时间了。
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

class Data
{
public:
	int x,y,v;
};

int n,X0;
Data D[maxN];
int Sum[maxN],F[maxN][maxN][2];

bool cmp(Data A,Data B);

int main()
{
	scanf("%d%d",&n,&X0);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].x);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].y);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].v);

	sort(&D[1],&D[n+1],cmp);

	for (int i=1;i<=n;i++) Sum[i]=Sum[i-1]+D[i].v;

	for (int i=1;i<=n;i++) F[i][i][0]=F[i][i][1]=D[i].y-Sum[n]*abs(X0-D[i].x);

	for (int len=2;len<=n;len++)
		for (int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			F[l][r][0]=max(F[l+1][r][0]+D[l].y-(Sum[n]-Sum[r]+Sum[l])*abs(D[l+1].x-D[l].x)
						   ,F[l+1][r][1]+D[l].y-(Sum[n]-Sum[r]+Sum[l])*abs(D[r].x-D[l].x));
			F[l][r][1]=max(F[l][r-1][0]+D[r].y-(Sum[n]-Sum[r-1]+Sum[l-1])*abs(D[r].x-D[l].x)
						   ,F[l][r-1][1]+D[r].y-(Sum[n]-Sum[r-1]+Sum[l-1])*abs(D[r].x-D[r-1].x));
		}
	printf("%.3lf\n",1.0*max(F[1][n][0],F[1][n][1])/1000.0);
	return 0;
}

bool cmp(Data A,Data B){
	return A.x<B.x;
}
