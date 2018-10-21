//分数规划，二分后判断函数与0的关系
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const double eps=1e-8;
const int inf=2147483647;

int n,K;
int A[maxN],B[maxN];
double D[maxN];

double Calc(double mid);

int main()
{
	while (scanf("%d%d",&n,&K)!=EOF)
	{
		if ((n==0)&&(K==0)) break;
		for (int i=1;i<=n;i++) scanf("%d",&A[i]);
		for (int i=1;i<=n;i++) scanf("%d",&B[i]);
		double L=0,R=1,Ans;
		for (int i=1;i<=n;i++) R=max(R,1.0*A[i]/1.0*B[i]);
		do
		{
			double mid=(L+R)/2.0;
			if (Calc(mid)<=eps) Ans=mid,R=mid;
			else L=mid;
		}
		while (L+eps<R);
		printf("%.0lf\n",Ans*100);
	}
	return 0;
}

double Calc(double mid)
{
	for (int i=1;i<=n;i++) D[i]=1.0*A[i]-1.0*B[i]*mid;
	sort(&D[1],&D[n+1]);
	double sum=0;
	for (int i=K+1;i<=n;i++) sum+=D[i];
	return sum;
}
