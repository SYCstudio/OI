#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long

const int maxN=200100;
const int Mod=10007;
const int inf=2147483647;

int n;
vector<int> E[maxN];
int W[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	for (int i=1;i<=n;i++)
		scanf("%d",&W[i]);
	ll Ans=0;
	ll maxW=0;
	for (int i=1;i<=n;i++)
	{
		ll nowsum=0;
		ll max1=0,max2=0;
		for (int j=0;j<E[i].size();j++)
		{
			int v=E[i][j];
			Ans=(Ans+nowsum*W[v]%Mod)%Mod;
			nowsum=(nowsum+W[v])%Mod;
			if (W[v]>=max1)
			{
				max2=max1;
				max1=W[v];
			}
			else
				if (W[v]>max2)
					max2=W[v];
		}
		maxW=max(maxW,max1*max2);
	}
	cout<<maxW<<" "<<Ans*2%Mod<<endl;
	return 0;
}
