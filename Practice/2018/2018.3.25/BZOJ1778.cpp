#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const ld eps=1e-13;
const int inf=2147483647;

int n,m,P,Q;
ld F[maxN][maxN];
int Cnt[maxN][maxN],Degree[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>P>>Q;
	ld gl=(ld)1-(ld)P/(ld)Q;
	for (int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		Cnt[u][v]++;Cnt[v][u]++;
		Degree[u]++;Degree[v]++;
	}
	F[1][n+1]=-1;
	for (int i=1;i<=n;i++)
	{
		F[i][i]=-1;
		for (int j=1;j<=n;j++)
			if (Cnt[j][i])
				F[i][j]+=(ld)gl*(ld)Cnt[j][i]/(ld)Degree[j];
	}
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n+1;j++)
			printf("%.6LF ",F[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	int now=0;
	for (int i=1;i<=n;i++)
	{
		int j=i;
		while (fabs(F[j][i])<eps) j++;
		for (int k=1;k<=n+1;k++) swap(F[i][k],F[j][k]);
		ld d=(ld)1/F[i][i];
		for (int k=1;k<=n+1;k++) F[i][k]*=d;
		for (int k=1;k<=n;k++)
			if ((k!=i)&&(fabs(F[k][i])>eps))
			{
				d=F[k][i]/F[i][i];
				for (int l=1;l<=n+1;l++) F[k][l]=F[k][l]-F[i][l]*d;
			}
	}
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n+1;j++)
			printf("%.6LF ",F[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	ld sum=0;
	for (int i=1;i<=n;i++) sum+=F[i][n+1];
	for (int i=1;i<=n;i++) printf("%.9LF\n",fabs(F[i][n+1]/sum));
	return 0;
}
