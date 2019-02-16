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
ll Arr[maxN][maxN],F[maxN][maxN];

int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%lld",&Arr[i][j]);
		mem(F,0);
		for (int i=1;i<=n;i++) for (int j=m;j>=1;j--) F[i][j]=max(F[i-1][j+1]+Arr[i][j],max(F[i-1][j],F[i][j+1]));
		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				cout<<F[i][j]<<" ";
			cout<<endl;
		}
		//*/
		printf("%lld\n",F[n][1]);
	}
	return 0;
}

