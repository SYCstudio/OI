#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1;
const int inf=2147483647;

int one=4;
int two=8;

int main()
{
	int K;scanf("%d",&K);
	if (K>2*18)
	{
		printf("-1\n");
		return 0;
	}
	while (K>=2) printf("%d",two),K-=2;
	if (K==1) printf("%d",one);
	printf("\n");
	return 0;
}
