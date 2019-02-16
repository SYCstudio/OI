#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=60;
const int inf=2147483647;

int n,m;
int G[maxN][maxN];
bool F[40][maxN][maxN];

int main()
{
	memset(G,120,sizeof(G));
	memset(F,0,sizeof(F));
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u][v]=1;
		F[0][u][v]=1;
	}
	for (int i=1;i<=36;i++)
	    for (int u=1;u<=n;u++)
			for (int v=1;v<=n;v++)
				for (int k=1;k<=n;k++)
						if ((F[i-1][u][k]==1)&&(F[i-1][k][v]==1))
						{
							F[i][u][v]=1;
							G[u][v]=1;
						}
    for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
				for (int k=1;k<=n;k++)
					if (G[i][k]+G[k][j]>=0)
						G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	cout<<G[1][n]<<endl;
	return 0;
}
