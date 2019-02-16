#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=60;
const int maxT=300;
const int meminf=2139062143;

int n,T;
int Train[maxN][maxT][2];
int Dist[maxN];
int F[maxT][maxN];

int main()
{
    int cas=0;
    while ((scanf("%d",&n)!=EOF)&&(n!=0))
    {
		mem(Train,0);mem(F,127);
		scanf("%d",&T);
		for (int i=1;i<n;i++) scanf("%d",&Dist[i]);
		int m;scanf("%d",&m);
		for (int i=1;i<=m;i++)
		{
			int nt;scanf("%d",&nt);
			int j=1;
			while ((nt<=T)&&(j<=n))
			{
				Train[j][nt][0]=1;
				nt+=Dist[j];
				j++;
			}
		}
		scanf("%d",&m);
		for (int i=1;i<=m;i++)
		{
			int nt;scanf("%d",&nt);
			int j=n;
			while ((nt<=T)&&(j>=1))
			{
				Train[j][nt][1]=1;
				nt+=Dist[j-1];
				j--;
			}
		}
		F[0][1]=0;
		for (int i=1;i<=T;i++)
			for (int j=1;j<=n;j++)
			{
				F[i][j]=min(F[i][j],F[i-1][j]+1);
				if ((j!=1)&&(Train[j-1][i-Dist[j-1]][0]==1)) F[i][j]=min(F[i][j],F[i-Dist[j-1]][j-1]);
				if ((j!=n)&&(Train[j+1][i-Dist[j]][1]==1)) F[i][j]=min(F[i][j],F[i-Dist[j]][j+1]);
			}
		printf("Case Number %d: ",++cas);
		if (F[T][n]!=meminf) printf("%d\n",F[T][n]);
		else printf("impossible\n");
    }
    return 0;
}
