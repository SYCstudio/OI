#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=20011;
const int maxM=2011;
const int inf=147483647;

int n,m,K;
int X[maxN];
int Y[maxN];
bool is_pipe[maxN];
int Pipe_up[maxN];
int Pipe_down[maxN];
int F[2][maxM];

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	memset(Pipe_up,0,sizeof(Pipe_up));
	memset(Pipe_down,0,sizeof(Pipe_down));
	memset(is_pipe,0,sizeof(is_pipe));
	for (int i=0;i<n;i++)
		scanf("%d%d",&X[i],&Y[i]);
	for (int i=1;i<=n;i++)
	{
		Pipe_down[i]=0;
		Pipe_up[i]=m+1;
	}
	for (int i=1;i<=K;i++)
	{
		int pipe_pos,l,r;
		scanf("%d%d%d",&pipe_pos,&l,&r);
		Pipe_down[pipe_pos]=l;
		Pipe_up[pipe_pos]=r;
		is_pipe[pipe_pos]=1;
	}
	for (int i=1;i<=m;i++)
		F[0][i]=0;
	int cnt=0;
	int Ans;
	for (int i=1;i<=n;i++)
	{
		int now=i&1;
		Ans=inf;
		for (int j=0;j<=m;j++)
			F[now][j]=inf;
		//cout<<Pipe_down[i]<<" "<<Pipe_up[i]<<endl;
		
		for (int j=X[i-1]+1;j<=m;j++)
		{
			F[now][j]=min(F[!now][j-X[i-1]],F[now][j-X[i-1]])+1;
			//cout<<F[!now][j-X[i-1]]<<endl;
		}

		for (int j=m-X[i-1];j<=m;j++)
		{
			F[now][m]=min(F[now][m],F[now][j]+1);
			F[now][m]=min(F[now][m],F[!now][j]+1);
		}

		for (int j=m-Y[i-1];j>=1;j--)
			F[now][j]=min(F[now][j],F[!now][j+Y[i-1]]);

		cnt+=(int)(is_pipe[i]);

		for (int j=1;j<=m;j++)
		{
			if ((j<=Pipe_down[i])||(j>=Pipe_up[i]))
				F[now][j]=inf;
			Ans=min(Ans,F[now][j]);
		}
		if (Ans==inf)
		{
			printf("0\n%d\n",cnt-1);
			return 0;
		}
		/*
		for (int j=1;j<=m;j++)
			if (F[now][j]!=inf)
				cout<<F[now][j]<<" ";
			else
				cout<<"i ";
		cout<<endl;
		//*/
	}
	printf("1\n%d\n",Ans);
	return 0;
}
