//借助斜率优化的思想，单调队列维护递增的斜率
//该题卡读入优化，目前TLE
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n,K;
int A[maxN],Q[maxN];

int Read();
double Slope(int x1,int x2);

int main()
{
	while (scanf("%d%d",&n,&K)!=EOF)
	{
		for (int i=1;i<=n;i++) A[i]=Read();//scanf("%d",&A[i]);
		for (int i=1;i<=n;i++) A[i]+=A[i-1];
		double Ans=0;
		int L=1,R=0;
		for (int i=K;i<=n;i++)
		{
			while ((L<R)&&(Slope(Q[R-1],Q[R])>Slope(Q[R],i-K))) R--;
			Q[++R]=i-K;
			while ((L<R)&&(Slope(Q[L],i)<Slope(Q[L+1],i))) L++;
			Ans=max(Ans,1.0*(A[i]-A[Q[L]])/(1.0*(i-Q[L])));
		}
		printf("%.2lf\n",Ans);
	}
	return 0;
}

double Slope(int x1,int x2)
{
	return 1.0*(A[x1]-A[x2])/(1.0*(x1-x2));
}

int Read()
{
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!=EOF)) ch=getchar();
	int x=0;
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-'0',ch=getchar();
	return x;
}
