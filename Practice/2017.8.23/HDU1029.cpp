#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000000;
const int inf=2147483647;

int n;
int Arr[maxN];

int main()
{
	while (cin>>n)
	{
		for (int i=1;i<=n;i++)
			scanf("%d",&Arr[i]);
		sort(&Arr[1],&Arr[n+1]);
		printf("%d\n",Arr[n/2+1]);
	}
	return 0;
}
