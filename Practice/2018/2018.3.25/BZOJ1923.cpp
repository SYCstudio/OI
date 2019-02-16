#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2010;
const int inf=2147483647;

int n,m;
int Ans=0;
bitset<maxN> A[maxN];
char Input[maxN];

void Gauss();

int main()
{
	ios::sync_with_stdio(false);

	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		cin>>(Input+1);
		for (int j=1;j<=n;j++) A[i][j]=Input[j]-'0';
		int x;cin>>x;
		A[i][n+1]=x;
	}
	Gauss();
	if (Ans==-1){
		cout<<"Cannot Determine"<<endl;
		return 0;
	}
	cout<<Ans<<endl;
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n+1;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
	//*/
	for (int i=1;i<=n;i++)
		if (A[i][n+1]) cout<<"?y7M#"<<endl;
		else cout<<"Earth"<<endl;
	return 0;
}

void Gauss()
{
	int now=0;
	for (int i=1;i<=n;i++)
	{
		int j=now+1;
		while ((A[j][i]==0)&&(j<=m)) j++;
		if (j==m+1){
			Ans=-1;break;
		}
		now++;if (now!=j) swap(A[now],A[j]);
		Ans=max(Ans,j);
		for (int k=1;k<=m;k++)
			if ((k!=now)&&(A[k][i]==1)) A[k]^=A[now];
	}
	return;
}
