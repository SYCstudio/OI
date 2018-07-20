#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=17;
const int Mod=1e9+7;
const int inf=2147483647;

class Edge
{
public:
	int u,v;
};

int n;
vector<Edge> E[maxN];
int Mat[maxN][maxN];

int Guass();

int main()
{
	scanf("%d",&n);
	for (int i=0;i<n-1;i++)
	{
		int cnt;scanf("%d",&cnt);
		for (int j=1;j<=cnt;j++)
		{
			int u,v;scanf("%d%d",&u,&v);
			E[i].push_back((Edge){u,v});
		}
	}

	int Ans=0;
	for (int S=0;S<(1<<(n-1));S++)
	{
		int opt=0;
		mem(Mat,0);
		for (int i=0;i<n;i++)
			if (S&(1<<i)){
				opt++;
				for (int sz=E[i].size(),j=0;j<sz;j++){
					Mat[E[i][j].u][E[i][j].v]--;
					Mat[E[i][j].v][E[i][j].u]--;
					Mat[E[i][j].u][E[i][j].u]++;
					Mat[E[i][j].v][E[i][j].v]++;
				}
			}
		if ((opt&1)==((n-1)&1)) Ans=(Ans+Guass())%Mod;
		else Ans=(Ans-Guass()+Mod)%Mod;
	}
	printf("%d\n",Ans);
	return 0;
}

int Guass()
{
	int ret=1;
	for (int i=1;i<n;i++)
	{
		for (int j=i+1;j<n;j++)
			while (Mat[j][i])
			{
				int p=Mat[i][i]/Mat[j][i];
				for (int k=i;k<n;k++) Mat[i][k]=(Mat[i][k]-1ll*Mat[j][k]*p%Mod+Mod)%Mod;
				swap(Mat[i],Mat[j]);
				ret=-ret;
			}
		ret=1ll*ret*Mat[i][i]%Mod;
	}
	return (ret+Mod)%Mod;
}

/*
4
2 3 2 4 2
5 2 1 3 1 3 2 4 1 4 3
4 2 1 3 2 4 1 4 2
//*/
