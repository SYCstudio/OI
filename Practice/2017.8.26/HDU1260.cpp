#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2010;
const int inf=147483647;

int n;
int C1[maxN];
int C2[maxN];
int F[maxN];

int main()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&C1[i]);
		for (int i=2;i<=n;i++)
			scanf("%d",&C2[i]);
		for (int i=0;i<=n;i++)
			F[i]=inf;
		F[0]=0;
		F[1]=C1[1];
		for (int i=2;i<=n;i++)
			F[i]=min(F[i],min(F[i-1]+C1[i],F[i-2]+C2[i]));
		int hh=8,mm=0,ss=0;
		ss=ss+F[n];
		mm=ss/60;
		ss=ss%60;
		hh=hh+mm/60;
		mm=mm%60;
		bool is_am=1;
		if (hh>=13)
		{
			hh=hh-12;
			is_am=0;
		}
		if (is_am)
			printf("%02d:%02d:%02d am\n",hh,mm,ss);
		else
			printf("%02d:%02d:%02d pm\n",hh,mm,ss);
		//printf("%d\n",F[n]);
	}
	return 0;
}
