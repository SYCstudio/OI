#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxNode=1010000;
const int maxN=210;
const int inf=1147483647;
const ll INF=1e15;

int n,m,S,T;
int nodecnt=0,Map[maxNode];
ll Mat[21][maxN][maxN];
ll Ans[maxN][maxN],Bp[maxN][maxN];

void Mul(int id);

int main()
{
	scanf("%d%d%d%d",&n,&m,&S,&T);
	mem(Mat,63);
	for (int i=1;i<=m;i++)
	{
		int u,v,len;
		scanf("%d%d%d",&len,&u,&v);
		if (Map[u]==0) Map[u]=++nodecnt;
		if (Map[v]==0) Map[v]=++nodecnt;
		u=Map[u];v=Map[v];
		//cout<<u<<" "<<v<<endl;
		Mat[0][u][v]=Mat[0][v][u]=len;
	}
	S=Map[S];T=Map[T];
	for (int i=1;i<=20;i++)
		for (int k=1;k<=nodecnt;k++)
			for (int u=1;u<=nodecnt;u++)
				for (int v=1;v<=nodecnt;v++)
					Mat[i][u][v]=Mat[i][v][u]=min(Mat[i][u][v],Mat[i-1][u][k]+Mat[i-1][k][v]);
	
	/*
	for (int i=0;i<=5;i++)
	{
		for (int u=1;u<=nodecnt;u++)
		{
			for (int v=1;v<=nodecnt;v++)
				cout<<Mat[i][u][v]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	//*/
	for (int i=1;i<=nodecnt;i++) for (int j=1;j<=nodecnt;j++) Ans[i][j]=Mat[0][i][j];
	n--;
	for (int i=0;i<21;i++) if (n&(1<<i)) Mul(i);

	printf("%lld\n",Ans[S][T]);
	return 0;
}

void Mul(int id)
{
	for (int i=1;i<=nodecnt;i++) for (int j=1;j<=nodecnt;j++) Bp[i][j]=Ans[i][j],Ans[i][j]=INF;
	for (int k=1;k<=nodecnt;k++)
		for (int i=1;i<=nodecnt;i++)
			for (int j=1;j<=nodecnt;j++)
				Ans[i][j]=Ans[j][i]=min(Ans[i][j],Bp[i][k]+Mat[id][k][j]);
	return;
}
/*
3 8 1 6
7 1 2
4 1 3
2 2 4
6 3 4
5 3 5
3 4 5
9 4 6
1 5 6
//*/
