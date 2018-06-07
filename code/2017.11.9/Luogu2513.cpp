#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1010;
const int Mod=10000;
const int inf=2147483647;

int n,K;
int F[maxN][maxN];
int Sum[maxN][maxN];

int main()
{
    scanf("%d%d",&n,&K);
    F[1][0]=1;
    Sum[1][1]=1;
    for (int i=2;i<=K+1;i++) Sum[1][i]=Sum[1][i-1];
    for (int i=2;i<=n;i++)
    {
		for (int j=0;j<=K;j++)
		{
			F[i][j]=(Sum[i-1][j+1]-Sum[i-1][max(j-i+1,0)]+Mod)%Mod;//由于左端点可能是0,再减一会变成负下标,所以整体向上移一位
			Sum[i][j+1]=(Sum[i][j]+F[i][j]+Mod)%Mod;
		}
		Sum[i][K+1]=(Sum[i][K]+F[i][K]+Mod)%Mod;
    }
    printf("%d\n",F[n][K]);
    return 0;
}
