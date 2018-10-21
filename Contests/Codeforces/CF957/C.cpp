#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

int n,U;
int E[maxN];

int main()
{
	ios::sync_with_stdio(false);

	cin>>n>>U;
	for (int i=1;i<=n;i++) cin>>E[i];
	ld Ans=0;
	bool getans=0;
	for (int i=1,p=1;i<n;i++)
	{
		while ((p<n)&&(E[p+1]<=E[i]+U)) p++;
		if (i+2<=p) getans=1,Ans=max(Ans,(ld)(E[p]-E[i+1])/(ld)(E[p]-E[i]));
	}
	if (getans) printf("%.12LF\n",Ans);
	else printf("-1\n");
	return 0;
}
