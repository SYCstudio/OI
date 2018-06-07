#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1010;
const int maxM=210;
const int Mod=1000000007;
const int inf=2147483647;

int n,m,K;
char A[maxN];
char B[maxM];
int F[2][maxM][maxM][2];

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	scanf("%s",(A+1));
	scanf("%s",(B+1));
	memset(F,0,sizeof(F));
	F[0][0][0][1]=F[1][0][0][1]=1;
	for (int i=1;i<=n;i++)
	{
		F[i%2][0][0][1]=1;
		for (int j=1;j<=m;j++)
			for (int k=1;k<=K;k++)
			{
				if (A[i]==B[j])
					F[i%2][j][k][0]=(F[(i-1)%2][j-1][k][0]+F[(i-1)%2][j-1][k-1][1])%Mod;
				else
					F[i%2][j][k][0]=0;
				F[i%2][j][k][1]=(F[i%2][j][k][0]+F[(i-1)%2][j][k][1])%Mod;
			}
	}
	printf("%d\n",F[n%2][m][K][1]%Mod);
	return 0;
}

