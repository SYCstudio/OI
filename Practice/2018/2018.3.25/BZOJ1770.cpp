#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40;
const int inf=2147483647;

int n,m;
int Ans=inf,Status[maxN];
bitset<maxN> A[maxN];

void Gauss();
void dfs(int now,int tot);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		A[u][v]=A[v][u]=1;
	}
	for (int i=1;i<=n;i++) A[i][n+1]=A[i][i]=1;
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n+1;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	//*/
	Gauss();
	dfs(n,0);
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n+1;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
	//*/
	cout<<Ans<<endl;
	return 0;
}

void Gauss()
{
	int now=0;
	for (int i=1;i<=n;i++)
	{
		now++;int j=now;
		while ((A[j][i]==0)&&(j<=n)) j++;
		if (j>n) continue;
		if (now!=j) swap(A[now],A[j]);
		for (int k=1;k<=n;k++)
			if ((k!=now)&&(A[k][i]==1)) A[k]^=A[now];
	}
	return;
}

void dfs(int now,int tot)
{
	if (tot>=Ans) return;
	if (now==0)
	{
		Ans=min(Ans,tot);
		//cout<<tot<<endl;
		//for (int i=1;i<=n;i++) cout<<Status[i]<<" ";cout<<endl;
		return;
	}
	if (A[now][now]==1)//高斯消元时不是自由元
	{
		int t=A[now][n+1];
		for (int i=now+1;i<=n;i++) if (A[now][i]) t^=Status[i];
		Status[now]=t;
		dfs(now-1,tot+t);
	}
	else//是自由元
	{
		Status[now]=0;dfs(now-1,tot);
		Status[now]=1;dfs(now-1,tot+1);
	}
	return;
}
