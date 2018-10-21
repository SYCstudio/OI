#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int inf=2147483647;

int n,Ans=0;
int Col[maxN],Colf[maxN];
set<int> S[maxN];

void Merge(int u,int v);

int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=1000000;i++) Colf[i]=i;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&Col[i]);
		if (Col[i]!=Col[i-1]) Ans++;
		S[Col[i]].insert(i);
	}
	while (m--)
	{
		int opt;scanf("%d",&opt);
		if (opt==1)
		{
			int u,v;scanf("%d%d",&u,&v);
			if (u==v) continue;
			if (S[Colf[u]].size()>S[Colf[v]].size()) swap(Colf[u],Colf[v]);
			Merge(Colf[u],Colf[v]);
		}
		if (opt==2) printf("%d\n",Ans);
	}
	return 0;
}

void Merge(int u,int v)
{
	for (set<int>::iterator i=S[u].begin();i!=S[u].end();i++)
	{
		if (Col[*i-1]==v) Ans--;
		if (Col[*i+1]==v) Ans--;
		S[v].insert(*i);
	}
	for (set<int>::iterator i=S[u].begin();i!=S[u].end();i++)
	    Col[*i]=v;
	S[u].clear();
	return;
}
