#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int inf=2147483647;

int n;
int Arr[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>Arr[i];
	sort(&Arr[1],&Arr[n+1]);
	int numcnt=unique(&Arr[1],&Arr[n+1])-Arr-1;
	int Ans=0;
	if (Arr[1]==0) Ans=max(0,numcnt-1);
	else Ans=max(0,numcnt);
	printf("%d\n",Ans);
	return 0;
}
