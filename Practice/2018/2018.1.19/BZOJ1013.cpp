#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ld long double

const int maxN=20;
const int inf=2147483647;

int n;
ld Mat[maxN][maxN];
ld Input[maxN][maxN];
ld Ans[maxN];

void Guess();

int main()
{
	scanf("%d",&n);
	for (int i=0;i<=n;i++) for (int j=1;j<=n;j++) scanf("%LF",&Input[i][j]);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) Mat[i][j]=(ld)2*(Input[i][j]-Input[0][j]);
		ld s1=0,s2=0;
		for (int j=1;j<=n;j++) s1=s1+Input[i][j]*Input[i][j],s2=s2+Input[0][j]*Input[0][j];
		Mat[i][n+1]=s1-s2;
	}
	Guess();
	printf("%.3LF",Ans[1]);
	for (int i=2;i<=n;i++) printf(" %.3LF",Ans[i]);
	return 0;
}

void Guess()
{
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			ld ret=Mat[j][i]/Mat[i][i];
			for (int k=i;k<=n+1;k++)
				Mat[j][k]-=Mat[i][k]*ret;
		}
	Ans[n]=Mat[n][n+1]/Mat[n][n];
	for (int i=n-1;i>=1;i--)
	{
		ld sum=0;
		for (int j=i;j<=n;j++) sum=sum+Mat[i][j]*Ans[j];
		Ans[i]=(Mat[i][n+1]-sum)/Mat[i][i];
	}
	return;
}
