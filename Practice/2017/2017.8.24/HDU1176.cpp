#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxPos=15;
const int maxT=100011;
const int inf=2147483647;

int n;
int T;
int F[maxT][maxPos];

int main()
{
	while(cin>>n)
	{
		if (n==0)
			break;
		T=0;
		memset(F,0,sizeof(F));
		for (int i=1;i<=n;i++)
		{
			int pos,tpie;
			scanf("%d%d",&pos,&tpie);
			F[tpie][pos]++;
			T=max(T,tpie);
		}
		for (int i=T;i>=0;i--)
		{
			F[i][0]+=max(F[i+1][0],F[i+1][1]);
			for (int j=1;j<=9;j++)
				F[i][j]+=max(F[i+1][j],max(F[i+1][j-1],F[i+1][j+1]));
			F[i][10]+=max(F[i+1][10],F[i+1][9]);
		}
		printf("%d\n",F[0][5]);
	}
	return 0;
}
