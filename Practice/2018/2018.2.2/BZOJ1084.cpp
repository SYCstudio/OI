#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int maxM=3;
const int maxK=11;
const int inf=2147483647;

int n,m,K;
int Mat[maxN][maxM],Sum[maxN][maxM];
int F1[maxK][maxN];
int F2[maxK][maxN][maxN];

void Do1();
void Do2();

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	if (m==1) Do1();
	else Do2();
	return 0;
}

void Do1()
{
	for (int i=1;i<=n;i++) scanf("%d",&Mat[i][1]),Sum[i][1]=Sum[i-1][1]+Mat[i][1];
	F1[0][0]=0;
	for (int i=1;i<=K;i++)
		for (int j=1;j<=n;j++)
		{
			F1[i][j]=F1[i][j-1];//这一步保证从前面取得最优值
			for (int k=0;k<j;k++)
				F1[i][j]=max(F1[i][j],F1[i-1][k]+Sum[j][1]-Sum[k][1]);
		}
	printf("%d\n",F1[K][n]);
	return;
}

void Do2()
{
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&Mat[i][1],&Mat[i][2]);
		Sum[i][1]=Sum[i-1][1]+Mat[i][1];
		Sum[i][2]=Sum[i-1][2]+Mat[i][2];
	}
	F2[0][0][0]=0;
	for (int i=1;i<=K;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
			{
				F2[i][j][k]=max(F2[i][j-1][k],F2[i][j][k-1]);
				for (int pos=0;pos<j;pos++) F2[i][j][k]=max(F2[i][j][k],F2[i-1][pos][k]+Sum[j][1]-Sum[pos][1]);
				for (int pos=0;pos<k;pos++) F2[i][j][k]=max(F2[i][j][k],F2[i-1][j][pos]+Sum[k][2]-Sum[pos][2]);
				if (j==k)
					for (int pos=0;pos<j;pos++) F2[i][j][k]=max(F2[i][j][k],F2[i-1][pos][pos]+Sum[j][1]-Sum[pos][1]+Sum[k][2]-Sum[pos][2]);
			}
	/*
	for (int i=1;i<=K;i++)
	{
		for (int j=1;j<=n;j++)
		{
			for (int k=1;k<=n;k++)
				cout<<F2[i][j][k]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	//*/
	printf("%d\n",F2[K][n][n]);
	return;
}
