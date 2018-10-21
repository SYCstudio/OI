#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int inf=2147483647;

int n;
int L[maxN],R[maxN];
int Q[maxN];

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&L[i],&R[i]);
	int Ans=1,p1=1,p2=0;
	for (int l=1,r=1;l<=n;l++)
	{
		while ((r<=n)&&((p1>p2)||(R[r]>=L[Q[p1]])))
		{
			while ((p1<=p2)&&(L[Q[p2]]<=L[r])) p2--;
			Q[++p2]=r;r++;
		}
		Ans=max(Ans,r-l);
		if (Q[p1]==l) p1++;
	}
	printf("%d\n",Ans);
	return 0;
}
