#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=151;
const int maxK=21;
const int Mod=12345678;
const int inf=2147483647;

int n,m,K;
int F[maxN*2][maxN][maxK][maxK];

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	F[0][0][0][0]=1;
	for (int i=0;i<=n;i++)
		for (int j=0;j<=m;j++)
			for (int k=0;k<=K;k++)
				for (int l=0;l<=K;l++)
				{
					if ((i<n)&&(k<K)) F[i+1][j][k+1][max(0,l-1)]=(F[i+1][j][k+1][max(0,l-1)]+F[i][j][k][l])%Mod;
					if ((j<m)&&(l<K)) F[i][j+1][max(0,k-1)][l+1]=(F[i][j+1][max(0,k-1)][l+1]+F[i][j][k][l])%Mod;
				}
	int Ans=0;
	for (int i=0;i<=K;i++) for (int j=0;j<=K;j++) Ans=(Ans+F[n][m][i][j])%Mod;
	printf("%d\n",Ans);
	return 0;
}

