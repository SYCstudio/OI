#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

const int maxN=55;
const double eps=1e-8;

int n,m;
int A[maxN];
double F[maxN][maxN][maxN],C[maxN][maxN];

int main()
{
	for (int i=0; i<maxN; i++) for (int j=C[i][0]=1; j<maxN; j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) scanf("%d",&A[i]);
	F[0][0][0]=1;
	for (int i=0; i<m; i++)
		for (int j=0; j<=n; j++)
			for (int l=0; l<=n; l++)
				if (F[i][j][l]>eps)
					for (int k=0; j+k<=n; k++) {
						int mx=max(l,(k+A[i+1]-1)/A[i+1]);
						F[i+1][j+k][mx]+=F[i][j][l]*C[n-j][k];
					}
	double Ans=0;
	for (int i=0; i<=n; i++) Ans+=F[m][n][i]*i;
	Ans=Ans/pow(m,n);
	printf("%.18lf\n",Ans);
	return 0;
}