#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=32;
const int Mod=2017;
const int inf=2147483647;

int n,m;
int Ans[maxN][maxN],Mat[maxN][maxN];
int Backup[maxN][maxN];

void Mul1();
void Mul2();

int main()
{
	ios::sync_with_stdio(false);

	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		Mat[u][v]=Mat[v][u]=1;
	}
	for (int i=0;i<=n;i++) Mat[i][i]=Mat[i][0]=1;
	/*
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=n;j++)
			cout<<Mat[i][j]<<" ";
		cout<<endl;
	}
	//*/
	Ans[0][1]=1;
	int T;cin>>T;
	while (T)
	{
		if (T&1) Mul1();
		Mul2();
		T=T>>1;
	}
	ll sum=0;
	for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) sum=(sum+Ans[i][j])%Mod;
	//cout<<Ans[0][0]<<endl;
	cout<<sum<<endl;
	return 0;
}

void Mul1()
{
	for (int i=0;i<=n;i++) Backup[0][i]=Ans[0][i],Ans[0][i]=0;
	for (int i=0;i<=0;i++)
		for (int j=0;j<=n;j++)
			for (int k=0;k<=n;k++)
				Ans[i][j]=(Ans[i][j]+Backup[i][k]*Mat[k][j]%Mod)%Mod;
	return;
}

void Mul2()
{
	for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) Backup[i][j]=Mat[i][j],Mat[i][j]=0;
	for (int i=0;i<=n;i++)
		for (int j=0;j<=n;j++)
			for (int k=0;k<=n;k++)
				Mat[i][j]=(Mat[i][j]+Backup[i][k]*Backup[k][j]%Mod)%Mod;
	return;
}

