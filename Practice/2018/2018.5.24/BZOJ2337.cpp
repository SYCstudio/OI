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

const int maxN=110;
const int maxM=10100*2;
const ld eps=1e-6;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
ld Degree[maxN],Mat[maxN][maxN];

void Add_Edge(int u,int v,int w);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
		if (u!=v) Add_Edge(v,u,w);
	}
	ld Ans=0;
	for (int bit=0;bit<31;bit++)
	{
		mem(Mat,0);
		for (int i=1;i<n;i++)
		{
			Mat[i][i]=1;
			for (int j=Head[i];j!=-1;j=Next[j])
				//if (V[j]!=n)
				{
					if ((W[j]&(1<<bit))!=0) Mat[i][V[j]]+=1.0/Degree[i],Mat[i][n+1]+=1.0/Degree[i];
					else Mat[i][V[j]]-=1.0/Degree[i];
				}
		}
		Mat[n][n]=1;

		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n+1;j++) printf("%LF ",Mat[i][j]);
			printf("\n");
		}
		printf("\n");
        //*/
		for (int i=1;i<=n;i++)
		{
			int j=i;
			while (fabs(Mat[j][i])<eps) j++;
			if (i!=j) for (int k=1;k<=n+1;k++) swap(Mat[j][k],Mat[i][k]);
			ld d=(ld)1.0/Mat[i][i];
			for (int k=1;k<=n+1;k++) Mat[i][k]*=d;
			for (int k=1;k<=n;k++)
				if ((k!=i)&&(fabs(Mat[k][i])>0))
				{
					d=Mat[k][i]/Mat[i][i];
					for (int l=1;l<=n+1;l++) Mat[k][l]=Mat[k][l]-Mat[i][l]*d;
				}
		}

		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n+1;j++) printf("%LF ",Mat[i][j]);
			printf("\n");
		}
		printf("\n\n");
		//*/

		Ans=Ans+Mat[1][n+1]*(ld)(1ll<<bit);
	}
	printf("%.3LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	Degree[u]+=1.0;
	return;
}
