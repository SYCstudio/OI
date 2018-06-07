#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int inf=2147483647;

int main()
{
	int n,k,m;
	while (scanf("%d%d%d",&n,&k,&m)!=EOF)
	{
		if ((n==0)&&(m==0)&&(k==0))
			break;
		int f=0;
		for (int i=2;i<=n;i++)
			f=(f+k)%i;
		f=(f+m-k+1)%n;
		if (f<=0)
			f=f+n;
		printf("%d\n",f);
	}
	return 0;
}
