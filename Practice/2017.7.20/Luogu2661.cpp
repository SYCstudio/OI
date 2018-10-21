#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=200001;
const int inf=2147483647;

int n;
int Edge[maxN];
int InDegree[maxN];
int vis[maxN];
queue<int> Q;

int main()
{
	memset(InDegree,0,sizeof(InDegree));
	memset(vis,0,sizeof(vis));
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>Edge[i];
		InDegree[Edge[i]]++;
	}
	for (int i=1;i<=n;i++)
		if (InDegree[i]==0)
		{
			Q.push(i);
			vis[i]=-1;
		}
    while (!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		InDegree[Edge[u]]--;
		if (InDegree[Edge[u]]==0)
		{
			vis[Edge[u]]=-1;
			Q.push(Edge[u]);
		}
	}
	int Ans=inf;
	for (int i=1;i<=n;i++)
		if (vis[i]==0)
		{
			vis[i]=1;
			int u=i;
			int cnt=1;
			while (vis[Edge[u]]==0)
			{
				u=Edge[u];
				vis[u]=1;
				cnt++;
			}
			Ans=min(Ans,cnt);
		}
	cout<<Ans<<endl;
	return 0;
}
