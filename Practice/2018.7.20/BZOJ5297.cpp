#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int Mod=10007;
const int inf=2147483647;

int n,m;
int Mat[maxN][maxN];

int Guass();

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Mat[u][v]--;Mat[u][u]++;
	}

	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			cout<<Mat[i][j]<<" ";
		cout<<endl;
	}
	//*/

	printf("%d\n",Guass());
}

int Guass()
{
	int ret=1;
	for (int i=2;i<=n;i++)
	{
		for (int j=i+1;j<=n;j++)
			while (Mat[j][i])
			{
				int p=Mat[i][i]/Mat[j][i];
				for (int k=i;k<=n;k++) Mat[i][k]=(Mat[i][k]-1ll*Mat[j][k]*p%Mod+Mod)%Mod;
				ret=-ret;
				swap(Mat[i],Mat[j]);
			}
		//cout<<Mat[i][i]<<endl;
		ret=1ll*ret*Mat[i][i]%Mod;
	}
	return (ret+Mod)%Mod;
}
