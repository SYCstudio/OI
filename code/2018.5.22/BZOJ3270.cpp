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

const int maxN=23;
const int maxM=maxN*maxN;
const ld eps=1e-13;
const int inf=2147483647;

int n,m;
int S,T;
ld P[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Id[maxN][maxN];
ld Degree[maxN],To[maxN];
ld Mat[maxN*maxN][maxN*maxN];

int main()
{
	mem(Head,-1);
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
		Degree[u]+=1.0;Degree[v]+=1.0;
	}
	for (int i=1;i<=n;i++) scanf("%LF",&P[i]);
	for (int i=1;i<=n;i++) To[i]=(1.0-P[i])/Degree[i];

	int idcnt=0;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Id[i][j]=++idcnt;

	for (int u=1;u<=n;u++)
		for (int v=1;v<=n;v++)
		{
			if (u!=v) Mat[Id[u][v]][Id[u][v]]=(P[u]*P[v]-1.0);
			else Mat[Id[u][v]][Id[u][v]]=1.0;
			for (int e1=Head[u];e1!=-1;e1=Next[e1])
				for (int e2=Head[v];e2!=-1;e2=Next[e2])
				{
					if ((u!=V[e2])&&(v!=V[e2])) Mat[Id[u][v]][Id[u][V[e2]]]=P[u]*(1.0-P[V[e2]])/(ld)Degree[V[e2]];
					if ((u!=V[e1])&&(v!=V[e1])) Mat[Id[u][v]][Id[V[e1]][v]]=(1.0-P[V[e1]])*P[v]/(ld)Degree[V[e1]];
					if (V[e1]!=V[e2]) Mat[Id[u][v]][Id[V[e1]][V[e2]]]=(1.0-P[V[e1]])*(1.0-P[V[e2]])/(ld)Degree[V[e1]]/(ld)Degree[V[e2]];
				}
		}
	Mat[Id[S][T]][idcnt+1]=1;
	/*
	for (int i=1;i<=idcnt;i++)
	{
		for (int j=1;j<=idcnt+1;j++) printf("%.4LF ",Mat[i][j]);
		printf("\n");
	}
	//*/
	for (int i=1;i<=idcnt;i++)
	{
		int j=i;
		while (fabs(Mat[j][i])<eps) j++;
		for (int k=1;k<=idcnt+1;k++) swap(Mat[j][k],Mat[i][k]);
		ld d=(ld)1.0/Mat[i][i];
		for (int k=1;k<=idcnt+1;k++) Mat[i][k]*=d;
		for (int k=1;k<=idcnt;k++)
			if ((k!=i)&&(fabs(Mat[k][i])>eps))
			{
				d=Mat[k][i]/Mat[i][i];
				for (int l=1;l<=idcnt+1;l++) Mat[k][l]=Mat[k][l]-Mat[i][l]*d;
			}
	}
	ld sum=0;
	for (int i=1;i<=n;i++) sum=sum+Mat[Id[i][i]][idcnt+1];
	//for (int i=1;i<=n;i++) printf("%.4LF ",Mat[Id[i][i]][idcnt+1]);printf("\n");
	/*
	printf("\n");
	for (int i=1;i<=idcnt;i++)
	{
		for (int j=1;j<=idcnt+1;j++) printf("%.4LF ",Mat[i][j]);
		printf("\n");
	}
	//*/
	for (int i=1;i<=n;i++) printf("%.6LF ",Mat[Id[i][i]][idcnt+1]/sum);
	return 0;
}

