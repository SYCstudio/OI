#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

int n,m;
int Val[maxN];
int S[maxN],T[maxN];
int F[maxN][maxN],Q[maxN];

double Slope(int x1,int x2,int id);

int main()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		if (n+m==0) break;
		mem(S,0);mem(T,0);mem(F,0);
		for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
		for (int i=1;i<=n;i++) S[i]=S[i-1]+Val[i],T[i]=T[i-1]+Val[i]*Val[i];
		for (int i=1;i<=n;i++) F[0][i]=(S[i]*S[i]-T[i])/2;
		/*
		for (int i=1;i<=m;i++)
		{
			F[i][1]=0;
			for (int j=2;j<=n;j++)
			{
				F[i][j]=inf;
				for (int k=1;k<j;k++)
					F[i][j]=min(F[i][j],F[i-1][k]+((S[j]-S[k])*(S[j]-S[k])-T[j]+T[k])/2);
			}
		}
		//*/
		for (int i=1;i<=m;i++)
		{
			int L=1,R=0;
			for (int j=1;j<=n;j++)
			{
				while ((L<R)&&(Slope(Q[L],Q[L+1],i-1)<2.0*S[j])) L++;
				//cout<<"("<<i-1<<","<<Q[L]<<") -> ("<<i<<","<<j<<")"<<endl;
				F[i][j]=F[i-1][Q[L]]+((S[j]-S[Q[L]])*(S[j]-S[Q[L]])-(T[j]-T[Q[L]]))/2;
				while ((L<R)&&(Slope(Q[R-1],Q[R],i-1)>Slope(Q[R],j,i-1))) R--;
				Q[++R]=j;
			}
		}
		//*/
		/*
		for (int i=0;i<=m;i++)
		{
			for (int j=1;j<=n;j++)
				printf("%4d",F[i][j]);
			printf("\n");
		}
		//*/
		printf("%d\n",F[m][n]);
	}
	return 0;
}

double Slope(int x1,int x2,int id)
{
	//cout<<"GetSlope:"<<x1<<" "<<x2<<" "<<id<<":"<<endl;
	return (1.0*(2.0*F[id][x1]+S[x1]*S[x1]+T[x1])-1.0*(2.0*F[id][x2]+S[x2]*S[x2]+T[x2]))/(1.0*(S[x1]-S[x2]));
}
