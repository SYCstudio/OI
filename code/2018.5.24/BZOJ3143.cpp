#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=510;
const int maxM=maxN*maxN;
const ld eps=1e-7;
const int inf=2147483647;

int n,m;
ld Degree[maxN];
int U[maxM],V[maxM];
ld Mat[maxN][maxN],W[maxM];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&U[i],&V[i]);
		Degree[U[i]]+=1.0;Degree[V[i]]+=1.0;
	}
	for (int i=1;i<=m;i++)
	{
		Mat[U[i]][V[i]]-=(ld)1.0/Degree[V[i]];
		Mat[V[i]][U[i]]-=(ld)1.0/Degree[U[i]];
	}
	for (int i=1;i<=n+1;i++) Mat[n][i]=0;
	for (int i=1;i<=n;i++) Mat[i][i]=1;
	Mat[1][n+1]=1;//Mat[n][n+1]=1;

	for (int i=1;i<=n;i++)
	{
		int j=i;
		while (fabs(Mat[j][i])<eps) j++;
		for (int k=1;k<=n+1;k++) swap(Mat[j][k],Mat[i][k]);
		ld d=(ld)1.0/Mat[i][i];
		for (int k=1;k<=n+1;k++) Mat[i][k]*=d;
		for (int k=1;k<=n;k++)
			if ((i!=k)&&(fabs(Mat[k][i])>eps))
			{
				d=Mat[k][i]/Mat[i][i];
				for (int l=1;l<=n+1;l++) Mat[k][l]=Mat[k][l]-Mat[i][l]*d;
			}
	}
	for (int i=1;i<=m;i++) W[i]=Mat[U[i]][n+1]/Degree[U[i]]+Mat[V[i]][n+1]/Degree[V[i]];
	sort(&W[1],&W[m+1]);
	ld Ans=0;
	for (int i=1;i<=m;i++) Ans=Ans+W[i]*(ld)(m-i+1);
	printf("%.3LF\n",Ans);
	return 0;
}
