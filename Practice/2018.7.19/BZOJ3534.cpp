#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51;
const ld eps=1e-8;
const int inf=2147483647;

int n;
ld Mat[maxN][maxN];

ld Guass();

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			scanf("%LF",&Mat[i][j]);
			if (fabs(Mat[i][j])<eps) Mat[i][j]=eps;
			if (fabs(1-Mat[i][j])<eps) Mat[i][j]=1-eps;
		}
	ld sum=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (i!=j)
			{
				if (i<j) sum=sum*(1.0-Mat[i][j]);
				Mat[i][j]=Mat[i][j]/(1.0-Mat[i][j]);
			}

	for (int i=1;i<=n;i++){
		Mat[i][i]=0;
		for (int j=1;j<=n;j++)
			if (i!=j) Mat[i][i]-=Mat[i][j];
	}

	printf("%.10LF\n",Guass()*sum);
	return 0;
}

ld Guass()
{
	ld ret=1;
	for (int i=1;i<n;i++)
	{
		for (int j=i;j<n;j++)
			if (fabs(Mat[i][i])<fabs(Mat[j][i])){
				swap(Mat[i],Mat[j]);
				ret=-ret;
			}
		for (int j=i+1;j<n;j++)
		{
			ld p=Mat[j][i]/Mat[i][i];
			for (int k=1;k<n;k++) Mat[j][k]=Mat[j][k]-Mat[i][k]*p;
		}
		ret=ret*Mat[i][i];
	}
	return fabs(ret);
}
