#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2010;
const int maxE=305;
const int inf=2147483647;

int n,m;
int classnum;
int edgenum;
int Dist[maxE][maxE];
int C1[maxN];
int C2[maxN];
double Probo[maxN];
double F[maxN][maxN][2];

int main()
{
	scanf("%d%d%d%d",&n,&m,&classnum,&edgenum);
	for (int i=1;i<=n;i++)
		scanf("%d",&C1[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&C2[i]);
	for (int i=1;i<=n;i++)
		scanf("%lf",&Probo[i]);
	
	for (int i=0;i<=classnum;i++)
		for (int j=0;j<=classnum;j++)
			if (i==j)
				Dist[i][j]=0;
			else
				Dist[i][j]=1e9;
	
	for (int i=0;i<=n;i++)
		for (int j=0;j<=n;j++)
			F[i][j][0]=F[i][j][1]=1e9;
	F[1][0][0]=F[1][1][1]=0;
	
	for (int i=1;i<=edgenum;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if (u==v)
			continue;
		if (w<Dist[u][v])
			Dist[u][v]=Dist[v][u]=w;
	}

	for (int k=1;k<=classnum;k++)
		for (int i=1;i<=classnum;i++)
				for (int j=1;j<=classnum;j++)
					if (Dist[i][k]+Dist[k][j]<Dist[i][j])
						Dist[i][j]=Dist[i][k]+Dist[k][j];
	for (int i=2;i<=n;i++)
	{
		F[i][0][0]=F[i-1][0][0]+Dist[C1[i-1]][C1[i]];
		for (int j=1;j<=min(i,m);j++)
		{
			F[i][j][0]=min(F[i-1][j][0]+Dist[C1[i-1]][C1[i]],
						   F[i-1][j][1]+1.0*Dist[C2[i-1]][C1[i]]*Probo[i-1]
						   +Dist[C1[i-1]][C1[i]]*(1.0-Probo[i-1]));
			F[i][j][1]=min(F[i-1][j-1][0]+Dist[C1[i-1]][C2[i]]*Probo[i]
						   +Dist[C1[i-1]][C1[i]]*(1.0-Probo[i]),
						   F[i-1][j-1][1]+Dist[C2[i-1]][C2[i]]*Probo[i]*Probo[i-1]
						   +Dist[C1[i-1]][C2[i]]*(1.0-Probo[i-1])*Probo[i]
						   +Dist[C2[i-1]][C1[i]]*Probo[i-1]*(1.0-Probo[i])
						   +Dist[C1[i-1]][C1[i]]*(1.0-Probo[i])*(1.0-Probo[i-1]));
			//*/
		}
	}
	double Ans=F[n][0][0];
	for (int i=1;i<=m;i++)
		Ans=min(Ans,min(F[n][i][0],F[n][i][1]));
	printf("%.2f\n",Ans);
	return 0;
}
