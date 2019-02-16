#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ld Calc1(int m,int n);
ld Calc2(int m,int n);

int main()
{
	ios::sync_with_stdio(false);

	int T;
	while (cin>>T)
	{
		while (T--)
		{
			int opt,m,n;cin>>opt>>m>>n;
			if (opt==0) printf("%.9lf\n",Calc1(m,n));
			else printf("%.9lf\n",Calc2(m,n));
		}
	}
	return 0;
}

ld Calc1(int m,int n)
{
	return (pow(m,n)-1.0)/(m-1.0);
}

ld Calc2(int m,int n)
{
	ld ret=1;
	for (int i=n-1;i>=1;i--) ret=1.0*m/(m-i)*ret+1.0;
	return ret;
}	
