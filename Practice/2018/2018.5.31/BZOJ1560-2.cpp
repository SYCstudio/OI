#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;
const ld eps=1e-7;
const int meminf=1061109567;

int n,m;
int Val[maxN][maxN],F[maxN][maxN];
int Dis[maxN],Pos[maxN],Q[maxN];

ld Slope(int x1,int x2);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Val[u][v]=w;
	}
	mem(F,63);
	F[1][1]=Val[1][1];Val[1][1]=0;Pos[1]=1;
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=m;j++)
			if (Pos[j]) Dis[j]=(Pos[j]-i)*(Pos[j]-i);
			else Dis[j]=0;
		int L=1,R=0;
		for (int j=1;j<=m;j++)
		{
			if (Pos[j])
			{
				while ((L<R)&&(Slope(Q[R-1],Q[R])>Slope(Q[R],j)-eps)) R--;
				Q[++R]=j;
			}
			if (Val[i][j])
			{
				while ((L<R)&&(Slope(Q[L],Q[L+1])-eps<j)) L++;
				//cout<<"("<<Pos[Q[L]]<<","<<Q[L]<<")->("<<i<<","<<j<<") "<<F[Pos[Q[L]]][Q[L]]<<endl;
				F[i][j]=F[Pos[Q[L]]][Q[L]]-Dis[Q[L]]-(j-Q[L])*(j-Q[L])+Val[i][j];
				Pos[j]=i;Dis[j]=0;
				while ((L<R)&&(Slope(Q[R-1],Q[R])>Slope(Q[R],j)-eps)) R--;
				Q[++R]=j;
			}
		}
	}
	/*
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=m;j++)
			if (F[i][j]!=meminf) cout<<F[i][j]<<" ";
			else cout<<"inf ";
		cout<<endl;
	}
	//*/
	printf("%d\n",F[m][m]);
	return 0;
}

ld Slope(int y1,int y2)
{
	int x1=Pos[y1],x2=Pos[y2];
	if (y1==y2) return -inf;
	return (ld)1.0*(ld)((y1*y1+Dis[y1]-F[x1][y1])-(y2*y2+Dis[y2]-F[x2][y2]))/((ld)2.0*(y1-y2));
}
