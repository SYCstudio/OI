#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=60000;
const int maxL=1000000000;
const int inf=2147483647;

int n,m,L;
int D[maxN];

bool check(int mid);

int main()
{
	scanf("%d%d%d",&L,&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&D[i]);
	int l=0,r=maxL;
	int Ans=0;
	do
	{
		int mid=(l+r)/2;
		if (check(mid))
		{
			Ans=max(Ans,mid);
			l=mid+1;
		}
		else
			r=mid-1;
	}
	while (l<=r);
	if (check(l))
		Ans=max(Ans,l);
	if (check(r))
		Ans=max(Ans,r);
	printf("%d\n",Ans);
	return 0;
}

bool check(int mid)
{
	int Mcnt=0;
	int lastpos=0;
	for (int i=1;i<=n;i++)
		if (D[i]-lastpos<mid)
			Mcnt++;
		else
			lastpos=D[i];
	if (L-lastpos<mid)
		Mcnt++;
	return Mcnt<=m;
}
