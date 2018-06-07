#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxN=101;
const int inf=2147483647;

int n,m;
int M[maxN][maxN];

int main()
{
	while (cin>>n>>m)
	{
	memset(M,0,sizeof(M));
	for (int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		M[u][v]=1;
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
	    	for (int j=1;j<=n;j++)
	            M[i][j]=M[i][j] || ((M[i][k])&&(M[k][j]));
	int Ans=0;
	for (int i=1;i<=n;i++)
	{
		int cnt=0;
		for (int j=1;j<=n;j++)
		    if ((i!=j)&&((M[i][j])||(M[j][i])))
		        cnt++;
		if (cnt==n-1)
		    Ans++;
	}
	cout<<Ans<<endl;
    }
	return 0;
}
